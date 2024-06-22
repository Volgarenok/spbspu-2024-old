#include <iostream>
#include <base-types.hpp>
#include <circle.hpp>
#include <rectangle.hpp>
#include <composite-shape.hpp>
#include <matrix.hpp>
#include <partition.hpp>

void printFrameRect(const volkov::CompositeShape& shape, std::ostream& out)
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
    volkov::Shape::shape_ptr rectangle_1 = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {1, 2}, 3, 4 }));
    volkov::Shape::shape_ptr circle_1 = std::make_shared<volkov::Circle>(volkov::Circle({ 5, 6 }, 7));
    volkov::Shape::shape_ptr rectangle_2 = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {5, 6}, 7, 8 }));
    volkov::Shape::shape_ptr circle_2 = std::make_shared<volkov::Circle>(volkov::Circle({ 9, 10 }, 11));

    volkov::CompositeShape shape;
    shape.add(rectangle_1);
    std::cout << shape.getArea() << "\n";
    printFrameRect(shape, std::cout);
    std::cout << "\n\n";

    shape.add(circle_1);
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

    shape.rotate(30);
    std::cout << shape.getArea() << "\n";
    printFrameRect(shape, std::cout);
    std::cout << "\n\n";

    shape.remove(1);
    std::cout << shape.getArea() << "\n";
    printFrameRect(shape, std::cout);
    std::cout << "\n\n";

    shape.add(rectangle_2);
    shape.add(circle_2);

    volkov::Matrix matrix = volkov::part(shape);
    for (size_t i = 0; i < matrix.getRows(); i++)
    {
      for (size_t j = 0; j < matrix.getColumns(); j++)
      {
        if (matrix[i][j] != nullptr)
        {
          std::cout << "Info about shape in matrix["
                    << i << "]["
                    << j << "]" << "\n";
          std::cout << matrix[i][j]->getArea() << "\n";
          volkov::rectangle_t frameRect = matrix[i][j]->getFrameRect();
          std::cout << frameRect.pos.x << ' '
                    << frameRect.pos.y << ' '
                    << frameRect.height << ' '
                    << frameRect.width << "\n\n";
        }
      }
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << "Error: " << e.what() << "\n\n";
  }
  return 0;
}
