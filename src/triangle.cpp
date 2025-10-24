#include "../include/triangle.h"
#include <iostream>

Triangle::Triangle() : base(0.0), height(0.0), origin(0, 0, 0) {
    std::cout << "Triangle: конструктор по умолчанию\n";
}

Triangle::Triangle(double b, double h, Point3D o) : base(b), height(h), origin(o) {
    std::cout << "Triangle: конструктор с параметрами\n";
}

Triangle::~Triangle() {
    std::cout << "Triangle: деструктор (основание = " << base << ", высота = " << height << ")\n";
}

Triangle& Triangle::operator=(const Triangle& other) {
    std::cout << "Triangle: оператор присваивания копированием\n";
    if (this != &other) {
        base = other.base;
        height = other.height;
        origin = other.origin;
    }
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other) noexcept {
    std::cout << "Triangle: оператор присваивания перемещением\n";
    if (this != &other) {
        base = other.base;
        height = other.height;
        origin = other.origin;
        
        other.base = 0.0;
        other.height = 0.0;
        other.origin = Point3D(0, 0, 0);
    }
    return *this;
}

void Triangle::print(std::ostream& os) const {
    os << "Треугольник (основание = " << base << ", высота = " << height << "):\n";
    os << "  Вершина 1: (" << origin.x << ", " << origin.y << ", " << origin.z << ")\n";
    os << "  Вершина 2: (" << (origin.x + base) << ", " << origin.y << ", " << origin.z << ")\n";
    os << "  Вершина 3: (" << origin.x << ", " << (origin.y + height) << ", " << origin.z << ")";
}

void Triangle::input(std::istream& is) {
    std::cout << "Введите основание треугольника: ";
    is >> base;
    std::cout << "Введите высоту треугольника: ";
    is >> height;
    std::cout << "Введите координату X вершины прямого угла: ";
    is >> origin.x;
}

Point3D Triangle::calc_center() const {
    return Point3D(origin.x + 3.0 * base / 4.0, 0.0, 0.0);
}

double Triangle::calc_square() const {
    return 0.5 * base * height;
}

Triangle::operator double() const {
    return calc_square();
}