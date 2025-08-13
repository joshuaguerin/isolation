# Initialization Directory

Here is where you can store files containing initialization states for the game board. These state files are encoded as plain-text, and represent the game board in much the same way it is represented internally and printed to the screen.

This feature was added so that mid-game playout could be tested. E.g., An agent could be put initially at a mid-game disadvantage to demonstrate how well it will cope.

You can use the file to provide symbols for an `n`x`n` grid, and:
* pre-punch board locations (with an `X`) or
* move the starting placement of the `b` and `w` agents.

The implementation should take partial files (not a full `n`x`n` grid) or full enumerations of the game board.

Note that an incomplete or inconsistent file could specify full or partial boards that do not make sense. Because there are a range of possible applications of this feature due to incomplete files being allowed, minimal error checking is done by the system to validate the starting placements for consistency.

I.e., The user must ensure that any initialization files provided are correct within the rules of the game or undefined behaviors may occur.
