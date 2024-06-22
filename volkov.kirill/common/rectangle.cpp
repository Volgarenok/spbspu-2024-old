#include <cmath>
#include <stdexcept>
#include "rectangle.hpp"

constexpr double FULLROTATION = 360.0;

volkov::Rectangle::Rectangle(const point_t &pos, double height, double width):
  center_(pos),
  height_(height),
  width_(width),
  angle_(0)
{
  if (height_ <= 0.0 || width_ <= 0.0)
  {
    throw std::invalid_argument("Rectangle dimensions must be greater than zero");
  }
}

double volkov::Rectangle::getArea() const
{
  return (height_ * width_);
}

volkov::rectangle_t volkov::Rectangle::getFrameRect() const
{
  const double radian = angle_ * PI / 180;
  const double sinA = std::sin(radian);
  const double cosA = std::cos(radian);
  const double height = fabs(sinA) * width_ + fabs(cosA) * height_;
  const double width = fabs(sinA) * height_ + fabs(cosA) * width_;
  return { center_, height, width };
}

void volkov::Rectangle::move(const point_t &newPos)
{
  center_ = newPos;
}

void volkov::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void volkov::Rectangle::doScale(double factor)
{
  width_ *= factor;
  height_ *= factor;
}

void volkov::Rectangle::rotate(double angle)
{
  angle_ += angle;
  while (angle_ >= FULLROTATION)
  {
    angle_ -= FULLROTATION;
  }
  while (angle_ < 0.0)
  {
    angle_ += FULLROTATION;
  }
}
