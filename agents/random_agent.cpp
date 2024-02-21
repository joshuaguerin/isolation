/*
 * File: random_agent.cpp
 * Author: Joshua T. Guerin
 * Description: A very simple isola agent.  For details see ordered_agent.h
 */

#include "random_agent.h"

// Change namespace name to your lastname_firstname
// Should be consistent with the namespace you select in your .h file.
namespace random_agent {

  // Can be hard-coded to any custom name for your agent.
  const std::string agent::agent_name ="Random Agent";
  
  agent::agent(player c) : color(c) {
    // Note: srand(time(NULL)) was already called in the main.
    // Don't bother to call again.
  }

  action agent::next_move(isola current_board) {
    // The primary logic for your agent: selects the next move based on
    // the current board state.
    direction pawn_direction;
    location current_location, to_remove;
    
    // Discover pawn's current location
    current_location = current_board.find_player(color);
    
    // Generate a random (valid) direction
    pawn_direction = random_direction();
    while(!current_board.legal_move(color, pawn_direction)) {
      pawn_direction = random_direction();
    }

    // Generate a random (valid) square to remove (assuming the previously
    // selected pawn move).
    to_remove = random_location(current_board.max_rows(),
				current_board.max_cols());
    while(!current_board.legal_move(color, pawn_direction, to_remove)) {
      to_remove = random_location(current_board.max_rows(),
				  current_board.max_cols());
    }

    // Return random move
    return action(pawn_direction, to_remove);
  } // agent::next_move


  direction agent::random_direction() {
    int number = rand()%8;

    switch(number){
    case 0:
      return north;
    case 1:
      return south;
    case 2:
      return east;
    case 3:
      return west;
    case 4:
      return northwest;
    case 5:
      return northeast;
    case 6:
      return southwest;
    }

    return southeast;
  } // agent::random_direction
  

  location agent::random_location(int max_rows, int max_cols) {
    location rand_loc;
    
    rand_loc.row = rand()%max_rows;
    rand_loc.col = rand()%max_cols;

    return rand_loc;
    
  } // agent::random_location
  
} // namespace random_agent
