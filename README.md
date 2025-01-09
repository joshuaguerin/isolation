# Isolation
A C++ implementation of the board game [Isolation](https://en.wikipedia.org/wiki/Isolation_(board_game)). Designed to practice building agents and playing the game with them.

## Compilation
At the moment the project doesn't need any per-machine configuration. To compile simply download, and run `make` in the directory with the [Makefile](./Makefile). It should compile everything and generate the `tournament` binary.

## Use
All options are for the single, `tournament` binary.

```
./tournament
```
* Runs the agents against each other, prints only the result.

### Flags
```
--help
```
* Prints the help file. Also available with the `-h` flag.

```
--grid n
```
* Runs the tournament with a custom board size. All boards are square.

```
--output
```
* Prints turn-by-turn information. Also available as `-o`.

```
--pause
```
* Requires the user to hit the `return` key between moves. Builds suspense.
* Also available as `-p`.

```
--simulations n
```
* Runs the tournament `n` times. Good to determine which agent is better.
* Also available with the `-s` flag.

```
--winner
```
* Suppresses all informations, usually for the -s flag.

## Sample Run

Note, numerous moves were removed to simplify output.

```
./tournament -o
Starting game:
Initial board: First move black.
  0123456
0|   b   |
1|       |
2|       |
3|       |
4|       |
5|       |
6|   w   |


Current move: black pawn
  0123456
0|       |
1|    b  |
2|       |
3|       |
4|       |
5|   X   |
6|   w   |


Current move: white pawn
  0123456
0|X      |
1|    b  |
2|       |
3|       |
4|       |
5|   X   |
6|  w    |
.
.
.

Current move: black pawn
  0123456
0|XXXXXXX|
1|XXXXXXX|
2|XXXXXXX|
3|wXX X b|
4| XX   X|
5|XX X   |
6| X XX  |


Current move: white pawn
  0123456
0|XXXXXXX|
1|XXXXXXX|
2|XXXXXXX|
3|XXX X b|
4|wXX   X|
5|XX X   |
6| X XX  |


...And the winner is...
The black pawn: Random Agent!
```

## Modifying
I've made this available on a public repo for the explicit purpose of learning. If you are a professor who is interested in using this for a project (or student), please reach out! It would warm my heart to learn that someone out there found it useful! For any non-academic purposes, please reach out for permission.

I've tried to streamline the addition of new agents. *Most* of the work required is to put together your own code in its own files in the [agents](agents) directory. I've drafted up two relatively simple (and unsophisticated) agents for this purpose to present basic functionality. The only other additions required are to modify the [Makefile](Makefile) so that compilation is possible, and make a couple of quick edits to the [driver](main.cpp) to `#include` your agent and add it to the current tournament.

For a more detailed account of adding agents, please see the README in the [agents directory](agents).

If more sophisticated modificatoins to existing functionality are desired you can always reach out on the issues page, but my ability to support you may be a bit more limited depending on timing. Otherwise, I have tried to keep things somwhat organized and readable to make your job easier!

## Issues
I've used this framework for several semesters in my Artificial Intelligence course. So far no bugs have been reported by students. If you notice anything you would like to report, please feel free to create an issue.
