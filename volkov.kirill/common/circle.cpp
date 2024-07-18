#include <stdexcept>
#include "circle.hpp"

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

void volkov::Circle::doScale(double factor)
{
  radius_ *= factor;
}

void volkov::Circle::rotate(double)
{}
