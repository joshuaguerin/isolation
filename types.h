/*
 * File: types.h
 * Author: Joshua T. Guerin
 * Purpose: Typedefs, structs, enums, and anything else required across
 *          isola, tournament, agent, or main files.
 */

#ifndef TYPES_H
#define TYPES_H

#include <string>

enum direction {
  // Legal move directions: vertical, horizontal, and diagonal.
  north, south, east, west, northwest, northeast, southwest, southeast
};

// Pawn colors.
enum player {black='b', white='w'};


struct round_winner {
  // The winner of an individual round (including ties).
  bool black, white;
  inline bool operator==(const round_winner& rhs){
    return black == rhs.black && white == rhs.white;
  }
};


struct location {
  /*
   * A location simply identifies one square's position (x, y) in the grid.
   *   E.g.,
   *   - board[location.row][location.col]
   */
  unsigned row; unsigned col;

  location() {}
  
  location(int r, int c):row(r), col(c) {}
  /*
   * Purpose: Convenient initialization.  E.g.,
   *     return location(5, 3);
   */

  inline bool operator==(const location& rhs){
    return row == rhs.row && col == rhs.col;
  }
  
};

struct action {
  /*
   * A valid (single) action on the current board (move_to, remove) where:
   *   - move_to is a valid direction indicating where to move the pawn
   *   - remove is a valid location indicating which square to punch out
   */
  direction move_to;
  location remove;

  action() {};
  action (direction d, location s):move_to(d), remove(s) {};
};

/*
 * Formatting string (inserted into cout as though they were manipulators).
 * Notes: All are ansi escape codes, not necessarily cross-platform.
 *        Any manipulation (bold, regular, underline) may persist after
 *        application is terminated.  (It is advisable to end each bold
 *        or underline with a regular when the bold or underlined texts are
 *        finished.
 */
const std::string bold="\033[1m";
const std::string regular="\033[0m";
const std::string underline="\33[4m";

#endif
