#pragma once

#include <stdint.h>

class Piece
{
public:
    Piece(const bool InIsHorizontal, const uint16_t InLength, const char InDisplayChar);

    bool GetIsHorizontal() const;
    uint16_t GetLength() const;
    char GetDisplayChar() const;

private:
    const bool IsHorizontal;
    const uint16_t Length;
    const char DisplayChar;
};

class HorizontalPiece : public Piece
{
public:
    HorizontalPiece(const uint16_t InLength, const char InDisplayChar)
        : Piece(true, InLength, InDisplayChar)
    {
    }
};

class VerticalPiece : public Piece
{
public:
    VerticalPiece(const uint16_t InLength, const char InDisplayChar)
        : Piece(false, InLength, InDisplayChar)
    {
    }
};