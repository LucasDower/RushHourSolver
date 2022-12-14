#pragma once

#include <stdint.h>

typedef size_t PieceId;

struct Pos
{
public:
    Pos(const uint16_t InCol, const uint16_t InRow);

    uint16_t Col;
    uint16_t Row;

    bool operator==(const Pos& Other) const
    {
        return Col == Other.Col && Row == Other.Row;
    }
};

uint32_t NextPowerOf2(uint32_t Value);