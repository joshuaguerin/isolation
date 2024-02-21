/*
 * File: tournament.h
 * Author: Joshua T. Guerin
 * Purpose: Implements a tournament wrapper around the isola board game.
 *          That is, isola.cpp/.h is responsible for the game's logic,
 *          tournament.h is responsible for running a game or series of
 *          games and reporting the results.
 * 
 * Note: This is a templated class (template parameters are agent AI classes).
 *       As such there is no tournament.cpp.
 */

#include "isola.h" // Game board/logic
#include "types.h" // Types for isola game/tournament logic.

using namespace std;

template <typename TBlackAgent, typename TWhiteAgent>
class tournament {
  /*
   * Tournament class: Manages one or more rounds of isola as played by
   *                   agents TBlackAgent and TWhiteAgent.
   * 
   * Note: The order of TBlackAgent and TWhiteAgent should be irrelevant
   *       to the instantiation and/or playing of a round of isola.  Their
   *       order simply dictates pawn color.
   */
 private:
  // Simulation flags/data
  unsigned total_simulations;
  bool output_moves;
  bool pause_between_moves;
  bool display_winner;
  unsigned board_size;
  
 public:
  tournament();
  /*
   * Description: Constructs an isola tournament of one game of size 7,
   *              with output and pauses fully enabled.
   */
  
  tournament(unsigned num_simulations, bool print_moves, bool user_pause, \
	     bool print_winners, unsigned grid_size);
  /*
   * Description: Constructs an isola tournament given the user's preferences
   *              as indicated by the given parameters (which correspond
   *              directly to the private simulation flags of similar names).
   */
  
  void run();
  /*
   * Description: Runs a complete isola tournament based on the simulation
   *              flags.
   *
   * Requires:
   *    run_simulation() - To simulate individual games.
   */
  
  
  round_winner run_simulation();
  /*
   * Description: Simulates a single game of isola.
   * 
   * Notes: Starting player is randomly selected with uniform probability.
   */
  
  inline void clear_screen() { cout << "\033[2J\033[H"; };
  /*
   * Description: Clears the screen, resets the cursor position to home.
   * 
   * Notes: Uses the ansi escape sequences to clear the screen and move
   *        the cursor.  Should work on most *nix implementations, but
   *        cross-platform use is not otherwise guaranteed.
   */
};

template <typename TBlackAgent, typename TWhiteAgent>
  tournament<TBlackAgent, TWhiteAgent>::tournament() {
  total_simulations = 1;
  output_moves=true;
  pause_between_moves=true;
  display_winner=true;
  board_size = 7;
}

template <typename TBlackAgent, typename TWhiteAgent>
  tournament<TBlackAgent, TWhiteAgent>::tournament(unsigned num_simulations, bool print_moves, bool user_pause, bool print_winners, unsigned grid_size) {
  total_simulations = num_simulations;
  output_moves=print_moves;
  pause_between_moves=user_pause;
  display_winner=print_winners;
  board_size = grid_size;
}

template <typename TBlackAgent, typename TWhiteAgent>
void tournament<TBlackAgent, TWhiteAgent>::run() {
  int num_wins_black=0, num_wins_white=0;

  // Agents initialized only to get their names for report.
  TBlackAgent player_black(black);
  TWhiteAgent player_white(white);

  // Values returned by each simulation in run_simulation()
  round_winner winner;

  // Run a round of isola, tabulate results.
  // (Number of ties is calculated indirectly.)
  for(unsigned i=0; i<num_simulations; i++) {
    winner = run_simulation();
    if(winner.black && !winner.white)
      num_wins_black++;
    else if(!winner.black && winner.white)
      num_wins_white++;
  }

  // Generate a simulation report based on tournament play.
  if(num_simulations > 1) {
    cout << bold << "Generating tournament report..." << regular << endl
	 << bold << "Total simulations: " << regular << num_simulations << endl
	 << bold << "Total white wins: " << regular << num_wins_white
      	 << " (" << float(num_wins_white)/num_simulations * 100  << "%)" << endl
	 << bold << "Total black wins: " << regular << num_wins_black
	 << " (" << float(num_wins_black)/num_simulations * 100  << "%)" << endl
	 << bold << "Total ties: " << regular << num_simulations-num_wins_black-num_wins_white
	 << " (" << float(num_simulations - (num_wins_black+num_wins_white))/num_simulations * 100  << "%)" << endl << endl;
    
    cout << bold << "And the tournament winner is: " << regular;
    if(num_wins_black > num_wins_white)
      cout << "black, " << player_black.name();
    else if(num_wins_white > num_wins_black)
      cout << "white, " << player_white.name();
    else
      cout << "a tie";
    cout << endl;
  }
}

template <typename TBlackAgent, typename TWhiteAgent>
round_winner tournament<TBlackAgent, TWhiteAgent>::run_simulation() {
  isola game(board_size);
  // Default value (is changed randomly in a few lines)
  player current_move = white;
  action next;
  round_winner winner;

  // Randomly generate starting color.
  if(rand()%2 == 0)
    current_move = black;
  
  
  // Initialize both AI game agents.
  TBlackAgent player_black(black);
  TWhiteAgent player_white(white);
  
  if(output_moves | pause_between_moves) {
    cout << bold << "Starting game:" << regular << endl;
    if(pause_between_moves) {
      cout << "Press return to start or see next move." << endl;
      cin.get();
      clear_screen();
    }

    cout << bold << "Initial board:" << regular << " First move "
	 << (current_move==white ? "white":"black") << '.' << endl;
    game.print();
    cout << endl << endl;
  }

  // Play isola until at least one pawn loses.
  while(!game.lost_game(black) && !game.lost_game(white)) {
    if(pause_between_moves)
      cin.get();

    if(pause_between_moves)
      clear_screen();
    
    if(output_moves | pause_between_moves) {
      cout << bold << "Current move: " << regular
	   << ((current_move==white) ? "white":"black")
	   << " pawn" << endl;
    }

    
    // Find/apply next move.
    if(current_move == black) {
      next = player_black.next_move(game);
    }
    else if(current_move == white) {
      next = player_white.next_move(game);
    }

    // Note: In the current implementation if an agent selects
    // an invalid move that player's move (or partial move) is
    // skipped.
    try{
      game.move(current_move, next.move_to, next.remove);
    }catch(const char* &e) {
      cerr << endl << "-------------" << endl
	   << e << endl
	   << "Offending player is: "
	   << (current_move==white ? "white":"black") << endl
	   << endl
	   << "Move details" << endl
	   << "\t direction: " << next.move_to << endl
	   << "\t row: " << next.remove.row
	   << "\t column: " << next.remove.col
	   << endl << "-------------" << endl;
    }
    
    // Switch players.
    if(current_move == white)
      current_move = black;
    else
      current_move = white;

    if(output_moves | pause_between_moves) {
      game.print();
      cout << endl << endl;
    }
  }
  
  if(display_winner)
    cout << bold << "...And the winner is..." << regular << endl;

  // Declare winner or tie.
  if(game.lost_game(black) && game.lost_game(white)) {
    winner.black = true;
    winner.white = true;
    if(display_winner)
      cout << "A tie!" << endl;
  }
  else if(game.lost_game(black)) {
    winner.black = false;
    winner.white = true;
    if(display_winner)
      cout << "The white pawn: " << player_white.name() << "!" << endl;
  }
  else if(game.lost_game(white)) {
    winner.black = true;
    winner.white = false;
    if(display_winner)
      cout << "The black pawn: " << player_black.name() <<  "!" << endl;
  }
  
  if(display_winner)
    cout << endl;

  return winner;
} //tournament::run_simulation()

