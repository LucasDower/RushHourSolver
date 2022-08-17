#include <stdio.h>
#include <chrono>

#include "Board.h"
#include "Util.h"


int main()
{
    Board GameBoard(6, 6);

    GameBoard.AddPiece(HorizontalPiece(2, 'B'), { 1, 0 });
    GameBoard.AddPiece(HorizontalPiece(2, 'A'), { 3, 2 });
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

    GameBoard.GetInitialConfig()->Dump();
    const auto StartTime = std::chrono::high_resolution_clock::now();
    GameBoard.Solve(1, 5, 2);
    const auto EndTime = std::chrono::high_resolution_clock::now();

    const auto Duration = duration_cast<std::chrono::microseconds>(EndTime - StartTime);
    printf("%d ms\n", Duration.count());

    return 0;
}