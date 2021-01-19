#pragma once

#ifndef GRADIENT_FINDER_COLOR_H
#define GRADIENT_FINDER_COLOR_H

namespace gradient_finder
{

struct ColorDiff
{
    short r, g, b;

    ColorDiff(int r = 0, int g = 0, int b = 0)
        : r(static_cast<short>(r)), g(static_cast<short>(g)), b(static_cast<short>(b))
    { }

    bool isZero() const
    {
        return r == 0 && g == 0 && b == 0;
    }

    bool operator ==(const ColorDiff& other) const
    {
        return r == other.r && g == other.g && b == other.b;
    }

    bool operator !=(const ColorDiff& other) const
    {
        return r != other.r || g != other.g || b != other.b;
    }
};

struct Color
{
    using DiffType = ColorDiff;

    uint8_t r, g, b;

    ColorDiff operator -(const Color& other) const
    {
        return {short(r) - other.r, short(g) - other.g, short(b) - other.b};
    }
};

struct GrayDiff
{
    short c;

    GrayDiff(int c = 0)
        : c(static_cast<short>(c))
    { }

    bool isZero() const
    {
        return c == 0;
    }

    bool operator ==(const GrayDiff& other) const
    {
        return c == other.c;
    }

    bool operator !=(const GrayDiff& other) const
    {
        return c != other.c;
    }
};

struct Gray
{
    using DiffType = GrayDiff;

    uint8_t c;

    GrayDiff operator -(const Gray& other) const
    {
        return {short(c) - other.c};
    }
};

template <typename PixelType>
struct DiffType
{
    using Type = void;
};

template <>
struct DiffType<Color>
{
    using Type = ColorDiff;
};

template <>
struct DiffType<Gray>
{
    using Type = GrayDiff;
};

}

#endif // GRADIENT_FINDER_COLOR_H
