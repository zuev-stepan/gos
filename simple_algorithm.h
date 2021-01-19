#pragma once

#ifndef __GRADIENT_FINDER_SIMPLE_ALGORITHM_H__
#define __GRADIENT_FINDER_SIMPLE_ALGORITHM_H__

#include <vector>
#include <deque>
#include <cassert>

#include "matrix.h"
#include "rect.h"

namespace gradient_finder
{

template <typename ImageType>
class GradientState
{
public:
    explicit GradientState(const ImageType& image)
        : m_rImage(image), m_currentWidth(image.getWidth(), image.getHeight())
    {
        next(0, 0);
    }

    void next(size_t x, size_t y)
    {
        m_width = -1;
        m_minWidth = -1;
        m_currentWidth[x][y] = 1;
    }

    bool update(size_t currX, size_t currY, size_t prevX, size_t prevY, size_t& rNumColors)
    {
        auto diff = m_rImage[currX][currY] - m_rImage[prevX][prevY];
        if (!diff.isZero())
        {
            ++rNumColors;
            if (m_minWidth == size_t(-1))
            {
                m_minWidth = m_currentWidth[prevX][prevY];
                m_diff = diff;
            }
            else
            {
                if (m_diff != diff)
                {
                    return false;
                }
                if (m_currentWidth[prevX][prevY] < m_minWidth)
                {
                    return false;
                }

                if (m_width == size_t(-1))
                {
                    m_width = m_currentWidth[prevX][prevY];
                }
                else if (m_currentWidth[prevX][prevY] != m_width)
                {
                    return false;
                }
            }

            m_currentWidth[currX][currY] = 1;
        }
        else
        {
            m_currentWidth[currX][currY] = m_currentWidth[prevX][prevY] + 1;
            if (m_width != size_t(-1) && m_currentWidth[currX][currY] > m_width)
            {
                return false;
            }
        }

        return true;
    }

private:
    const ImageType& m_rImage;
    Matrix<size_t> m_currentWidth;
    size_t m_width, m_minWidth;
    typename DiffType<typename ImageType::Cell>::Type m_diff;
};

template <typename ImageType>
Rect find_gradient_simple(const ImageType& image)
{
    Rect ans{1, 0, 0, 0};

    GradientState<ImageType> xState(image), yState(image);
    std::vector<size_t> lastValid(image.getHeight()), numColorsX(image.getHeight());

    for (size_t fromX = 0; fromX < image.getWidth(); ++fromX)
    {
        for (size_t fromY = 0; fromY < image.getHeight(); ++fromY)
        {
            for (size_t toY = fromY; toY < image.getHeight(); ++toY)
            {
                lastValid[toY] = fromX;
                xState.next(fromX, toY);
                numColorsX[toY] = 0;
                for (size_t toX = fromX + 1; toX < image.getWidth(); ++toX)
                {
                    if (!xState.update(toX, toY, toX - 1, toY, numColorsX[toY]))
                    {
                        break;
                    }

                    lastValid[toY] = toX;
                }
            }

            for (size_t toX = fromX; toX < image.getWidth(); ++toX)
            {
                yState.next(toX, fromY);
                size_t numColorsY = 0;
                for (size_t toY = fromY + 1; toY < image.getHeight(); ++toY)
                {
                    if (!yState.update(toX, toY, toX, toY - 1, numColorsY))
                    {
                        break;
                    }

                    if (lastValid[toY] >= toX && numColorsX[toY] != 2 && numColorsY != 2)
                    {
                        Rect currAns{fromX, toX, fromY, toY};
                        if (ans.area() < currAns.area())
                        {
                            ans = currAns;
                        }
                    }
                }
            }
        }
    }

    return ans;
}

}

#endif // __GRADIENT_FINDER_SIMPLE_ALGORITHM_H__
