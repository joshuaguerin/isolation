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

## Issues
I've used this framework for several semesters in my Artificial Intelligence course. So far no bugs have been reported by students. If you notice anything you would like to report, please feel free to create an issue.
