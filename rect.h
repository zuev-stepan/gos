#pragma once

#ifndef __GRADIENT_FINDER_RECT_H__
#define __GRADIENT_FINDER_RECT_H__

#include <vector>
#include <deque>
#include <cassert>

#include "gradient_description.h"

namespace gradient_finder
{

struct Rect
{
    size_t left, right, up, down;

    size_t area() const
    {
        return (right - left + 1) * (down - up + 1);
    }
};

}

#endif // __GRADIENT_FINDER_RECT_H__
