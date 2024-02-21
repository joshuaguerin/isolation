/*
 * File: ordered_agent.h
 * Description: Demonstrates a very basic isola agent.  This agent always
 *              attempts to move north, but will attempt other directions
 *              in a hard-coded order (N/W/E/S/NW/NE/SW/SE) until it locates
 *              a valid move, and then applies it.
 *              (Not a very strong AI.)
 */


#ifndef ORDERED_AGENT_H
#define ORDERED_AGENT_H

#include "../isola.h" // Game logic (required as a parameter to next_move)
#include "../types.h" // Isola/tournament types.

// Additional includes may be added here.

// Change namespace name to your lastname_firstname
namespace ordered_agent {
  class agent {
  private:
    player color; // Required
    const static std::string agent_name; // Required

    // Additional helper methods can be declared here for internal
    // use as needed.
    
  public:
    agent(player c); // Required
    action next_move(isola current_board); // Required
    std::string name() { return agent_name; } // Required
  };
}

#endif
