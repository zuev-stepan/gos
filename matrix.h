#pragma once

#ifndef GRADIENT_FINDER_MATRIX_H
#define GRADIENT_FINDER_MATRIX_H

#include "color.h"
#include "column_accessor.h"

namespace gradient_finder
{

template <typename CellType>
class Matrix
{
public:
    using Cell = CellType;

public:
    Matrix(size_t width, size_t height)
        : m_width(width), m_height(height), m_cells(width * height)
    { }

    const CellType& get(size_t x, size_t y) const
    {
        assert(x < m_width && y < m_height);

        return m_cells[y * m_width + x];
    }

    CellType& get(size_t x, size_t y)
    {
        assert(x < m_width && y < m_height);

        return m_cells[y * m_width + x];
    }

    ColumnAccessor<Matrix&, CellType&> operator[](size_t columnIdx)
    {
        return {*this, columnIdx};
    }

    ColumnAccessor<const Matrix&, const CellType&> operator[](size_t columnIdx) const
    {
        return {*this, columnIdx};
    }

    size_t getWidth() const
    {
        return m_width;
    }

    size_t getHeight() const
    {
        return m_height;
    }

    char* bytes()
    {
        return reinterpret_cast<char*>(m_cells.data());
    }

    unsigned char* ubytes()
    {
        return reinterpret_cast<unsigned char*>(m_cells.data());
    }

private:
    size_t m_width, m_height;
    std::vector<CellType> m_cells;
};

using GrayscaleImage = Matrix<Gray>;
using RGBImageType = Matrix<Color>;

}

#endif // GRADIENT_FINDER_MATRIX_H
