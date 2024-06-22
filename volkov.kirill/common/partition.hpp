#ifndef PARTITION_HPP
#define PARTITION_HPP

#include "composite-shape.hpp"
#include "matrix.hpp"

namespace volkov
{
  Matrix part(const volkov::Shape::shape_array array, size_t size);
  Matrix part(const CompositeShape &composite);

  bool isOverlap(const volkov::Shape::shape_ptr &firstShape, const volkov::Shape::shape_ptr &secondShape);
}

#endif
