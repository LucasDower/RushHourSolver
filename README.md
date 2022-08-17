<p align="center">
  <img width="256" height="256" src="https://i.imgur.com/4pHDLUf.gif">
</p>

# RushHourSolver
[Rush Hour](https://en.wikipedia.org/wiki/Rush_Hour_(puzzle)) is a sliding block puzzle game. The aim of the game is to move the red car (use your imagination) to the goal (the white circle). Each car can only move horizontally/vertically and each car must move out of the way so that the red car can exit.

The hardest *Rush Hour* configuration is solveable in ~0.09s on my machine.

## Usage
```cpp
Board GameBoard(6, 6);

GameBoard.AddPiece(HorizontalPiece(2, 'B'), { 1, 0 });
GameBoard.AddPiece(HorizontalPiece(2, 'A'), { 3, 2 }); // <-- red car
GameBoard.AddPiece(HorizontalPiece(3, 'C'), { 0, 3 });
GameBoard.AddPiece(HorizontalPiece(2, 'D'), { 4, 4 });
GameBoard.AddPiece(HorizontalPiece(2, 'E'), { 0, 5 });
GameBoard.AddPiece(HorizontalPiece(2, 'F'), { 3, 5 });

GameBoard.AddPiece(VerticalPiece(3, 'G'), { 0, 0 });
GameBoard.AddPiece(VerticalPiece(2, 'L'), { 4, 0 });
GameBoard.AddPiece(VerticalPiece(2, 'H'), { 1, 1 });
GameBoard.AddPiece(VerticalPiece(2, 'I'), { 2, 1 });
GameBoard.AddPiece(VerticalPiece(2, 'K'), { 3, 3 });
GameBoard.AddPiece(VerticalPiece(2, 'J'), { 2, 4 });
GameBoard.AddPiece(VerticalPiece(3, 'M'), { 5, 1 });

GameBoard.GetInitialConfig()->Dump(); // print board
/*
GBB.L.
GHI.LM
GHIAAM
CCCK.M
..JKDD
EEJFF.
*/

GameBoard.Solve(/*red car index*/1, /*goal column*/5, /*goal row*/2);
```

**Note:** Moving "forward" for horizontal pieces means moving to the right and means moving downwards for vertical pieces.

### Visualisation
When the board is solved a sequence of 'moves' is printed to the console. This doesn't look very pretty so I've written a visualisation that requires [Processing](https://processing.org/) to run that produces the animation at the top of this README. This requires you to copy the **second** sequence of moves that are printed to the console into `/Visualisation/moves.txt`. The sequence to look for will look something like this:
```
5 1
10 1
2 1
2 1
6 1
0 0
6 1
8 1
8 1
9 0
1 0
1 0
7 1
12 0
...
```
