#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace volkov
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    point_t pos;
    double height;
    double width;
  };

  constexpr double PI = 3.141592;
}

#endif
