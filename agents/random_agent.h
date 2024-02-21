/*
 * File: random_agent.h
 * Description: Demonstrates a very basic isola agent.  The agent selects:
 *              1. a valid pawn move and then
 *              2. a valid square to remove after the pawn is moved.
 *
 * Notes: This is not a very strong agent, however it wins most of the
 *        time against the weaker provided agent (the ordered agent).
 *        All moves are weighted with equal probability so long as they
 *        are valid.
 */

#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include "../isola.h" // Game logic (required as a parameter to next_move)
#include "../types.h" // Isola/tournament types.

#include <random> // Included due to the random nature of this agent.

// Additional includes may be added here.

// Change namespace name to your lastname_firstname
namespace random_agent {
  class agent {
  private:
    player color; // Required
    const static std::string agent_name; // Required

    // Custom methods for the random agent (optional)
    direction random_direction();
    location random_location(int max_rows, int max_cols);

    // Additional helper methods can be declared here for internal
    // use as needed.
    
  public:
    agent(player c); // Required
    action next_move(isola current_board); // Required
    std::string name() {return agent_name; } // Required
  };
}

#endif
