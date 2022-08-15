#include <stdio.h>

#include "Board.h"

int main()
{
    Board board(6, 6);
    board.AddPiece(HorizontalPiece(2, 'A'), {0, 0});
    board.AddPiece(HorizontalPiece(2, 'B'), {4, 0});
    board.AddPiece(HorizontalPiece(2, 'C'), {0, 1});
    board.AddPiece(HorizontalPiece(2, 'D'), {2, 2});
    board.AddPiece(HorizontalPiece(3, 'E'), {1, 3});
    board.AddPiece(HorizontalPiece(2, 'F'), {0, 5});
    board.AddPiece(HorizontalPiece(2, 'G'), {4, 5});

    board.AddPiece(VerticalPiece(2, 'Z'), {2, 0});
    board.AddPiece(VerticalPiece(3, 'Y'), {4, 1});
    board.AddPiece(VerticalPiece(3, 'X'), {0, 2});
    board.AddPiece(VerticalPiece(2, 'W'), {5, 3});
    board.AddPiece(VerticalPiece(2, 'V'), {3, 4});

    //board.GetInitialConfig()->Dump();
    board.Solve(3, 5, 2);

    return 0;
}