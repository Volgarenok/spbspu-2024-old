#include <iostream>
#include "base-types.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

void printArea(const Shape& shape)
{
  std::cout << "Area is " << shape.getArea() << "\n";
}

void printFrameRect(const Shape& shape)
{
  rectangle_t frameRect = shape.getFrameRect();
  std::cout << "Center is " << '('
    << frameRect.pos.x << ", " << frameRect.pos.y << ')'
    << ", Height is " << frameRect.height
    << ", Width is " << frameRect.width << "\n\n";
}

int main()
{
  std::cout << "In rectangle with centre (1, 2), height = 3, width = 4\n";
  Rectangle rectangle({ {1, 2}, 3, 4 });
  printArea(rectangle);
  printFrameRect(rectangle);

  std::cout << "Circle center  is (5, 6), radiius = 7\n";
  Circle circle({ 5, 6 }, 7);
  printArea(circle);
  printFrameRect(circle);

  std::cout << "Move circle by (dx = 8 and dy = 9)\n";
  circle.move(8, 9);
  printArea(circle);
  printFrameRect(circle);

  std::cout << "Move rectangle to the point (10, 11)\n";
  rectangle.move({ 10, 11 });
  printArea(rectangle);
  printFrameRect(rectangle);
  return 0;
}
