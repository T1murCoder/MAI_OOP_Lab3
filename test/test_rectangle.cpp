#include <gtest/gtest.h>
#include "../include/rectangle.h"
#include <sstream>
#include <cmath>

// Тест конструктора по умолчанию
TEST(RectangleTest, DefaultConstructor) {
    Rectangle rect;
    EXPECT_DOUBLE_EQ(rect.calc_square(), 0.0);
    EXPECT_DOUBLE_EQ(rect.calc_square(), static_cast<double>(rect));
    
    Point3D center = rect.calc_center();
    EXPECT_DOUBLE_EQ(center.x, 0.0);
    EXPECT_DOUBLE_EQ(center.y, 0.0);
    EXPECT_DOUBLE_EQ(center.z, 0.0);
}

// Тест конструктора с параметрами
TEST(RectangleTest, ParameterizedConstructor) {
    Rectangle rect(4.0, 5.0, Point3D(0, 0, 0));
    EXPECT_DOUBLE_EQ(rect.calc_square(), 20.0);
    EXPECT_DOUBLE_EQ(rect.calc_square(), static_cast<double>(rect));
}

// Тест вычисления площади
TEST(RectangleTest, CalcSquareStandard) {
    Rectangle rect1(3.0, 4.0);
    EXPECT_DOUBLE_EQ(rect1.calc_square(), 12.0);
    EXPECT_DOUBLE_EQ(rect1.calc_square(), static_cast<double>(rect1));
}

TEST(RectangleTest, CalcSquareLarge) {
    Rectangle rect2(10.0, 2.5);
    EXPECT_DOUBLE_EQ(rect2.calc_square(), 25.0);
    EXPECT_DOUBLE_EQ(rect2.calc_square(), static_cast<double>(rect2));
}

TEST(RectangleTest, CalcSquareSmall) {
    Rectangle rect3(0.5, 0.5);
    EXPECT_DOUBLE_EQ(rect3.calc_square(), 0.25);
    EXPECT_DOUBLE_EQ(rect3.calc_square(), static_cast<double>(rect3));
}

// Тест вычисления геометрического центра - начало координат
TEST(RectangleTest, CalcCenterAtOrigin) {
    Rectangle rect(6.0, 3.0, Point3D(0, 0, 0));
    Point3D center = rect.calc_center();
    
    EXPECT_DOUBLE_EQ(center.x, 3.0);  // 0 + 6/2
    EXPECT_DOUBLE_EQ(center.y, 0.0);
    EXPECT_DOUBLE_EQ(center.z, 0.0);
}

// Тест вычисления геометрического центра - смещение по X
TEST(RectangleTest, CalcCenterOffsetX) {
    Rectangle rect(8.0, 4.0, Point3D(2, 0, 0));
    Point3D center = rect.calc_center();
    
    EXPECT_DOUBLE_EQ(center.x, 6.0);  // 2 + 8/2
    EXPECT_DOUBLE_EQ(center.y, 0.0);
    EXPECT_DOUBLE_EQ(center.z, 0.0);
}

// Тест оператора приведения к double
TEST(RectangleTest, CastToDouble) {
    Rectangle rect(6.0, 4.0);
    double area = static_cast<double>(rect);
    EXPECT_DOUBLE_EQ(area, 24.0);
}

// Тест оператора копирования
TEST(RectangleTest, CopyAssignment) {
    Rectangle rect1(5.0, 3.0, Point3D(1, 0, 0));
    Rectangle rect2;
    rect2 = rect1;
    
    EXPECT_DOUBLE_EQ(rect2.calc_square(), 15.0);
    EXPECT_DOUBLE_EQ(rect2.calc_square(), static_cast<double>(rect2));
    
    Point3D center = rect2.calc_center();
    EXPECT_DOUBLE_EQ(center.x, 3.5);  // 1 + 5/2
}

// Тест оператора перемещения
TEST(RectangleTest, MoveAssignment) {
    Rectangle rect1(4.0, 5.0, Point3D(1, 0, 0));
    Rectangle rect2;
    rect2 = std::move(rect1);
    
    EXPECT_DOUBLE_EQ(rect2.calc_square(), 20.0);
    EXPECT_DOUBLE_EQ(rect1.calc_square(), 0.0);
    EXPECT_DOUBLE_EQ(rect2.calc_square(), static_cast<double>(rect2));
    EXPECT_DOUBLE_EQ(rect1.calc_square(), static_cast<double>(rect1));
}

// Тест оператора сравнения - одинаковая площадь
TEST(RectangleTest, EqualityOperatorSameArea) {
    Rectangle rect1(4.0, 5.0);  // площадь = 20
    Rectangle rect2(5.0, 4.0);  // площадь = 20
    EXPECT_TRUE(rect1 == rect2);
}

// Тест оператора сравнения - разная площадь
TEST(RectangleTest, EqualityOperatorDifferentArea) {
    Rectangle rect1(4.0, 5.0);  // площадь = 20
    Rectangle rect2(3.0, 6.0);  // площадь = 18
    EXPECT_FALSE(rect1 == rect2);
}

// Тест оператора вывода
TEST(RectangleTest, OutputOperator) {
    Rectangle rect(6.0, 3.0, Point3D(0, 0, 0));
    
    std::ostringstream oss;
    oss << rect;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Прямоугольник") != std::string::npos);
    EXPECT_TRUE(output.find("6") != std::string::npos);
    EXPECT_TRUE(output.find("3") != std::string::npos);
}

// Тест оператора ввода
TEST(RectangleTest, InputOperator) {
    Rectangle rect;
    std::istringstream iss("4.0\n5.0\n1.0\n");
    
    // Подавляем cout
    std::streambuf* old_cout = std::cout.rdbuf();
    std::ostringstream null_stream;
    std::cout.rdbuf(null_stream.rdbuf());
    
    iss >> rect;
    
    std::cout.rdbuf(old_cout);
    
    EXPECT_DOUBLE_EQ(rect.calc_square(), 20.0);
    EXPECT_DOUBLE_EQ(rect.calc_square(), static_cast<double>(rect));
    
    Point3D center = rect.calc_center();
    EXPECT_DOUBLE_EQ(center.x, 3.0);  // 1 + 4/2
}

// Тест граничных случаев
TEST(RectangleTest, EdgeCaseZeroWidth) {
    Rectangle rect(0.0, 5.0);
    EXPECT_DOUBLE_EQ(rect.calc_square(), 0.0);
    EXPECT_DOUBLE_EQ(rect.calc_square(), static_cast<double>(rect));
}

TEST(RectangleTest, EdgeCaseZeroHeight) {
    Rectangle rect(5.0, 0.0);
    EXPECT_DOUBLE_EQ(rect.calc_square(), 0.0);
    EXPECT_DOUBLE_EQ(rect.calc_square(), static_cast<double>(rect));
}