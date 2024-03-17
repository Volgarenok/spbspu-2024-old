#include "circle.hpp"
#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>

Circle::Circle(const point_t &pos, double radius) :
  center_(pos),
  radius_(radius)
{
  assert(radius_ >= 0.0);
}

double Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
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

point_t Circle::getPos() const
{
  return center_;
};
