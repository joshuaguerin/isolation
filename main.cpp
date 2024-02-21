/*
 * File: main.cpp
 * Author: Joshua T. Guerin
 * Purpose: Driver for the isola tournament.
 *          Manages command line arguments and runs the tournament.
 *
 */


#include <iostream>  // console io
#include <random>    // srand(), rand()
#include <ctime>     // time() for srand()
#include <getopt.h>  // getopt()
#include <cstdlib>   // atoi()
#include <algorithm> // remove()

// Simulation Flags
bool output_moves=false;
bool pause_between_moves=false;
bool display_winner=true;
unsigned num_simulations=1;
unsigned grid_size=7;

#include "tournament.h" // Templated class that runs an isola tournament.
#include "types.h"      // Types associated with game/tournament.

/*
 * Agents to play the game.
 * Notes: Include any additional agents here.
 *        Agents that are included but not used to instantiate a tournament
 *        object are effectively ignored.
 */
#include "agents/random_agent.h"
#include "agents/ordered_agent.h"


using namespace std;


void parse_args(int argc, char *argv[]);
/*
 * Description: Parses command line arguments, sets associated flags.
 * Parameters:
 *    int argc - argc that is passed into main()
 *    int argv - argv that is passed into main()
 */


void help(string binary_name, string options);
/*
 * Description: Prints usage message if -h or --help flags arguments
 *              are passed on the command line.
 */


int main(int argc, char *argv[]) {
  srand(time(NULL));
  
  parse_args(argc, argv);
  
  // You can change random_agent::agent or ordered_agent::agent
  // to initialize any two agents of your own design or mine for testing.
  tournament<random_agent::agent, ordered_agent::agent>
    tourney(num_simulations, output_moves, pause_between_moves,
	    display_winner, grid_size);

  // Run tournament
  tourney.run();
    
  return 0;
}


void parse_args(int argc, char *argv[]) {
  int option;
  char *cvalue = NULL;
  opterr = 0;

  // getopt_long arguments
  string options = "g:hops:w";
  const struct option long_options[] =
    {
      {"grid",        required_argument,  0, 'g'},
      {"help",        no_argument,        0, 'h'},
      {"output",      no_argument,        0, 'o'},
      {"pause",       no_argument,        0, 'p'},
      {"simulations", required_argument,  0, 's'},
      {"winner",      no_argument,        0, 'w'},
      {0,0,0,0},
    };
  int option_index;
    
  
  option = getopt_long(argc, argv, options.c_str(),
		       long_options, &option_index);
  
  while(option != -1) {
    switch(option) {
    case 'g':
      // Grid size flag
      cvalue = optarg;
      grid_size = atoi(cvalue);
      break;
    case 'h':
      // Help flag
      help(argv[0], options);
      exit(0);
      break;
    case 'o':
      // Output individual moves
      output_moves = true;
      break;
    case 'p':
      // Pause for user input between moves
      pause_between_moves = true;
      break;
    case 's':
      // Number of simulated games to run
      cvalue = optarg;
      num_simulations = atoi(cvalue);
      break;
    case 'w':
      // If the winner flag is provided suppress the display of individual
      // round wins.
      display_winner = false;
      break;
    case '?':
      if(optopt == 'g' || optopt == 's') {
	cerr << "Error: Option -"<< char(optopt)
	     <<" requires an argument." << endl;
      }
      else {
	cerr << "Error: Unrecognized argument '-" << char(optopt)
	     <<  "'." << endl;
      }
      cerr << "See the -h option for usage." << endl;
      exit(0);
      break;
    default:
      cerr << "Error: Unknown argument: " << char(option) << endl;
      exit(0);
      break;
    }

    option = getopt_long(argc, argv, options.c_str(),
			 long_options, &option_index);
  }
}


void help(string binary_name, string options) {
  options.erase(remove(options.begin(), options.end(), ':'), options.end());

  cout << bold << "NAME\n\t" << binary_name << regular << " -- plays an isola tournament using two software agents" << endl
       << bold << "SYNOPSIS: \n\t" << binary_name
       << " [-" << options << "]" << regular << endl
       << bold << "OPTIONS:" << regular << endl
       << bold << "-g | --grid n" << regular
       << "         Sets gameboard size to " << bold << 'n' << regular << 'x' << bold << 'n' << regular << '.' << endl
       << bold << "-h | --help" << regular
       << "           Print this help." << endl
       << bold << "-o | --output" << regular
       << "         Outputs turn-by-turn moves." << endl
       << bold << "-p | --pause" << regular
       << "          Same as -o, except there is a pauses after each" << endl
       << "                      move until the user types the <return> key." << endl
       << bold << "-s | --simulations n" << regular
       << "  Specifies the number of simulations " << bold
       << "n" << regular << " in the tournament." << endl
       << bold << "-w | --winner" << regular
       << "         Suppresses the display of individual round wins for "
       << endl << "                      multi-round tournaments." << endl;
}
