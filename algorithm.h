#pragma once

#ifndef __GRADIENT_FINDER_ALGORITHM_H__
#define __GRADIENT_FINDER_ALGORITHM_H__

#include <vector>
#include <deque>
#include <cassert>

#include "gradient_description.h"
#include "rect.h"

namespace gradient_finder
{

struct PosValue
{
    size_t pos;
    size_t value;

    PosValue(size_t pos, size_t value)
        : pos(pos), value(value)
    { }
};

struct ColumnPart
{
    std::deque<PosValue> column;

    const PosValue& getMin() const
    {
        assert(!column.empty());

        return column.front();
    }

    void add(size_t pos, size_t value)
    {
        while (!column.empty() && column.back().value >= value)
        {
            column.pop_back();
        }

        column.emplace_back(pos, value);
    }

    void setPos(size_t newPos)
    {
        while (!column.empty() && column.front().pos < newPos)
        {
            column.pop_front();
        }
    }

    void clear()
    {
        column.clear();
    }
};

template <typename GradientDescription>
bool is_valid_concat(const GradientDescription& left, const GradientDescription& right)
{

}

template <typename ImageType>
Rect find_gradient(const ImageType& image)
{
    Matrix<Rect> ans(image.getWidth(), image.getHeight());
    Rect bestAns{1, 0, 0, 0};

    std::vector<GradientDescription<ImageType>> up(image.getWidth()), left(image.getWidth());
    std::vector<size_t> leftBound(image.getWidth()), rightBound(image.getWidth());
    std::vector<std::deque<size_t>> verticalColorChanges(image.getWidth());
    std::deque<size_t> horizontalColorChanges;
    std::vector<size_t> colorChanges(image.getWidth());
    std::vector<ColumnPart> leftPush(image.getWidth()), rightPush(image.getWidth());
    ColumnPart upPush;

    for (size_t y = 0; y < image.getHeight(); ++y)
    {
        if (y > 0)
        {
            for (size_t x = 0; x < image.getWidth(); ++x)
            {
                bool colorChanged = false;
                up[x] = update(up[x], image[x][y - 1], image[x][y], colorChanged);

                if (colorChanged)
                {
                    verticalColorChanges[x].push_back(y);
                }
                while (!verticalColorChanges[x].empty() && verticalColorChanges[x].front() <= y - up[x].length + 1)
                {
                    verticalColorChanges[x].pop_front();
                }

                colorChanges[x] = verticalColorChanges[x].size();
            }
        }

        upPush.clear();
        horizontalColorChanges.clear();
        for (size_t x = 0; x < image.getWidth(); ++x)
        {
            if (x > 0)
            {
                bool colorChanged = false;
                left[x] = update(left[x - 1], image[x - 1][y], image[x][y], colorChanged);

                if (colorChanged)
                {
                    horizontalColorChanges.push_back(x);
                }
                while (!horizontalColorChanges.empty() && horizontalColorChanges.front() <= x - left[x].length + 1)
                {
                    horizontalColorChanges.pop_front();
                }

                colorChanges[x] += horizontalColorChanges.size();
            }
            else
            {
                left[0] = GradientDescription<ImageType>();
            }
            leftPush[x].setPos(y - up[x].length + 1);
            leftPush[x].add(y, left[x].length);

            upPush.add(x, up[x].length);
            auto& upPushMin = upPush.getMin();

            auto leftUpPushBound = upPushMin.pos == x ? 0 : upPushMin.pos + 1;
            auto leftPushBound = x - leftPush[x].getMin().value + 1;
            leftBound[x] = std::max(leftUpPushBound, leftPushBound);
        }

        GradientDescription<ImageType> right;
        upPush.clear();
        horizontalColorChanges.clear();
        for (size_t x = image.getWidth(); x-- > 0;)
        {
            if (x + 1 < image.getWidth())
            {
                bool colorChanged = false;
                right = update(right, image[x + 1][y], image[x][y], colorChanged);

                if (colorChanged)
                {
                    horizontalColorChanges.push_back(x);
                }
                while (!horizontalColorChanges.empty() && horizontalColorChanges.front() >= x + right.length - 1)
                {
                    horizontalColorChanges.pop_front();
                }

                colorChanges[x] += horizontalColorChanges.size();
            }
            rightPush[x].setPos(y - up[x].length + 1);
            //bool valid = true;
            /*if (left[x].currentWidth != left[x].length && right.currentWidth != right.length)
            {
                if (left[x].width != right.width || left[x].diff != right.diff)
                    valid = false;

                if (left[x].currentWidth + right.currentWidth == right.width && left[x + 1].currentWidth < left[x].currentWidth)
                    valid = false;
                else if (left[x].currentWidth == right.width && right.currentWidth == right.width && left[x + 1].length <= left[x].length)
                    valid = false;
            }
            else if (left[x].currentWidth != left[x].length)
            {

            }
            else if (right.currentWidth != right.length)
            {

            }*/

            rightPush[x].add(y, right.length);

            upPush.add(x, up[x].length);
            auto& upPushMin = upPush.getMin();

            auto rightUpPushBound = upPushMin.pos == x ? image.getWidth() - 1 : upPushMin.pos - 1;
            auto rightPushBound = x + rightPush[x].getMin().value - 1;
            rightBound[x] = std::min(rightUpPushBound, rightPushBound);
        }

        for (size_t x = 0; x < image.getWidth(); ++x)
        {
            ans[x][y] = {leftBound[x], rightBound[x], y - up[x].length + 1, y};
            if (bestAns.area() < ans[x][y].area() && colorChanges[x] > 3)
            {
                bestAns = ans[x][y];
            }
        }
    }

    return bestAns;
}

}

#endif // __GRADIENT_FINDER_ALGORITHM_H__
