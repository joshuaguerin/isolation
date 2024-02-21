/*
 * File: isola.h
 * Author: Joshua T. Guerin
 * Purpose: Documentation for the isola class.
 *          Manages the logic of the game isola.
 *
 */

#ifndef ISOLA_H
#define ISOLA_H

#include <vector>  // The game board is a 2D vector
#include "types.h" // Types associated with the game/tournament


class isola {
  /*
   * Description: Manages the logic for the game isola.
   */
 private:
  unsigned board_size;
  std::vector<std::vector<char> > board;
  location black_loc, white_loc;

  bool legal_move(location remove); 
  /*
   * Description: Checks whether the removal of location remove is a legal
   *              second-half of a move.
   * 
   * Preconditions: In general, this version of legal_move is to be called
   *                after the pawn's move has been applied.
   *
   * Notes: (For efficiency) Considers only the removal, assuming _half_ of 
   *        the current move has already been applied (the pawn's movement).
   *        Because there is no interface to apply only half of a move (the
   *        pawn's movement) this method is for internal use only.
   */
  
 public:
  isola();
  /*
   * Description: Initialize 7x7 isola board with players on the north
   *              and south ends.
   */

  isola(unsigned n);
  /*
   * Description: Initialize nxn isola board with players on the north
   *              and south ends.
   */

  void print();
  /*
   * Description: Prints the current game board configuration to the terminal.
   */
  
  void move(player p, direction d, location remove);
  /*
   * Description: Applies the move specified by d, remove to player p.
   * Postconditions: If the move is legal it has been applied.  If the
   *                  move was illegal (bad direction or bad remove) then
   *                  an exception is thrown.
   */
  
  location find_player(player p);
  /*
   * Description: Returns p's location on the game board as specified by
   *              the values of black_loc & white_loc.
   * Parameters:
   *     p - The player (black or white).
   * Returns:
   *     location: The (x,y) location of p.
   */

  
  bool legal_move(player p, direction d);
  /*
   * Description: Checks if p can move in direction d.
   *
   * Returns:
   *     true  - The location specified by (p, d) is a valid move.
   *     false - the location specified by (p, d) is removed or is currently
   *             occupied.
   *
   * Notes: Considers the board _as_is_, assuming no portion of the
   *        current move has been applied.
   */
  
  bool legal_move(player p, direction d, location remove);
  /*
   * Description: Checks (in order) whether p can:
   *              1. Move to the space indicated by direction d and
   *              2. Then remove the square indicated by remove (x, y).
   *
   * Returns:
   *     true  - The location specified by if (p, d) is a valid move and
   *             then the removal of remove can be applied.
   *     false - The location specified by (p, d) is removed or is currently
   *             occupied, or if the removal of location remove is illegal
   *             after the pawn's movement is applied..
   *
   * Note: Considers the board _as_is_, assuming no portion of the
   *       current move has been applied.
   */


  location new_location(player p, direction d);
  /*
   * Description: Computes the new location of p after a move has been
   *              applied in direction d.
   *
   * Returns:
   *     location: The (x, y) location of p after moving in direction d.
   */
  
  unsigned max_rows();
  /*
   * Description: Returns the maximum number of rows of the current board
   *              instance.  (Default: 7)
   *
   * Returns:
   *     The max number of rows as indicated by the outer dimension
   *     board.size.
   *
   * Note: The current implementation assumes a square game board (i.e., 
   *       max_rows() == max_cols()).
   */
  
  unsigned max_cols();
  /*
   * Description: Returns the maximum number of rows of the current board
   *              instance.  (Default: 7)
   *
   * Returns:
   *     The max number of rows as indicated by the outer dimension
   *     board[0].size() (each inner row should be identical in size).
   *
   * Note: The current implementation assumes a square game board (i.e., 
   *       max_rows() == max_cols()).
   */
  
  std::vector<char>& operator[](unsigned row);
  /*
   * Description: Returns the desired row (allows for an isola board to be
   *              double indexed: isola[row][col].
   *
   * Returns:
   *     A copy of the requested row of the game board.
   *
   */

  
  const std::vector<char>& operator[](unsigned row) const;
  /*
   * Description: Returns the desired row (allows for an isola board to be
   *              double indexed: isola[row][col].
   *
   * Returns:
   *     A copy of the requested row of the game board.
   *
   */

  std::vector<std::vector<char> > current_board();
  /*
   * Description: Returns a copy of the current board as it is stored
   *              internally (a 2d vector).
   *
   * Returns:
   *     A copy of the entire board configuration..
   *
   */
  
  bool lost_game(player p);
  /*
   * Description: Checks whether player p has any legal moves in terms
   *              of direction (should fail before removal fails).
   *
   * Returns:
   *     true  - p has lost the game.
   *     false - p can still legally move in one of: N/S/E/W/NW/NE/SW/SE.
   * 
   * Note: A returned value of false may imply either the other player's
   *       victory _or_ that a tie has occurred.
   */
};

#endif
