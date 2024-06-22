#include <algorithm>
#include <cmath>
#include <stdexcept>
#include "composite-shape.hpp"

volkov::CompositeShape::CompositeShape():
  count_(0)
{}

volkov::CompositeShape::CompositeShape(const CompositeShape& source):
  count_(source.count_),
  shapeArr_(std::make_unique<shape_ptr[]>(source.count_))
{
  for (size_t i = 0; i < count_; i++)
  {
    shapeArr_[i] = source.shapeArr_[i];
  }
}

volkov::CompositeShape::CompositeShape(CompositeShape&& source) noexcept:
  count_(source.count_),
  shapeArr_(std::move(source.shapeArr_))
{
  source.count_ = 0;
}

volkov::CompositeShape::CompositeShape(shape_ptr shape):
  count_(1),
  shapeArr_(std::make_unique<shape_ptr[]>(1))
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  shapeArr_[0] = shape;
}

volkov::CompositeShape& volkov::CompositeShape::operator=(const CompositeShape& rhs)
{
  if (this != &rhs)
  {
    count_ = rhs.count_;
    shape_array shapes(std::make_unique<shape_ptr[]>(count_));

    for (size_t i = 0; i < count_; i++)
    {
      shapes[i] = rhs.shapeArr_[i];
    }
    shapeArr_.swap(shapes);
  }

  return *this;
}

volkov::CompositeShape& volkov::CompositeShape::operator=(CompositeShape&& rhs) noexcept
{
  if (this != &rhs)
  {
    count_ = rhs.count_;
    shapeArr_ = std::move(rhs.shapeArr_);
    rhs.count_ = 0;
  }

  return *this;
}

const volkov::Shape::shape_ptr volkov::CompositeShape::operator[](size_t index) const
{
  return shapeArr_[index];
}

const volkov::Shape::shape_ptr volkov::CompositeShape::at(size_t index) const
{
  if (index >= count_)
  {
    throw std::invalid_argument("Invalid index");
  }

  return shapeArr_[index];
}

double volkov::CompositeShape::getArea() const
{
  double compositeArea = 0;

  for (size_t i = 0; i < count_; i++)
  {
    compositeArea += shapeArr_[i]->getArea();
  }

  return compositeArea;
}

bool compareMaxX(const volkov::Shape::shape_ptr a, const volkov::Shape::shape_ptr b)
{
  return (a->getFrameRect().pos.x + a->getFrameRect().width / 2) < (b->getFrameRect().pos.x + b->getFrameRect().width / 2);
}

bool compareMinX(const volkov::Shape::shape_ptr a, const volkov::Shape::shape_ptr b)
{
  return (a->getFrameRect().pos.x - a->getFrameRect().width / 2) < (b->getFrameRect().pos.x - b->getFrameRect().width / 2);
}

bool compareMaxY(const volkov::Shape::shape_ptr a, const volkov::Shape::shape_ptr b)
{
  return (a->getFrameRect().pos.y + a->getFrameRect().height / 2) < (b->getFrameRect().pos.y + b->getFrameRect().height / 2);
}

bool compareMinY(const volkov::Shape::shape_ptr a, const volkov::Shape::shape_ptr b)
{
  return (a->getFrameRect().pos.y - a->getFrameRect().height / 2) < (b->getFrameRect().pos.y - b->getFrameRect().height / 2);
}

volkov::rectangle_t volkov::CompositeShape::getFrameRect() const
{
  if (count_ == 0)
  {
    throw std::logic_error("Object doesn't exist");
  }

  auto minXIter = std::min_element(shapeArr_.get(), shapeArr_.get() + count_, compareMinX);
  auto maxXIter = std::max_element(shapeArr_.get(), shapeArr_.get() + count_, compareMaxX);
  auto minYIter = std::min_element(shapeArr_.get(), shapeArr_.get() + count_, compareMinY);
  auto maxYIter = std::max_element(shapeArr_.get(), shapeArr_.get() + count_, compareMaxY);

  double minX = (*minXIter)->getFrameRect().pos.x - (*minXIter)->getFrameRect().width / 2;
  double maxX = (*maxXIter)->getFrameRect().pos.x + (*maxXIter)->getFrameRect().width / 2;
  double minY = (*minYIter)->getFrameRect().pos.y - (*minYIter)->getFrameRect().height / 2;
  double maxY = (*maxYIter)->getFrameRect().pos.y + (*maxYIter)->getFrameRect().height / 2;

  return rectangle_t{ {(maxX + minX) / 2, (maxY + minY) / 2}, maxX - minX, maxY - minY };
}

void volkov::CompositeShape::move(const point_t& newPos)
{
  const double dx = newPos.x - getFrameRect().pos.x;
  const double dy = newPos.y - getFrameRect().pos.y;

  move(dx, dy);
}

void volkov::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < count_; i++)
  {
    shapeArr_[i]->move(dx, dy);
  }
}

size_t volkov::CompositeShape::getSize() const
{
  return count_;
}

volkov::Shape::shape_array volkov::CompositeShape::getShapes() const
{
  shape_array shapes(std::make_unique<shape_ptr[]>(count_));

  for (size_t i = 0; i < count_; i++)
  {
    shapes[i] = shapeArr_[i];
  }
  return shapes;
}

void volkov::CompositeShape::doScale(double factor)
{
  if (count_ == 0)
  {
    throw std::logic_error("Object doesn't exist");
  }

  point_t center = getFrameRect().pos;

  for (size_t i = 0; i < count_; i++)
  {
    shapeArr_[i]->scale(factor);
    point_t shapeCenter = shapeArr_[i]->getFrameRect().pos;
    shapeArr_[i]->move((shapeCenter.x - center.x) * (factor - 1), (shapeCenter.y - center.y) * (factor - 1));
  }
}

void volkov::CompositeShape::rotate(double angle)
{
  double radians = angle * PI / 180;
  const double sinA = std::sin(radians);
  const double cosA = std::cos(radians);
  const point_t compositeCenter = getFrameRect().pos;
  for (size_t i = 0; i < count_; i++)
  {
    const point_t shapeCenter = shapeArr_[i]->getFrameRect().pos;
    const double dx = shapeCenter.x - compositeCenter.x;
    const double dy = shapeCenter.y - compositeCenter.y;
    const double newX = compositeCenter.x + dx * cosA - dy * sinA;
    const double newY = compositeCenter.y + dx * sinA + dy * cosA;
    shapeArr_[i]->move({ newX, newY});
    shapeArr_[i]->rotate(angle);
  }
}

void volkov::CompositeShape::add(shape_ptr shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }

  shape_array shapes(std::make_unique<shape_ptr[]>(count_ + 1));

  for (size_t i = 0; i < count_; i++)
  {
    shapes[i] = shapeArr_[i];
  }

  shapes[count_] = shape;
  count_++;
  shapeArr_.swap(shapes);
}

void volkov::CompositeShape::remove(size_t index)
{
  if (index >= count_)
  {
    throw std::out_of_range("Invalid index");
  }

  for (size_t i = index; i < (count_ - 1); i++)
  {
    shapeArr_[i] = shapeArr_[i + 1];
  }
  count_--;
}
