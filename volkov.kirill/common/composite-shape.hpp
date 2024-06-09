#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP
#include <cstddef>
#include "shape.hpp"

namespace volkov
{

  class CompositeShape final: public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape& source);
    CompositeShape(CompositeShape&& source) noexcept;
    CompositeShape(shape_ptr shape);
    ~CompositeShape() = default;

    CompositeShape& operator=(const CompositeShape& rhs);
    CompositeShape& operator=(CompositeShape&& rhs) noexcept;
    const shape_ptr operator[](size_t index) const;
    const shape_ptr at(size_t index) const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& newPos) override;
    void move(double dx, double dy) override;
    size_t getSize() const;
    void add(shape_ptr shape);
    void remove(size_t index);

  protected:
    void doScale(double factor) override;

  private:
    size_t count_;
    shape_array shapeArr_;
  };
}

#endif
