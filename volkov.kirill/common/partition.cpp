#include <cmath>
#include "partition.hpp"

volkov::Matrix volkov::part(const volkov::Shape::shape_array array, size_t size)
{
  Matrix matrix;
  size_t rows = 0;
  size_t columns = 0;

  for (size_t i = 0; i < size; i++)
  {
     for (size_t j = 0; j < matrix.getRows(); j++)
    {
      for (size_t k = 0; k < matrix.getColumns(); k++)
      {
        if (matrix.at(j, k) == nullptr)
        {
          rows = j;
          columns = k;
          break;
        }

        if (isOverlap(array[i], matrix.at(j, k)))
        {
          rows = j + 1;
          columns = 0;
          break;
        }
        else
        {
          rows = j;
          columns = k + 1;
        }
      }

      if (rows == j)
      {
        break;
      }
    }

    matrix.add(array[i], rows, columns);
  }

  return matrix;
}

volkov::Matrix volkov::part(const CompositeShape &composite)
{
  return part(composite.getShapes(), composite.getSize());
}

bool volkov::isOverlap(const volkov::Shape::shape_ptr &firstShape, const volkov::Shape::shape_ptr &secondShape)
{
  const double centerDistanceX = fabs(firstShape->getFrameRect().pos.x - secondShape->getFrameRect().pos.x);
  const double centerDistanceY = fabs(firstShape->getFrameRect().pos.y - secondShape->getFrameRect().pos.y);
  const double totalWidth = (firstShape->getFrameRect().width + secondShape->getFrameRect().width) / 2;
  const double totalHeight = (firstShape->getFrameRect().height + secondShape->getFrameRect().height) / 2;

  return (centerDistanceX < totalWidth) && (centerDistanceY < totalHeight);
}
