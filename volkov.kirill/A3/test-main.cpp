#define BOOST_TEST_MODULE A3
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include <circle.hpp>
#include <rectangle.hpp>
#include <composite-shape.hpp>

BOOST_AUTO_TEST_SUITE(testCompositeShape)

const double accuracy = 0.01;

BOOST_AUTO_TEST_CASE(testCompositeShapeCopyConstructor)
{
  volkov::Shape::shape_ptr testRectangle = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {2, 2}, 2, 3 }));
  volkov::Shape::shape_ptr testCircle = std::make_shared<volkov::Circle>(volkov::Circle({ 1, 1 }, 1));

  volkov::CompositeShape testComposition(testRectangle);
  testComposition.add(testCircle);

  const volkov::rectangle_t initialComposition = testComposition.getFrameRect();
  const double initialArea = testComposition.getArea();

  volkov::CompositeShape copyComposition(testComposition);

  BOOST_CHECK_CLOSE(initialComposition.pos.x, copyComposition.getFrameRect().pos.x, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.pos.y, copyComposition.getFrameRect().pos.y, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.width, copyComposition.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.height, copyComposition.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(initialArea, copyComposition.getArea(), accuracy);
  BOOST_CHECK_EQUAL(testComposition.getSize(), copyComposition.getSize());
}

BOOST_AUTO_TEST_CASE(testCompositeShapeMoveConstructor)
{
  volkov::Shape::shape_ptr testRectangle = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {2, 2}, 2, 3 }));
  volkov::Shape::shape_ptr testCircle = std::make_shared<volkov::Circle>(volkov::Circle({ 1, 1 }, 1));
  volkov::CompositeShape testComposition(testRectangle);
  testComposition.add(testCircle);

  const volkov::rectangle_t initialComposition = testComposition.getFrameRect();
  const double initialArea = testComposition.getArea();
  const size_t initialSize = testComposition.getSize();

  volkov::CompositeShape moveComposition(std::move(testComposition));

  BOOST_CHECK_CLOSE(initialComposition.pos.x, moveComposition.getFrameRect().pos.x, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.pos.y, moveComposition.getFrameRect().pos.y, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.width, moveComposition.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.height, moveComposition.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(initialArea, moveComposition.getArea(), accuracy);
  BOOST_CHECK_EQUAL(initialSize, moveComposition.getSize());
  BOOST_CHECK_CLOSE(testComposition.getArea(), 0, accuracy);
  BOOST_CHECK_EQUAL(testComposition.getSize(), 0);
}

BOOST_AUTO_TEST_CASE(testCompositeShapeCopyOperator)
{
  volkov::Shape::shape_ptr testRectangle = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {2, 2}, 2, 3 }));
  volkov::Shape::shape_ptr testCircle = std::make_shared<volkov::Circle>(volkov::Circle({ 1, 1 }, 1));
  volkov::CompositeShape testComposition(testRectangle);
  testComposition.add(testCircle);

  const volkov::rectangle_t initialComposition = testComposition.getFrameRect();
  const double initialArea = testComposition.getArea();

  volkov::CompositeShape copyComposition;
  copyComposition = testComposition;

  BOOST_CHECK_CLOSE(initialComposition.pos.x, copyComposition.getFrameRect().pos.x, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.pos.y, copyComposition.getFrameRect().pos.y, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.width, copyComposition.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.height, copyComposition.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(initialArea, copyComposition.getArea(), accuracy);
  BOOST_CHECK_EQUAL(testComposition.getSize(), copyComposition.getSize());
}

BOOST_AUTO_TEST_CASE(testCompositeShapeMoveOperator)
{
  volkov::Shape::shape_ptr testRectangle = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {2, 2}, 2, 3 }));
  volkov::Shape::shape_ptr testCircle = std::make_shared<volkov::Circle>(volkov::Circle({ 1, 1 }, 1));
  volkov::CompositeShape testComposition(testRectangle);
  testComposition.add(testCircle);

  const volkov::rectangle_t initialComposition = testComposition.getFrameRect();
  const double initialArea = testComposition.getArea();
  const size_t initialSize = testComposition.getSize();

  volkov::CompositeShape moveComposition;
  moveComposition = std::move(testComposition);

  BOOST_CHECK_CLOSE(initialComposition.pos.x, moveComposition.getFrameRect().pos.x, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.pos.y, moveComposition.getFrameRect().pos.y, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.width, moveComposition.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.height, moveComposition.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(initialArea, moveComposition.getArea(), accuracy);
  BOOST_CHECK_EQUAL(initialSize, moveComposition.getSize());
  BOOST_CHECK_CLOSE(testComposition.getArea(), 0, accuracy);
  BOOST_CHECK_EQUAL(testComposition.getSize(), 0);
}

BOOST_AUTO_TEST_CASE(constCompositeShapeAfterMovingByIncrements)
{
  volkov::Shape::shape_ptr testRectangle = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {2, 2}, 2, 3 }));
  volkov::Shape::shape_ptr testCircle = std::make_shared<volkov::Circle>(volkov::Circle({ 1, 1 }, 1));
  volkov::CompositeShape testComposition(testRectangle);
  testComposition.add(testCircle);

  const volkov::rectangle_t initialComposition = testComposition.getFrameRect();
  const double initialArea = testComposition.getArea();

  testComposition.move(2, 3);

  BOOST_CHECK_CLOSE(initialComposition.width, testComposition.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.height, testComposition.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(initialArea, testComposition.getArea(), accuracy);
}

BOOST_AUTO_TEST_CASE(constCompositeShapeAfterMovingToPoint)
{
  volkov::Shape::shape_ptr testRectangle = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {2, 2}, 2, 3 }));
  volkov::Shape::shape_ptr testCircle = std::make_shared<volkov::Circle>(volkov::Circle({ 1, 1 }, 1));
  volkov::CompositeShape testComposition(testRectangle);
  testComposition.add(testCircle);

  const volkov::rectangle_t initialComposition = testComposition.getFrameRect();
  const double initialArea = testComposition.getArea();

  testComposition.move({ 5, 10 });

  BOOST_CHECK_CLOSE(initialComposition.width, testComposition.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(initialComposition.height, testComposition.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(initialArea, testComposition.getArea(), accuracy);
}

BOOST_AUTO_TEST_CASE(quadraticChangeCompositeShapeAreaAfterScaling)
{
  volkov::Shape::shape_ptr testRectangle = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {2, 2}, 2, 3 }));
  volkov::Shape::shape_ptr testCircle = std::make_shared<volkov::Circle>(volkov::Circle({ 1, 1 }, 1));
  volkov::CompositeShape testComposition(testRectangle);
  testComposition.add(testCircle);

  const double zoomFactor_1 = 2;
  const double zoomFactor_2 = 0.5;
  double initialArea = testComposition.getArea();

  testComposition.scale(zoomFactor_1);

  BOOST_CHECK_CLOSE(testComposition.getArea(), initialArea * zoomFactor_1 * zoomFactor_1, accuracy);

  initialArea = testComposition.getArea();

  testComposition.scale(zoomFactor_2);

  BOOST_CHECK_CLOSE(testComposition.getArea(), initialArea * zoomFactor_2 * zoomFactor_2, accuracy);
}

BOOST_AUTO_TEST_CASE(changeCompositeShapeAreaAfterAddingShape)
{
  volkov::Shape::shape_ptr testRectangle_1 = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {2, 2}, 2, 3 }));
  volkov::Shape::shape_ptr testCircle = std::make_shared<volkov::Circle>(volkov::Circle({ 1, 1 }, 1));
  volkov::Shape::shape_ptr testRectangle_2 = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {4, 4}, 4, 6 }));
  volkov::CompositeShape testComposition(testRectangle_1);
  testComposition.add(testCircle);

  const double initialArea = testComposition.getArea();

  testComposition.add(testRectangle_2);

  BOOST_CHECK_CLOSE(testComposition.getArea(), initialArea + testRectangle_2->getArea(), accuracy);
}

BOOST_AUTO_TEST_CASE(changeCompositeShapeAreaAfterDeletingShape)
{
  volkov::Shape::shape_ptr testRectangle_1 = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {2, 2}, 2, 3 }));
  volkov::Shape::shape_ptr testCircle = std::make_shared<volkov::Circle>(volkov::Circle({ 1, 1 }, 1));
  volkov::Shape::shape_ptr testRectangle_2 = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {4, 4}, 4, 6 }));
  volkov::CompositeShape testComposition(testRectangle_1);
  testComposition.add(testCircle);
  testComposition.add(testRectangle_2);

  const double initialArea = testComposition.getArea();

  testComposition.remove(1);

  BOOST_CHECK_CLOSE(testComposition.getArea(), initialArea - testCircle->getArea(), accuracy);
}

BOOST_AUTO_TEST_CASE(invalidCompositeShapeParameteres)
{
  volkov::CompositeShape testComposition;

  BOOST_CHECK_THROW(testComposition.getFrameRect(), std::logic_error);
  BOOST_CHECK_THROW(testComposition.scale(2), std::logic_error);

  volkov::Shape::shape_ptr testRectangle = std::make_shared<volkov::Rectangle>(volkov::Rectangle({ {2, 2}, 2, 3 }));
  volkov::Shape::shape_ptr testCircle = std::make_shared<volkov::Circle>(volkov::Circle({ 1, 1 }, 1));
  testComposition.add(testRectangle);
  testComposition.add(testCircle);

  BOOST_CHECK_THROW(testComposition.at(4), std::invalid_argument);
  BOOST_CHECK_THROW(testComposition.scale(-2), std::invalid_argument);
  BOOST_CHECK_THROW(testComposition.remove(4), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
