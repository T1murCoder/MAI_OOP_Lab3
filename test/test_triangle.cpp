#include <gtest/gtest.h>
#include "../include/triangle.h"
#include "../include/rectangle.h"
#include <sstream>
#include <cmath>

// Тест конструктора по умолчанию
TEST(TriangleTest, DefaultConstructor) {
    Triangle tri;
    EXPECT_DOUBLE_EQ(tri.calc_square(), 0.0);
    
    Point3D center = tri.calc_center();
    EXPECT_DOUBLE_EQ(center.x, 0.0);
    EXPECT_DOUBLE_EQ(center.y, 0.0);
    EXPECT_DOUBLE_EQ(center.z, 0.0);
}

// Тест конструктора с параметрами
TEST(TriangleTest, ParameterizedConstructor) {
    Triangle tri(8.0, 6.0, Point3D(0, 0, 0));
    EXPECT_DOUBLE_EQ(tri.calc_square(), 24.0);  // 0.5 * 8 * 6
}

// Тест вычисления площади
TEST(TriangleTest, CalcSquareStandard) {
    Triangle tri1(6.0, 4.0);
    EXPECT_DOUBLE_EQ(tri1.calc_square(), 12.0);  // 0.5 * 6 * 4
}

TEST(TriangleTest, CalcSquareLarge) {
    Triangle tri2(10.0, 5.0);
    EXPECT_DOUBLE_EQ(tri2.calc_square(), 25.0);  // 0.5 * 10 * 5
}

TEST(TriangleTest, CalcSquareSmall) {
    Triangle tri3(3.0, 4.0);
    EXPECT_DOUBLE_EQ(tri3.calc_square(), 6.0);  // 0.5 * 3 * 4
}

// Тест вычисления геометрического центра - начало координат
TEST(TriangleTest, CalcCenterAtOrigin) {
    Triangle tri(8.0, 6.0, Point3D(0, 0, 0));
    Point3D center = tri.calc_center();
    
    EXPECT_DOUBLE_EQ(center.x, 6.0);  // 0 + 3*8/4
    EXPECT_DOUBLE_EQ(center.y, 0.0);
    EXPECT_DOUBLE_EQ(center.z, 0.0);
}

// Тест вычисления геометрического центра - смещение по X
TEST(TriangleTest, CalcCenterOffsetX) {
    Triangle tri(12.0, 9.0, Point3D(2, 0, 0));
    Point3D center = tri.calc_center();
    
    EXPECT_DOUBLE_EQ(center.x, 11.0);  // 2 + 3*12/4
    EXPECT_DOUBLE_EQ(center.y, 0.0);
    EXPECT_DOUBLE_EQ(center.z, 0.0);
}

// Тест формулы центра конуса (3/4 от основания)
TEST(TriangleTest, CalcCenterFormulaValidation) {
    Triangle tri(4.0, 3.0, Point3D(0, 0, 0));
    Point3D center = tri.calc_center();
    
    EXPECT_DOUBLE_EQ(center.x, 3.0);  // 0 + 3*4/4 = 3
}

// Тест оператора приведения к double
TEST(TriangleTest, CastToDouble) {
    Triangle tri(10.0, 8.0);
    double area = static_cast<double>(tri);
    EXPECT_DOUBLE_EQ(area, 40.0);  // 0.5 * 10 * 8
}

// Тест оператора копирования
TEST(TriangleTest, CopyAssignment) {
    Triangle tri1(6.0, 4.0, Point3D(1, 0, 0));
    Triangle tri2;
    tri2 = tri1;
    
    EXPECT_DOUBLE_EQ(tri2.calc_square(), 12.0);
    
    Point3D center = tri2.calc_center();
    EXPECT_DOUBLE_EQ(center.x, 5.5);  // 1 + 3*6/4 = 1 + 4.5
}

// Тест оператора перемещения
TEST(TriangleTest, MoveAssignment) {
    Triangle tri1(8.0, 6.0, Point3D(2, 0, 0));
    Triangle tri2;
    tri2 = std::move(tri1);
    
    EXPECT_DOUBLE_EQ(tri2.calc_square(), 24.0);
    EXPECT_DOUBLE_EQ(tri1.calc_square(), 0.0);
}

// Тест оператора сравнения - одинаковая площадь
TEST(TriangleTest, EqualityOperatorSameArea) {
    Triangle tri1(8.0, 6.0);   // площадь = 24
    Triangle tri2(12.0, 4.0);  // площадь = 24
    EXPECT_TRUE(tri1 == tri2);
}

// Тест оператора сравнения - разная площадь
TEST(TriangleTest, EqualityOperatorDifferentArea) {
    Triangle tri1(8.0, 6.0);   // площадь = 24
    Triangle tri2(6.0, 6.0);   // площадь = 18
    EXPECT_FALSE(tri1 == tri2);
}

// Тест оператора вывода
TEST(TriangleTest, OutputOperator) {
    Triangle tri(8.0, 6.0, Point3D(0, 0, 0));
    
    std::ostringstream oss;
    oss << tri;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Треугольник") != std::string::npos);
    EXPECT_TRUE(output.find("8") != std::string::npos);
    EXPECT_TRUE(output.find("6") != std::string::npos);
}

// Тест оператора ввода
TEST(TriangleTest, InputOperator) {
    Triangle tri;
    std::istringstream iss("10.0\n5.0\n2.0\n");
    
    // Подавляем cout
    std::streambuf* old_cout = std::cout.rdbuf();
    std::ostringstream null_stream;
    std::cout.rdbuf(null_stream.rdbuf());
    
    iss >> tri;
    
    std::cout.rdbuf(old_cout);
    
    EXPECT_DOUBLE_EQ(tri.calc_square(), 25.0);
    
    Point3D center = tri.calc_center();
    EXPECT_DOUBLE_EQ(center.x, 9.5);  // 2 + 3*10/4 = 2 + 7.5
}

// Тест граничных случаев
TEST(TriangleTest, EdgeCaseZeroBase) {
    Triangle tri1(0.0, 5.0);
    EXPECT_DOUBLE_EQ(tri1.calc_square(), 0.0);
}

TEST(TriangleTest, EdgeCaseZeroHeight) {
    Triangle tri2(5.0, 0.0);
    EXPECT_DOUBLE_EQ(tri2.calc_square(), 0.0);
}

// Тест сравнения треугольников с квадратами и прямоугольниками
TEST(TriangleTest, CompareWithOtherFigures) {
    Triangle tri(8.0, 6.0);  // площадь = 24
    Rectangle rect(6.0, 4.0);  // площадь = 24
    
    EXPECT_TRUE(tri == rect);
}