#include <iostream>
#include <base-types.hpp>
#include <circle.hpp>
#include <rectangle.hpp>
#include <composite-shape.hpp>

void printFrameRect(const volkov::Shape &shape, std::ostream& out)
{
  volkov::rectangle_t frameRect = shape.getFrameRect();
  out << frameRect.pos.x << ' ' << frameRect.pos.y << ' '
      << frameRect.height << ' '
      << frameRect.width << ' ';
}

int main()
{
  try
  {
    volkov::Rectangle rectangle({ {1, 2}, 3, 4 });
    volkov::Circle circle({ 5, 6 }, 7);

    volkov::CompositeShape shape;
    shape.add(rectangle);
    std::cout << shape.getArea() << "\n";
    printFrameRect(shape, std::cout);
    std::cout << "\n\n";

    shape.add(circle);
    std::cout << shape.getArea() << "\n";
    printFrameRect(shape, std::cout);
    std::cout << "\n\n";

    shape.move({ 1, 2 });
    std::cout << shape.getArea() << "\n";
    printFrameRect(shape, std::cout);
    std::cout << "\n\n";

    shape.move(4, 3);
    std::cout << shape.getArea() << "\n";
    printFrameRect(shape, std::cout);
    std::cout << "\n\n";

    shape.scale(2);
    std::cout << shape.getArea() << "\n";
    printFrameRect(shape, std::cout);
    std::cout << "\n\n";

    shape.remove(1);
    std::cout << shape.getArea() << "\n";
    printFrameRect(shape, std::cout);
    std::cout << "\n\n";
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << "Error: " << e.what() << "\n\n";
  }
  return 0;
}
