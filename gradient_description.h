#pragma once

#ifndef __GRADIENT_FINDER_GRADIENT_DESCRIPTION_H__
#define __GRADIENT_FINDER_GRADIENT_DESCRIPTION_H__

#include "matrix.h"
#include "color.h"

namespace gradient_finder
{

template <typename MatrixType>
struct GradientDescription
{
    using DiffType = typename DiffType<typename MatrixType::Cell>::Type;

    size_t length;
    size_t width;
    size_t currentWidth;
    DiffType diff;

    explicit GradientDescription(size_t length = 1, size_t width = 1, size_t currentWidth = 1, DiffType diff = {})
        : length(length), width(width), currentWidth(currentWidth), diff(diff)
    { }
};

template <typename GradientDescription, typename PixelType>
GradientDescription update(GradientDescription desc, const PixelType& prev, const PixelType& curr, bool& rColorChanged)
{
    auto diff = curr - prev;
    if (!diff.isZero())
    {
        rColorChanged = true;
        if (desc.diff == diff)
        {
            if (desc.currentWidth < desc.width) // 0 0 1 1 2 |3|
            {
                desc.length = desc.currentWidth * 2;
            }

            ++desc.length;
        }
        else // 0 0 1 1 2 |4| // 0 0 1 1 2 2 |4|
        {
            desc.length = desc.currentWidth + 1;
            //state = State::eAdjustingWidth;
        }

        desc.width = desc.currentWidth;
        desc.currentWidth = 1;
        desc.diff = diff;
    }
    else
    {
        rColorChanged = false;
        ++desc.currentWidth;

        if (desc.currentWidth > desc.width) // 0 0 1 1 2 2 |2|
        {
            desc.length = std::min(desc.length + 1, desc.currentWidth + desc.width);
            desc.width = desc.currentWidth;
            //state = State::eAdjustingWidth;
        }
        else
        {
            ++desc.length;
        }
    }

    return desc;
}

}

#endif // __GRADIENT_FINDER_GRADIENT_DESCRIPTION_H__
