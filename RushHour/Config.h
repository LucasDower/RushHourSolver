#pragma once

#include <vector>
#include <memory>
#include <stdint.h>

#include "Util.h"

class Board;
class Piece;

class Config
{
public:
    Config(const Board* const InBoard, const std::shared_ptr<Config> InPrevConfig);

    void MovePieceForward(const PieceId InPieceId);
    void MovePieceBackward(const PieceId InPieceId);

    const Pos GetPieceStartPos(const PieceId InPieceId) const;
    const Pos GetPieceEndPos(const PieceId InPieceId) const;

    const Piece* GetPieceAt(const uint16_t InCol, const uint16_t InRow) const;
    bool IsEmptyAt(const uint16_t InCol, const uint16_t InRow) const;

    static void GenerateMovesForPiece(std::shared_ptr<Config> InConfig, const PieceId InPieceId, std::vector<std::shared_ptr<Config>>& OutQueue);
    static void GenerateMoves(std::shared_ptr<Config> InConfig, std::vector<std::shared_ptr<Config>>& OutQueue);

    bool DoesPieceOverlapPos(const PieceId InPieceId, const uint16_t InCol, const uint16_t InRow) const;

    void Dump() const;
    std::vector<std::shared_ptr<Config>> GetSteps() const;
    void DumpBoardSteps() const;
    void DumpPieceSteps() const;
    size_t Hash() const;

    /** The list of each piece's location indexed on the PieceId */
    std::vector<Pos> PiecePositions;

    /** The board that this configuration is based upon */
    const Board* const OwnerBoard;

    /** The configuration before this configuration */
    std::shared_ptr<Config> PrevConfig;

    uint8_t HashShiftLength;
};