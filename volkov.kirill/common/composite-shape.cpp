#include <stdexcept>
#include "composite-shape.hpp"

volkov::CompositeShape::CompositeShape():
  count_(0),
  shapeArr_(nullptr)
{}

volkov::CompositeShape::CompositeShape(const CompositeShape& source):
  count_(source.count_),
  shapeArr_(new Shape* [source.count_])
{
  for (size_t i = 0; i < count_; i++)
  {
    shapeArr_[i] = source.shapeArr_[i];
  }
}

volkov::CompositeShape::CompositeShape(CompositeShape&& source):
  count_(source.count_),
  shapeArr_(source.shapeArr_)
{
  source.count_ = 0;
  source.shapeArr_ = nullptr;
}

volkov::CompositeShape::CompositeShape(Shape& shape):
  count_(1),
  shapeArr_(new Shape* [1])
{
  shapeArr_[0] = &shape;
}

volkov::CompositeShape::~CompositeShape()
{
  delete[] shapeArr_;
}

volkov::CompositeShape& volkov::CompositeShape::operator =(const CompositeShape& rhs)
{
  if (this != &rhs)
  {
    Shape** shapes = new Shape * [rhs.count_];
    delete[] shapeArr_;
    count_ = rhs.count_;
    shapeArr_ = shapes;

    for (size_t i = 0; i < count_; i++)
    {
      shapeArr_[i] = rhs.shapeArr_[i];
    }
  }

  return *this;
}

volkov::CompositeShape& volkov::CompositeShape::operator =(CompositeShape&& rhs)
{
  if (this != &rhs)
  {
    delete[] shapeArr_;
    count_ = rhs.count_;
    shapeArr_ = rhs.shapeArr_;
    rhs.count_ = 0;
    rhs.shapeArr_ = nullptr;
  }

  return *this;
}

volkov::Shape& volkov::CompositeShape::operator [](size_t index) const
{
  if (index >= count_)
  {
    throw std::invalid_argument("Invalid index");
  }

  return *shapeArr_[index];
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

volkov::rectangle_t volkov::CompositeShape::getFrameRect() const
{
  if (count_ == 0)
  {
    throw std::logic_error("Object doesn't exist");
  }

  rectangle_t rect = shapeArr_[0]->getFrameRect();
  double maxY = rect.pos.y + rect.height / 2;
  double minY = rect.pos.y - rect.height / 2;
  double maxX = rect.pos.x + rect.width / 2;
  double minX = rect.pos.x - rect.width / 2;

  for (size_t i = 1; i < count_; i++)
  {
    rect = shapeArr_[i]->getFrameRect();
    maxY = std::max(maxY, rect.pos.y + rect.height / 2);
    minY = std::min(minY, rect.pos.y - rect.height / 2);
    maxX = std::max(maxX, rect.pos.x + rect.width / 2);
    minX = std::min(minX, rect.pos.x - rect.width / 2);
  }

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

void volkov::CompositeShape::add(Shape& shape)
{
  Shape** shapes = new Shape * [count_ + 1];

  for (size_t i = 0; i < count_; i++)
  {
    shapes[i] = shapeArr_[i];
  }

  shapes[count_] = &shape;
  count_++;
  delete[] shapeArr_;
  shapeArr_ = shapes;
}

void volkov::CompositeShape::remove(size_t index)
{
  if (index < 0 || index >= count_)
  {
    throw std::out_of_range("Invalid index");
  }

  for (size_t i = index; i < (count_ - 1); i++)
  {
    shapeArr_[i] = shapeArr_[i + 1];
  }
  count_--;
}
