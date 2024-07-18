#define BOOST_TEST_MODULE A4
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include <circle.hpp>
#include <rectangle.hpp>
#include <composite-shape.hpp>
#include <matrix.hpp>
#include <partition.hpp>

BOOST_AUTO_TEST_SUITE(testMatrix)

BOOST_AUTO_TEST_CASE(testMatrixCopyConstructor)
{
  volkov::Shape::shape_ptr testRectanglePtr = std::make_shared<volkov::Rectangle>(volkov::point_t{ 2, 2 }, 2, 3);
  volkov::Shape::shape_ptr testCirclePtr = std::make_shared<volkov::Circle>(volkov::point_t{ 1, 1 }, 1);

  volkov::CompositeShape testComposition(testRectanglePtr);
  testComposition.add(testCirclePtr);

  volkov::Matrix testMatrix = part(testComposition);

  volkov::Matrix copyMatrix(testMatrix);

  BOOST_CHECK(testMatrix == copyMatrix);
  BOOST_CHECK_EQUAL(testMatrix.getRows(), copyMatrix.getRows());
  BOOST_CHECK_EQUAL(testMatrix.getColumns(), copyMatrix.getColumns());
}

BOOST_AUTO_TEST_CASE(testMatrixMoveConstructor)
{
  volkov::Shape::shape_ptr testRectanglePtr = std::make_shared<volkov::Rectangle>(volkov::point_t{ 2, 2 }, 2, 3);
  volkov::Shape::shape_ptr testCirclePtr = std::make_shared<volkov::Circle>(volkov::point_t{ 1, 1 }, 1);

  volkov::CompositeShape testComposition(testRectanglePtr);
  testComposition.add(testCirclePtr);

  volkov::Matrix testMatrix = part(testComposition);

  volkov::Matrix copyMatrix(testMatrix);
  volkov::Matrix moveMatrix(std::move(testMatrix));

  BOOST_CHECK(copyMatrix == moveMatrix);
  BOOST_CHECK_EQUAL(copyMatrix.getRows(), moveMatrix.getRows());
  BOOST_CHECK_EQUAL(copyMatrix.getColumns(), moveMatrix.getColumns());
  BOOST_CHECK_EQUAL(testMatrix.getRows(), 0);
  BOOST_CHECK_EQUAL(testMatrix.getColumns(), 0);
}

BOOST_AUTO_TEST_CASE(testMatrixCopyOperator)
{
  volkov::Shape::shape_ptr testRectanglePtr = std::make_shared<volkov::Rectangle>(volkov::point_t{ 2, 2 }, 2, 3);
  volkov::Shape::shape_ptr testCirclePtr = std::make_shared<volkov::Circle>(volkov::point_t{ 1, 1 }, 1);

  volkov::CompositeShape testComposition(testRectanglePtr);
  testComposition.add(testCirclePtr);

  volkov::Matrix testMatrix = part(testComposition);

  volkov::Matrix copyMatrix;
  copyMatrix = testMatrix;

  BOOST_CHECK(testMatrix == copyMatrix);
  BOOST_CHECK_EQUAL(testMatrix.getRows(), copyMatrix.getRows());
  BOOST_CHECK_EQUAL(testMatrix.getColumns(), copyMatrix.getColumns());
}

BOOST_AUTO_TEST_CASE(testMatrixMoveOperator)
{
  volkov::Shape::shape_ptr testRectanglePtr = std::make_shared<volkov::Rectangle>(volkov::point_t{ 2, 2 }, 2, 3);
  volkov::Shape::shape_ptr testCirclePtr = std::make_shared<volkov::Circle>(volkov::point_t{ 1, 1 }, 1);

  volkov::CompositeShape testComposition(testRectanglePtr);
  testComposition.add(testCirclePtr);

  volkov::Matrix testMatrix = part(testComposition);

  volkov::Matrix copyMatrix(testMatrix);
  volkov::Matrix moveMatrix;
  moveMatrix = std::move(testMatrix);

  BOOST_CHECK(copyMatrix == moveMatrix);
  BOOST_CHECK_EQUAL(copyMatrix.getRows(), moveMatrix.getRows());
  BOOST_CHECK_EQUAL(copyMatrix.getColumns(), moveMatrix.getColumns());
  BOOST_CHECK_EQUAL(testMatrix.getRows(), 0);
  BOOST_CHECK_EQUAL(testMatrix.getColumns(), 0);
}

BOOST_AUTO_TEST_CASE(invalidMatrixParameteres)
{
  volkov::Shape::shape_ptr testRectanglePtr = std::make_shared<volkov::Rectangle>(volkov::point_t{ 2, 2 }, 2, 3);
  volkov::Shape::shape_ptr testCirclePtr = std::make_shared<volkov::Circle>(volkov::point_t{ 1, 1 }, 1);

  volkov::CompositeShape testComposition(testRectanglePtr);
  testComposition.add(testCirclePtr);

  volkov::Matrix testMatrix = part(testComposition);

  BOOST_CHECK_THROW(testMatrix.at(10, 1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(testCorrectPartition)
{
  volkov::Shape::shape_ptr testRectangle_1_ptr = std::make_shared<volkov::Rectangle>(volkov::point_t{ 5, 5 }, 1, 1);
  volkov::Shape::shape_ptr testRectangle_2_ptr = std::make_shared<volkov::Rectangle>(volkov::point_t{ 15, 15 }, 1, 1);
  volkov::Shape::shape_ptr testCircle_1_ptr = std::make_shared<volkov::Circle>(volkov::point_t{ 4, 5 }, 3);
  volkov::Shape::shape_ptr testCircle_2_ptr = std::make_shared<volkov::Circle>(volkov::point_t{ 14, 15 }, 2);

  volkov::CompositeShape testComposition(testRectangle_1_ptr);
  testComposition.add(testRectangle_2_ptr);
  testComposition.add(testCircle_1_ptr);
  testComposition.add(testCircle_2_ptr);

  volkov::Matrix testMatrix = part(testComposition);

  BOOST_REQUIRE_EQUAL(testMatrix.getRows(), 2);
  BOOST_REQUIRE_EQUAL(testMatrix.getLayerSize(0), 2);
  BOOST_REQUIRE_EQUAL(testMatrix.getLayerSize(1), 2);

  BOOST_CHECK_EQUAL(testMatrix.at(0, 0), testRectangle_1_ptr);
  BOOST_CHECK_EQUAL(testMatrix.at(0, 1), testRectangle_2_ptr);
  BOOST_CHECK_EQUAL(testMatrix.at(1, 0), testCircle_1_ptr);
  BOOST_CHECK_EQUAL(testMatrix.at(1, 1), testCircle_2_ptr);
}

BOOST_AUTO_TEST_CASE(testOverlap)
{
  volkov::Shape::shape_ptr testRectangle_1_ptr = std::make_shared<volkov::Rectangle>(volkov::point_t{ 5, 5 }, 1, 1);
  volkov::Shape::shape_ptr testRectangle_2_ptr = std::make_shared<volkov::Rectangle>(volkov::point_t{ 15, 15 }, 1, 1);
  volkov::Shape::shape_ptr testCirclePtr = std::make_shared<volkov::Circle>(volkov::point_t{ 4, 5 }, 3);

  BOOST_CHECK(volkov::isOverlap(testRectangle_1_ptr, testCirclePtr));
  BOOST_CHECK(!(volkov::isOverlap(testRectangle_2_ptr, testCirclePtr)));
}

BOOST_AUTO_TEST_SUITE_END();
