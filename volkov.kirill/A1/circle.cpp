#include "circle.hpp"
#include <stdexcept>
#include <cmath>

const double PI = 3.141592;

Circle::Circle(const point_t &pos, double radius):
  center_(pos),
  radius_(radius)
{
  if (radius_ <= 0.0)
  {
    throw std::invalid_argument("Circle radius must be greater than zero");
  }
}

double Circle::getArea() const
{
  return (PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const
{
  return { center_, radius_ * 2, radius_ * 2 };
}

void Circle::move(const point_t &newPos)
{
  center_ = newPos;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
