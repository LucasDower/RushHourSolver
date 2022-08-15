#include "Piece.h"

Piece::Piece(const bool InIsHorizontal, const uint16_t InLength, const char InDisplayChar)
    : IsHorizontal(InIsHorizontal)
    , Length(InLength)
    , DisplayChar(InDisplayChar)
{
}

bool Piece::GetIsHorizontal() const
{
    return IsHorizontal;
}

uint16_t Piece::GetLength() const
{
    return Length;
}

char Piece::GetDisplayChar() const
{
    return DisplayChar;
}
