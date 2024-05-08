#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t &pos, double height, double width):
  center_(pos),
  height_(height),
  width_(width)
{
  if (height_ <= 0.0 || width_ <= 0.0)
  {
    throw std::invalid_argument("Rectangle dimensions must be greater than zero");
  }
}

double Rectangle::getArea() const
{
  return (height_ * width_);
}

rectangle_t Rectangle::getFrameRect() const
{
  return { center_, height_, width_ };
}

void Rectangle::move(const point_t &newPos)
{
  center_ = newPos;
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
