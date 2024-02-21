# Agents Directory

Here is where you can add/modify/test new agent strategies. I've provided two agents as starters:
* Random Agent - Selects a randomized square to punch and move.
* Ordered Agent - Aggressive, but stupid. Chooses a pawn move in the following order: N, W, E, S, NW, NE, SW, SE. Starts punching at 0, 0, and keeps searching. The moment it finds a valid move, it deploys it.

Neither agent is capable of planning/forethought. That is left up to the user to design.

### Implementing
Either agent given can be modified in the `.h` or `.cpp` files. Adding functionality in the form of more methods or data members shouldn't compromise either implementation.

The primary method is: `action agent::next_move(isola current_board)`. Given a copy of the board, the agent returns a move action.

## New Agents
A new agent can be added to this directory by copying either agent into a new pair of files. Make sure to give it a descriptive name and namespace (`.cpp` file). There are a couple of additional modifications needed, but nothing that should prove terribly complicated.

Further modifications to finish adding:
* Update the `Makefile` to include compilation.

Update the `main.cpp` driver:
* Add an `#include` statement.
* Edit the `tournament` declaration in the main (line 63) to include the agent.