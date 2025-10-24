#include <gtest/gtest.h>
#include "../include/square.h"
#include <sstream>
#include <cmath>

// Тест конструктора по умолчанию
TEST(SquareTest, DefaultConstructor) {
    Square sq;
    EXPECT_DOUBLE_EQ(sq.calc_square(), 0.0);
    
    Point3D center = sq.calc_center();
    EXPECT_DOUBLE_EQ(center.x, 0.0);
    EXPECT_DOUBLE_EQ(center.y, 0.0);
    EXPECT_DOUBLE_EQ(center.z, 0.0);
}

// Тест конструктора с параметрами
TEST(SquareTest, ParameterizedConstructor) {
    Square sq(5.0, Point3D(1, 0, 0));
    EXPECT_DOUBLE_EQ(sq.calc_square(), 25.0);
    
    Point3D center = sq.calc_center();
    EXPECT_DOUBLE_EQ(center.x, 3.5);  // 1 + 5/2
}

// Тест вычисления площади - различные размеры
TEST(SquareTest, CalcSquareVariousSizes) {
    Square sq1(4.0);
    EXPECT_DOUBLE_EQ(sq1.calc_square(), 16.0);
    
    Square sq2(10.0);
    EXPECT_DOUBLE_EQ(sq2.calc_square(), 100.0);
    
    Square sq3(0.5);
    EXPECT_DOUBLE_EQ(sq3.calc_square(), 0.25);
}

// Тест вычисления геометрического центра - начало координат
TEST(SquareTest, CalcCenterAtOrigin) {
    Square sq(4.0, Point3D(0, 0, 0));
    Point3D center = sq.calc_center();
    
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 0.0);
    EXPECT_DOUBLE_EQ(center.z, 0.0);
}

// Тест вычисления геометрического центра - смещение по X
TEST(SquareTest, CalcCenterOffsetX) {
    Square sq(6.0, Point3D(3, 0, 0));
    Point3D center = sq.calc_center();
    
    EXPECT_DOUBLE_EQ(center.x, 6.0);  // 3 + 6/2
    EXPECT_DOUBLE_EQ(center.y, 0.0);
    EXPECT_DOUBLE_EQ(center.z, 0.0);
}

// Тест оператора приведения к double
TEST(SquareTest, CastToDouble) {
    Square sq(5.0);
    double area = static_cast<double>(sq);
    EXPECT_DOUBLE_EQ(area, 25.0);
}

// Тест оператора копирования
TEST(SquareTest, CopyAssignment) {
    Square sq1(4.0, Point3D(1, 0, 0));
    Square sq2;
    sq2 = sq1;
    
    EXPECT_DOUBLE_EQ(sq2.calc_square(), 16.0);
    
    Point3D center = sq2.calc_center();
    EXPECT_DOUBLE_EQ(center.x, 3.0);  // 1 + 4/2
}

// Тест оператора перемещения
TEST(SquareTest, MoveAssignment) {
    Square sq1(4.0, Point3D(2, 0, 0));
    Square sq2;
    sq2 = std::move(sq1);
    
    // sq2 должен получить значения sq1
    EXPECT_DOUBLE_EQ(sq2.calc_square(), 16.0);
    Point3D center2 = sq2.calc_center();
    EXPECT_DOUBLE_EQ(center2.x, 4.0);
    
    // sq1 должен быть обнулен
    EXPECT_DOUBLE_EQ(sq1.calc_square(), 0.0);
}

// Тест оператора сравнения - равные квадраты
TEST(SquareTest, EqualityOperatorEqual) {
    Square sq1(4.0);
    Square sq2(4.0);
    EXPECT_TRUE(sq1 == sq2);
}

// Тест оператора сравнения - разные квадраты
TEST(SquareTest, EqualityOperatorNotEqual) {
    Square sq1(4.0);
    Square sq2(5.0);
    EXPECT_FALSE(sq1 == sq2);
}

// Тест оператора вывода
TEST(SquareTest, OutputOperator) {
    Square sq(3.0, Point3D(1, 0, 0));
    
    // Перенаправляем вывод
    std::ostringstream oss;
    oss << sq;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Квадрат") != std::string::npos);
    EXPECT_TRUE(output.find("3") != std::string::npos);
}

// Тест оператора ввода
TEST(SquareTest, InputOperator) {
    Square sq;
    std::istringstream iss("5.0\n2.0\n");
    
    // Подавляем cout
    std::streambuf* old_cout = std::cout.rdbuf();
    std::ostringstream null_stream;
    std::cout.rdbuf(null_stream.rdbuf());
    
    iss >> sq;
    
    std::cout.rdbuf(old_cout);
    
    EXPECT_DOUBLE_EQ(sq.calc_square(), 25.0);
    Point3D center = sq.calc_center();
    EXPECT_DOUBLE_EQ(center.x, 4.5);  // 2 + 5/2
}