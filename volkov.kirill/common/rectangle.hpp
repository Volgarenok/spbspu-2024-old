#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace volkov
{
  class Rectangle final: public Shape
  {
  public:
    Rectangle(const point_t& center, double height, double width);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& newPos) override;
    void move(double dx, double dy) override;
    void rotate(double angle) override;

  protected:
    void doScale(double factor) override;

  private:
    point_t center_;
    double height_;
    double width_;
    double angle_;
  };
}

#endif
