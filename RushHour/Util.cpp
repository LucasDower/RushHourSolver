#include "Util.h"

Pos::Pos(const uint16_t InCol, const uint16_t InRow)
    : Col(InCol)
    , Row(InRow)
{
}

uint32_t NextPowerOf2(uint32_t Value)
{
    uint32_t v = Value;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}