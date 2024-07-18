#include <stdexcept>
#include "matrix.hpp"

volkov::Matrix::Matrix():
  rows_(0),
  columns_(0)
{}

volkov::Matrix::Matrix(const Matrix &source):
  rows_(source.rows_),
  columns_(source.columns_),
  list_(std::make_unique<volkov::Shape::shape_ptr[]>(source.rows_ * source.columns_))
{
  for (size_t i = 0; i < (rows_ * columns_); i++)
  {
    list_[i] = source.list_[i];
  }
}

volkov::Matrix::Matrix(Matrix &&source) noexcept:
  rows_(source.rows_),
  columns_(source.columns_),
  list_(std::move(source.list_))
{
  source.rows_ = 0;
  source.columns_ = 0;
}

volkov::Matrix & volkov::Matrix::operator=(const Matrix &rhs)
{
  using Shape_array = volkov::Shape::shape_array;
  using Shape_ptr = volkov::Shape::shape_ptr;

  if (this != &rhs)
  {
    Shape_array shapes(std::make_unique<Shape_ptr[]>(rhs.rows_ * rhs.columns_));
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;

    for (size_t i = 0; i < (rows_ * columns_); i++)
    {
      shapes[i] = rhs.list_[i];
    }

    list_.swap(shapes);
  }

  return *this;
}

volkov::Matrix & volkov::Matrix::operator=(Matrix &&rhs) noexcept
{
  if (this != &rhs)
  {
    rows_ = rhs.rows_;
    columns_ = rhs.columns_;
    list_ = std::move(rhs.list_);
    rhs.rows_ = 0;
    rhs.columns_ = 0;
    rhs.list_ = nullptr;
  }

  return *this;
}

const volkov::Shape::shape_ptr volkov::Matrix::at(size_t row, rsize_t column) const
{
  if (row >= rows_ || column >= columns_)
  {
    throw std::out_of_range("Invalid index");
  }

  return list_[row * columns_ + column];
}

const volkov::Shape::shape_ptr volkov::Matrix::unsafe_at(size_t row, rsize_t column) const
{
  return list_[row * columns_ + column];
}

bool volkov::Matrix::operator==(const Matrix &rhs) const
{
  if ((rows_ != rhs.rows_) || (columns_ != rhs.columns_))
  {
    return false;
  }

  for (size_t i = 0; i < (rows_ * columns_); i++)
  {
    if (list_[i] != rhs.list_[i])
    {
      return false;
    }
  }

  return true;
}

bool volkov::Matrix::operator!=(const Matrix &rhs) const
{
  return !(*this == rhs);
}

size_t volkov::Matrix::getRows() const
{
  return rows_;
}

size_t volkov::Matrix::getColumns() const
{
  return columns_;
}

size_t volkov::Matrix::getLayerSize(size_t layer) const
{
  if (layer >= rows_)
  {
    return 0;
  }

  for (size_t i = 0; i < columns_; i++)
  {
    if (list_[layer * columns_ + i] == nullptr)
    {
      return i;
    }
  }

  return columns_;
}

void volkov::Matrix::add(volkov::Shape::shape_ptr shape, size_t row, size_t column)
{
  using Shape_array = volkov::Shape::shape_array;
  using Shape_ptr = volkov::Shape::shape_ptr;

  if ((row > rows_) || (column > columns_))
  {
    throw std::out_of_range("Invalid indexes");
  }

  size_t rows = (row == rows_) ? (rows_ + 1) : rows_;
  size_t columns = (column == columns_) ? (columns_ + 1) : columns_;

  Shape_array shapes(std::make_unique<Shape_ptr[]>(rows * columns));

  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < columns; j++)
    {
      if ((i == rows_) || (j == columns_))
      {
        shapes[i * columns + j] = nullptr;
      }
      else
      {
        shapes[i * columns + j] = list_[i * columns_ + j];
      }
    }
  }

  shapes[row * columns + column] = shape;
  list_.swap(shapes);
  rows_ = rows;
  columns_ = columns;
}
