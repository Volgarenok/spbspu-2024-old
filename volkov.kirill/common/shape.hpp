#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <memory>
#include "base-types.hpp"

namespace volkov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t&) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;
    void scale(double factor);

    using shape_ptr = std::shared_ptr<Shape>;
    using shape_array = std::unique_ptr<shape_ptr[]>;

  protected:
    virtual void doScale(double factor) = 0;
  };
}

#endif
