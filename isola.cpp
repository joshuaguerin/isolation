/*
 * File: isola.cpp
 * Author: Joshua T. Guerin
 * Description: Implementation of the isola game logic.  See isola.h for
 *              details.
 */

#include <iostream>

#include "isola.h"

using namespace std;

isola::isola() : board(7, vector<char>(7, ' ')) {
  // Initialize board size.
  board_size = 7;

  // Locate the starting positions of black, white pawns
  black_loc = location(0, max_cols()/2);
  white_loc = location(max_rows()-1, max_cols()/2);

  // Place pawns.
  board[black_loc.row][black_loc.col] = 'b';
  board[white_loc.row][white_loc.col] = 'w';
}

isola::isola(unsigned n) : board(n, vector<char>(n, ' ')) {
  // Initialize board size.
  board_size=n;

  // Locate the starting positions of black, white pawns.
  black_loc = location(0, max_cols()/2);
  white_loc = location(max_rows()-1, max_cols()/2);

  // Place pawns.
  board[black_loc.row][black_loc.col] = 'b';
  board[white_loc.row][white_loc.col] = 'w';
}

void isola::print() {
  // Print guide-numbers, underlined
  cout << "  " << underline;
  for(unsigned i=0; i<board_size; i++) {
    cout << i%10;
  }
  cout << regular << endl;
  
  for(unsigned i=0; i<board.size(); i++) {
    cout << i%10 << '|';

    // Underline bottom row
    if(i==board.size()-1)
      cout << underline;
    
    for(unsigned j=0; j<board.size(); j++) {
      cout << board[i][j];
    }

    // Move back to default text font.
    if(i == board.size()-1)
      cout << regular;
    
    cout << '|' << endl;
  }
}


location isola::find_player(player p) {
  if(p == black)
    return black_loc;
  
  return white_loc;
}


void isola::move(player p, direction d, location remove) {
  location pawn_location = find_player(p);
  location new_pawn_location = pawn_location;

  // If the move in direction d cannot be implied throw an exception.
  if(!legal_move(p, d, remove))
    throw "Illegal Move: Illegal Direction";

  // Empty previous pawn location
  board[pawn_location.row][pawn_location.col] = ' ';

  // Compute new pawn location
  new_pawn_location = new_location(p, d);

  // Move pawn to next location
  board[new_pawn_location.row][new_pawn_location.col] = p;

  // Update internal state for pawn's location.
  if(p == black)
    black_loc = new_pawn_location;
  else
    white_loc = new_pawn_location;

  // If the tile indicated by location remove cannot be removed, throw an
  // exception.
  if(!legal_move(remove))
    throw "Illegal_move: Illegal Tile Removal";
  
  board[remove.row][remove.col] = 'X';
}

bool isola::legal_move(player p, direction d) {
  location pawn_location = find_player(p);
  location new_pawn_location = pawn_location;

  // Compute new pawn location
  new_pawn_location = new_location(p, d);

  // Check new pawn location for validity
  if(max_rows() <= new_pawn_location.row ||
     max_cols() <= new_pawn_location.col)
    return false;

  // Ensure that the new location has not already been removed.
  if(board[new_pawn_location.row][new_pawn_location.col] == 'X')
    return false;

  // Ensure that the pawn is not being moved into the other pawn's location.
  if(p == black &&
     board[new_pawn_location.row][new_pawn_location.col] == white)
    return false;
  else if(p == white &&
	  board[new_pawn_location.row][new_pawn_location.col] == black)
    return false;  
  
  return true;
}

bool isola::legal_move(player p, direction d, location remove) {
  // Check whether pawn move is legal
  if(!legal_move(p, d))
    return false;
  
  location pawn_location = find_player(p);
  location new_pawn_location = pawn_location;

  // Compute new pawn location
  new_pawn_location = new_location(p, d);
  
  // Removed square cannot be the pawn's new location.
  if(remove == new_pawn_location)
    return false;

  // Removed location may be only a blank or the player's old location.
  if(board[remove.row][remove.col] != ' ' &&
     board[remove.row][remove.col] != p)
    return false;
  
  return true;
}

bool isola::legal_move(location remove) {
  //Verify whether removed square is legal
  if(remove.row > board.size()-1 || remove.col > board.size()-1) {
    return false;
  }
  
  if(board[remove.row][remove.col] == ' ')
    return true;
  return false;
}



location isola::new_location(player p, direction d) {
  //Find current location
  location pawn_location = find_player(p);
  location new_pawn_location = pawn_location;

  //Compute new location
  if(d == north)
    new_pawn_location.row--;
  else if(d == south)
    new_pawn_location.row++;
  else if(d == west)
    new_pawn_location.col--;
  else if(d == east)
    new_pawn_location.col++;
  else if(d == northwest) {
    new_pawn_location.row--;
    new_pawn_location.col--;
  }
  else if(d == northeast) {
    new_pawn_location.row--;
    new_pawn_location.col++;
  }
  else if(d == southwest) {
    new_pawn_location.row++;
    new_pawn_location.col--;
  }
  else if(d == southeast) {
    new_pawn_location.row++;
    new_pawn_location.col++;
  }

  return new_pawn_location;
}


unsigned isola::max_rows() {
  // Get outer dimension.
  return board.size();
}


unsigned isola::max_cols() {
  // All inner dimensions should be equal.
  return board[0].size();
}


vector<char>& isola::operator[](unsigned row) {
  // Gives the isola object bracketed access: board[row][col]
  return board[row];
}


const vector<char>& isola::operator[](unsigned row) const {
  // Gives the isola object bracketed access: board[row][col]
  return board[row];
}


vector<vector<char> > isola::current_board() {
  return board;
}


bool isola::lost_game(player p) {
  if(!legal_move(p, north) &&
     !legal_move(p, south) &&
     !legal_move(p, east) &&
     !legal_move(p, west) &&
     !legal_move(p, northwest) &&
     !legal_move(p, northeast) &&
     !legal_move(p, southwest) &&
     !legal_move(p, southeast)) {
    // No moves are possible
    return true;
  }
  return false;
}
