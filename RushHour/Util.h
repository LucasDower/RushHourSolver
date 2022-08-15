#pragma once

#include <stdint.h>

typedef size_t PieceId;

struct Pos
{
public:
    Pos(const uint16_t InCol, const uint16_t InRow);

    uint16_t Col;
    uint16_t Row;
};
