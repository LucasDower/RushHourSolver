#pragma once

#include <stdint.h>
#include <vector>
#include <memory>

#include "Piece.h"
#include "Config.h"
#include "Util.h"

class Board
{
public:
    Board(const uint16_t InWidth, const uint16_t InHeight)
        : Width(InWidth)
        , Height(InHeight)
    {
    }

    PieceId AddPiece(const Piece& InPiece, const Pos& InPos);

    uint16_t GetWidth() const;
    uint16_t GetHeight() const;
    const Piece& GetPiece(const PieceId InPieceId) const;
    const std::vector<Piece> GetPieces() const;
    const size_t GetNumPieces() const;
    const std::shared_ptr<Config> GetInitialConfig() const;

    void Solve(const PieceId InPieceId, const uint16_t InCol, const uint16_t InRow) const;

private:

    const uint16_t Width;
    const uint16_t Height;
    std::vector<Piece> _Pieces;
    std::vector<Pos> _PiecePositions;

};
