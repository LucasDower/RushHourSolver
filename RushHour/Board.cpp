#include "Board.h"

#include <unordered_set>
#include <queue>

PieceId Board::AddPiece(const Piece& InPiece, const Pos& InPos)
{
    _Pieces.push_back(InPiece);
    _PiecePositions.push_back(InPos);

    return _Pieces.size() - 1;
}

const std::shared_ptr<Config> Board::GetInitialConfig() const
{
    Config config(this, nullptr);
    for (const Pos& SomePosition : _PiecePositions)
    {
        config.PiecePositions.push_back(SomePosition);
    }
    return std::make_shared<Config>(config);
}

uint16_t Board::GetWidth() const
{
    return Width;
}

uint16_t Board::GetHeight() const
{
    return Height;
}

const Piece& Board::GetPiece(const PieceId InPieceId) const
{
    return _Pieces[InPieceId];
}

const std::vector<Piece> Board::GetPieces() const
{
    return _Pieces;
}

const size_t Board::GetNumPieces() const
{
    return _Pieces.size();
}

void Board::Solve(const PieceId InPieceId, const uint16_t InGoalCol, const uint16_t InGoalRow) const
{
    std::unordered_set<size_t> SeenConfigs;
    std::queue<std::shared_ptr<Config>> ConfigsQueue({ GetInitialConfig() });

    uint32_t ConfigsSearched = 0;

    std::vector<std::shared_ptr<Config>> NewMoves;
    NewMoves.reserve(GetNumPieces() * 2); // Each piece can potentially move forward or backward

    while (ConfigsQueue.size() > 0)
    {
        const std::shared_ptr<Config>& SomeConfig = ConfigsQueue.front();

        // Check if this is a winning state
        if (SomeConfig->DoesPieceOverlapPos(InPieceId, InGoalCol, InGoalRow))
        {
            printf("Steps to solve:\n");
            SomeConfig->DumpBoardSteps();

            printf("Paste this sequence in /Visualisation/moves.txt to animate:\n");
            SomeConfig->DumpPieceSteps(false);

            printf("\nFound winning config!\n");
            printf("Solved in %llu step(s)\n", SomeConfig->GetSteps().size());
            printf("Searched %d configurations.\n", ConfigsSearched);

            return;
        }

        NewMoves.clear();
        Config::GenerateMoves(SomeConfig, NewMoves);

        // Only add each new configuration if the configuration is unique
        for (const std::shared_ptr<Config>& NewMove : NewMoves)
        {
            if (SeenConfigs.count(NewMove->Hash()) == 0)
            {
                ConfigsQueue.push(NewMove);
                SeenConfigs.insert(NewMove->Hash());
            }
        }

        ++ConfigsSearched;
        ConfigsQueue.pop();
    }

    printf("Searched %d configurations.\n", ConfigsSearched);
    printf("Could not find winning config!\n");
}