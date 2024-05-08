#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

class Rectangle final: public Shape
{
public:
  Rectangle(const point_t &center, double height, double width);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &newPos) override;
  void move(double dx, double dy) override;

private:
  point_t center_;
  double height_;
  double width_;
};

#endif
