#include "circle.hpp"
#include <stdexcept>
#include <cmath>

const double PI = 3.141592;

volkov::Circle::Circle(const point_t &pos, double radius):
  center_(pos),
  radius_(radius)
{
  if (radius_ <= 0.0)
  {
    throw std::invalid_argument("Circle radius must be greater than zero");
  }
}

double volkov::Circle::getArea() const
{
  return (PI * radius_ * radius_);
}

volkov::rectangle_t volkov::Circle::getFrameRect() const
{
  return { center_, radius_ * 2, radius_ * 2 };
}

void volkov::Circle::move(const point_t& newPos)
{
  center_ = newPos;
}

void volkov::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void volkov::Circle::scale(double factor)
{
  if (factor > 0.0)
  {
    radius_ *= factor;
  }
  else
  {
    throw std::invalid_argument("Factor cannot be negative");
  }
}
