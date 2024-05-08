#define BOOST_TEST_MODULE A2
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(testShape)

const double accuracy = 0.01;

BOOST_AUTO_TEST_CASE(testRectParameters)
{
  BOOST_CHECK_THROW(volkov::Rectangle({ 4, -3 }, -2, 1), std::invalid_argument);
  BOOST_CHECK_THROW(volkov::Rectangle({ 4, -3 }, 2, -1), std::invalid_argument);
  volkov::Rectangle testRect({ 1, -2 }, 3, 4);
  BOOST_CHECK_THROW(testRect.scale(-3), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testRectAfterMoving)
{
  volkov::Rectangle testRect({ 1, 2 }, 3, 4);
  const double areaBeforeMoving = testRect.getArea();
  const volkov::rectangle_t sideBeforeMoving = testRect.getFrameRect();

  testRect.move({ 10, 11 });
  double areaAfterMoving = testRect.getArea();
  volkov::rectangle_t sideAfterMoving = testRect.getFrameRect();
  BOOST_CHECK_CLOSE(areaBeforeMoving, areaAfterMoving, accuracy);
  BOOST_CHECK_CLOSE(sideBeforeMoving.width, sideAfterMoving.width, accuracy);
  BOOST_CHECK_CLOSE(sideBeforeMoving.height, sideAfterMoving.height, accuracy);

  testRect.move(10, 11);
  areaAfterMoving = testRect.getArea();
  sideAfterMoving = testRect.getFrameRect();
  BOOST_CHECK_CLOSE(areaBeforeMoving, areaAfterMoving, accuracy);
  BOOST_CHECK_CLOSE(sideBeforeMoving.width, sideAfterMoving.width, accuracy);
  BOOST_CHECK_CLOSE(sideBeforeMoving.height, sideAfterMoving.height, accuracy);
}

BOOST_AUTO_TEST_CASE(testRectScaling)
{
  volkov::Rectangle testRect({ 1, 2 }, 3, 4);
  const double areaBeforeScaling = testRect.getArea();

  const double coef = 3;
  testRect.scale(coef);
  const double areaAfterScaling = testRect.getArea();
  BOOST_CHECK_CLOSE(areaBeforeScaling * coef * coef, areaAfterScaling, accuracy);
}

BOOST_AUTO_TEST_CASE(testCircleParameters)
{
  BOOST_CHECK_THROW(volkov::Circle({ -7, 6 }, -5), std::invalid_argument);
  volkov::Circle testCircle({ -7, 6 }, 5);
  BOOST_CHECK_THROW(testCircle.scale(-2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testCircleAfterMoving)
{
  volkov::Circle testCircle({ 5, 6 }, 7);
  const double areaBeforeMoving = testCircle.getArea();
  const volkov::rectangle_t sideBeforeMoving = testCircle.getFrameRect();

  testCircle.move({ 8, 9 });
  double areaAfterMoving = testCircle.getArea();
  volkov::rectangle_t sideAfterMoving = testCircle.getFrameRect();
  BOOST_CHECK_CLOSE(areaBeforeMoving, areaAfterMoving, accuracy);
  BOOST_CHECK_CLOSE(sideBeforeMoving.width, sideAfterMoving.width, accuracy);
  BOOST_CHECK_CLOSE(sideBeforeMoving.height, sideAfterMoving.height, accuracy);

  testCircle.move(8, 9);
  areaAfterMoving = testCircle.getArea();
  sideAfterMoving = testCircle.getFrameRect();
  BOOST_CHECK_CLOSE(areaBeforeMoving, areaAfterMoving, accuracy);
  BOOST_CHECK_CLOSE(sideBeforeMoving.width, sideAfterMoving.width, accuracy);
  BOOST_CHECK_CLOSE(sideBeforeMoving.height, sideAfterMoving.height, accuracy);
}

BOOST_AUTO_TEST_CASE(testCircleScaling)
{
  volkov::Circle testCircle({ 5, 6 }, 7);
  const double areaBeforeScaling = testCircle.getArea();

  const double coef = 2;
  testCircle.scale(2);
  const double areaAfterScaling = testCircle.getArea();

  BOOST_CHECK_CLOSE(areaBeforeScaling * coef * coef, areaAfterScaling, accuracy);
}

BOOST_AUTO_TEST_SUITE_END()
