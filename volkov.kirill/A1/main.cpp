#include <iostream>
#include "base-types.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

void printFrameRect(const Shape &shape, std::ostream& out)
{
  rectangle_t frameRect = shape.getFrameRect();
  out << "Center is " << '(' << frameRect.pos.x << ", " << frameRect.pos.y << ')'
      << ", Height is " << frameRect.height
      << ", Width is " << frameRect.width << "\n\n";
}

int main()
{
  try
  {
    Rectangle rectangle({ {1, 2}, 3, 4 });
    Circle circle({ 5, 6 }, 7);
    Shape* shapes[] = { &rectangle, &circle };

    for (Shape* shape : shapes)
    {
      std::cout << typeid(*shape).name() << "\n";
      std::cout << "Area: " << shape->getArea() << "\n";
      printFrameRect(*shape, std::cout);

      shape->move(8, 9);
      std::cout << "Move by (dx = 8 and dy = 9)\n";
      printFrameRect(*shape, std::cout);
      
      shape->move({ 10, 11 });
      std::cout << "Move to the point (10, 11)\n";
      printFrameRect(*shape, std::cout);
    }
  }
  catch(const std::invalid_argument& e)
  {
    std::cerr << "Error: " << e.what() << "\n\n";
  }
  return 0;
}
