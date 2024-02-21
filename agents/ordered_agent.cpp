/*
 * File: ordered_agent.cpp
 * Author: Joshua T. Guerin
 * Description: A very simple isola agent.  For details see ordered_agent.h
 */

#include "ordered_agent.h"

// Change namespace name to your lastname_firstname
// Should be consistent with the namespace you select in your .h file.
namespace ordered_agent {

  // Can be hard-coded to any custom name for your agent.
  const std::string agent::agent_name = "Ordered Agent";

  agent::agent(player c) : color(c) {
    // Now initialized: color value (white, black)
    
    // Stupid agent, no initialization necessary.
  }

  action agent::next_move(isola current_board) {
    // The primary logic for your agent: selects the next move based on
    // the current board state.
    direction pawn_direction;
    location current_location, to_remove;
    
    // Discover pawn's current location
    current_location = current_board.find_player(color);

    // Move whatever direction we can in the following (arbitrary) order:
    // N, W, E, S, NW, NE, SW, SE
    if(current_board.legal_move(color, north)) {
      pawn_direction = north;
    }
    else if(current_board.legal_move(color, west)) {
      pawn_direction = west;
    }
    else if(current_board.legal_move(color, east)) {
      pawn_direction = east;
    }
    else if(current_board.legal_move(color, south)) {
      pawn_direction = south;
    }
    else if(current_board.legal_move(color, northwest)) {
      pawn_direction = northwest;
    }
    else if(current_board.legal_move(color, northeast)) {
      pawn_direction = northeast;
    }
    else if(current_board.legal_move(color, southwest)) {
      pawn_direction = southwest;
    }
    else if(current_board.legal_move(color, southeast)) {
      pawn_direction = southeast;
    }
    
    // Find the first square that is valid to remove, starting with 0,0
    // Once found, return immediately
    for(unsigned i=0; i<current_board.max_rows(); i++) {
      for(unsigned j=0; j<current_board.max_cols(); j++) {
	if(current_board.legal_move(color, pawn_direction, location(i, j))) {
	  to_remove.row = i;
	  to_remove.col = j;

	  // Return found move
	  return action(pawn_direction, to_remove);
	}
      }
    }

    // Final return to fulfill the compiler's demands.
    // Should never get here.
    return action(pawn_direction, to_remove);
    
  } // agent::next_move


} // namespace
