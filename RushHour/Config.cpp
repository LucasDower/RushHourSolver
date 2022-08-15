#include "Config.h"

#include "Board.h"
#include "Piece.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <functional>

Config::Config(const Board* const InBoard, const std::shared_ptr<Config> InPrevConfig)
    : OwnerBoard(InBoard)
    , PrevConfig(InPrevConfig)
{
}

void Config::MovePieceForward(const PieceId InPieceId)
{
    if (OwnerBoard->GetPiece(InPieceId).GetIsHorizontal())
    {
        ++PiecePositions[InPieceId].Col;
    }
    else
    {
        ++PiecePositions[InPieceId].Row;
    }
}

void Config::MovePieceBackward(const PieceId InPieceId)
{
    if (OwnerBoard->GetPiece(InPieceId).GetIsHorizontal())
    {
        --PiecePositions[InPieceId].Col;
    }
    else
    {
        --PiecePositions[InPieceId].Row;
    }
}

const Pos Config::GetPieceStartPos(const PieceId InPieceId) const
{
    return PiecePositions[InPieceId];
}

const Pos Config::GetPieceEndPos(const PieceId InPieceId) const
{
    Pos PiecePos = GetPieceStartPos(InPieceId);
    const Piece& ThisPiece = OwnerBoard->GetPiece(InPieceId);
    if (ThisPiece.GetIsHorizontal())
    {
        PiecePos.Col += ThisPiece.GetLength() - 1;
    }
    else
    {
        PiecePos.Row += ThisPiece.GetLength() - 1;
    }
    return PiecePos;
}

const Piece* Config::GetPieceAt(const uint16_t InCol, const uint16_t InRow) const
{
    for (size_t PieceId = 0; PieceId < PiecePositions.size(); ++PieceId)
    {
        const Pos& PiecePosition = PiecePositions[PieceId];
        const Piece& SomePiece = OwnerBoard->GetPiece(PieceId);

        if (SomePiece.GetIsHorizontal())
        {
            if (PiecePosition.Row == InRow && PiecePosition.Col <= InCol && InCol < PiecePosition.Col + SomePiece.GetLength())
            {
                return &SomePiece;
            }
        }
        else
        {
            if (PiecePosition.Col == InCol && PiecePosition.Row <= InRow && InRow < PiecePosition.Row + SomePiece.GetLength())
            {
                return &SomePiece;
            }
        }
    }
    return nullptr;
}

bool Config::IsEmptyAt(const uint16_t InCol, const uint16_t InRow) const
{
    return GetPieceAt(InCol, InRow) == nullptr;
}

const std::vector<std::shared_ptr<Config>> Config::GenerateMovesForPiece(std::shared_ptr<Config> InConfig, const PieceId InPieceId)
{
    std::vector<std::shared_ptr<Config>> Moves;
    Moves.reserve(2);

    const Piece& SomePiece = InConfig->OwnerBoard->GetPiece(InPieceId);

    {
        Pos BackwardPos = InConfig->GetPieceStartPos(InPieceId);
        if (SomePiece.GetIsHorizontal())
        {
            --BackwardPos.Col;
        }
        else
        {
            --BackwardPos.Row;
        }

        if (InConfig->IsEmptyAt(BackwardPos.Col, BackwardPos.Row))
        {
            if (BackwardPos.Col >= 0 && BackwardPos.Col < InConfig->OwnerBoard->GetWidth() && BackwardPos.Row >= 0 && BackwardPos.Row < InConfig->OwnerBoard->GetHeight())
            {
                Config NewConfig = *InConfig.get();
                NewConfig.MovePieceBackward(InPieceId);
                NewConfig.PrevConfig = InConfig;
                Moves.push_back(std::make_shared<Config>(NewConfig));
            }
        }
    }
    {
        Pos ForwardPos = InConfig->GetPieceEndPos(InPieceId);
        if (SomePiece.GetIsHorizontal())
        {
            ++ForwardPos.Col;
        }
        else
        {
            ++ForwardPos.Row;
        }

        if (InConfig->IsEmptyAt(ForwardPos.Col, ForwardPos.Row))
        {
            if (ForwardPos.Col >= 0 && ForwardPos.Col < InConfig->OwnerBoard->GetWidth() && ForwardPos.Row >= 0 && ForwardPos.Row < InConfig->OwnerBoard->GetHeight())
            {
                Config NewConfig = *InConfig.get();
                NewConfig.MovePieceForward(InPieceId);
                NewConfig.PrevConfig = InConfig;
                Moves.push_back(std::make_shared<Config>(NewConfig));
            }
        }
    }

    return Moves;
}

const std::vector<std::shared_ptr<Config>> Config::GenerateMoves(std::shared_ptr<Config> InConfig)
{
    std::vector<std::shared_ptr<Config>> NewConfigs;
    for (size_t PieceId = 0; PieceId < InConfig->OwnerBoard->GetNumPieces(); ++PieceId)
    {
        const std::vector<std::shared_ptr<Config>> NewPieceConfigs = GenerateMovesForPiece(InConfig, PieceId);
        for (const std::shared_ptr<Config>& Tmp : NewPieceConfigs)
        {
            NewConfigs.push_back(Tmp);
        }
    }
    return NewConfigs;
}

bool Config::DoesPieceOverlapPos(const PieceId InPieceId, const uint16_t InCol, const uint16_t InRow) const
{
    const Piece& SomePiece = OwnerBoard->GetPiece(InPieceId);
    const Pos& PiecePos = PiecePositions[InPieceId];

    if (SomePiece.GetIsHorizontal())
    {
        if (PiecePos.Row == InRow && PiecePos.Col <= InCol && InCol < PiecePos.Col + SomePiece.GetLength())
        {
            return true;
        }
    }
    else
    {
        if (PiecePos.Col == InCol && PiecePos.Row <= InRow && InRow < PiecePos.Row + SomePiece.GetLength())
        {
            return true;
        }
    }

    return false;
}

void Config::Dump() const
{
    for (uint16_t RowIndex = 0; RowIndex < OwnerBoard->GetHeight(); ++RowIndex)
    {
        for (uint16_t ColIndex = 0; ColIndex < OwnerBoard->GetWidth(); ++ColIndex)
        {
            if (const Piece* OccupyingPiece = GetPieceAt(ColIndex, RowIndex))
            {
                printf("%c", OccupyingPiece->GetDisplayChar());
            }
            else
            {
                printf(".");
            }
        }
        printf("\n");
    }
    //printf("%llu\n", Hash());
    printf("\n");
}

void Config::DumpTrace() const
{
    Dump();
    size_t MovesCount = 1;

    std::shared_ptr<Config> NextConfig = PrevConfig;
    while (NextConfig)
    {
        NextConfig->Dump();
        NextConfig = NextConfig->PrevConfig;
        ++MovesCount;
    }

    printf("Took %d moves.\n", MovesCount);
}

size_t Config::Hash() const
{
    const size_t NumPieces = OwnerBoard->GetPieces().size();
    uint64_t HashValue = 0;

    std::stringstream ss;
    
    for (const Pos& SomePos : PiecePositions)
    {
        ss << SomePos.Col << SomePos.Row;
    }

    std::string s = ss.str();

    return std::hash<std::string>{}(s);
}
