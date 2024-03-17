#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t &/*center*/, double /*height*/, double /*width*/);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &newPos);
  void move(double dx, double dy) override;
  point_t getPos() const override;

private:
  point_t center_;
  double height_;
  double width_;
};

#endif // !RECTANGLE_HPP
