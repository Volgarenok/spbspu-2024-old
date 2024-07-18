#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"

namespace volkov
{
  class Matrix
  {
  public:
    Matrix();
    Matrix(const Matrix &source);
    Matrix(Matrix &&source) noexcept;
    ~Matrix() = default;

    Matrix &operator=(const Matrix &rhs);
    Matrix &operator=(Matrix &&rhs) noexcept;
    const Shape::shape_ptr at(size_t row, rsize_t column) const;
    const Shape::shape_ptr unsafe_at(size_t row, rsize_t column) const;
    bool operator==(const Matrix &rhs) const;
    bool operator!=(const Matrix &rhs) const;

    size_t getRows() const;
    size_t getColumns() const;
    size_t getLayerSize(size_t layer) const;
    void add(Shape::shape_ptr shape, size_t row, size_t column);

  private:
    size_t rows_;
    size_t columns_;
    Shape::shape_array list_;
  };
}

#endif
