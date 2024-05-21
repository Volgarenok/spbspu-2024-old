#include <stdexcept>
#include "shape.hpp"

void volkov::Shape::scale(double factor)
{
  if (factor > 0.0)
  {
    doScale(factor);
  }
  else
  {
    throw std::invalid_argument("Factor cannot be negative");
  }
}
