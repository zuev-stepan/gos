#pragma once

#ifndef GRADIENT_FINDER_IMAGE_H
#define GRADIENT_FINDER_IMAGE_H

namespace gradient_finder
{

template <typename MatrixReferenceType, typename CellReferenceType>
class ColumnAccessor
{
public:
    ColumnAccessor(MatrixReferenceType rMatrix, size_t x)
        : m_rMatrix(rMatrix), m_x(x)
    { }

    CellReferenceType operator[](size_t y) const
    {
        assert(y < m_rMatrix.getHeight());
        return m_rMatrix.get(m_x, y);
    }

private:
    MatrixReferenceType m_rMatrix;
    size_t m_x;
};

}

#endif // GRADIENT_FINDER_IMAGE_H
