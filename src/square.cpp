#include "../include/square.h"
#include <iostream>

Square::Square() : side(0.0), bottom_left(0, 0, 0) {
    std::cout << "Square: конструктор по умолчанию\n";
}

Square::Square(double s, Point3D bl) : side(s), bottom_left(bl) {
    std::cout << "Square: конструктор с параметрами\n";
}

Square::~Square() {
    std::cout << "Square: деструктор (сторона = " << side << ")\n";
}

Square& Square::operator=(const Square& other) {
    if (this != &other) {
        side = other.side;
        bottom_left = other.bottom_left;
    }
    return *this;
}

Square& Square::operator=(Square&& other) noexcept {
    if (this != &other) {
        side = other.side;
        bottom_left = other.bottom_left;
        
        other.side = 0.0;
        other.bottom_left = Point3D(0, 0, 0);
    }
    return *this;
}

void Square::print(std::ostream& os) const {
    os << "Квадрат (сторона = " << side << "):\n";
    os << "  Вершина 1: (" << bottom_left.x << ", " << bottom_left.y << ", " << bottom_left.z << ")\n";
    os << "  Вершина 2: (" << (bottom_left.x + side) << ", " << bottom_left.y << ", " << bottom_left.z << ")\n";
    os << "  Вершина 3: (" << (bottom_left.x + side) << ", " << (bottom_left.y + side) << ", " << bottom_left.z << ")\n";
    os << "  Вершина 4: (" << bottom_left.x << ", " << (bottom_left.y + side) << ", " << bottom_left.z << ")";
}

void Square::input(std::istream& is) {
    std::cout << "Введите сторону квадрата: ";
    is >> side;
    std::cout << "Введите координату X левой нижней вершины: ";
    is >> bottom_left.x;
}

Point3D Square::calc_center() const {
    return Point3D(bottom_left.x + side / 2.0, 0.0, 0.0);
}

double Square::calc_square() const {
    return side * side;
}

Square::operator double() const {
    return calc_square();
}