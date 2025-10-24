#include "../include/rectangle.h"
#include <iostream>

Rectangle::Rectangle() : width(0.0), height(0.0), bottom_left(0, 0, 0) {
    std::cout << "Rectangle: конструктор по умолчанию\n";
}

Rectangle::Rectangle(double w, double h, Point3D bl) : width(w), height(h), bottom_left(bl) {
    std::cout << "Rectangle: конструктор с параметрами\n";
}

Rectangle::~Rectangle() {
    std::cout << "Rectangle: деструктор (ширина = " << width << ", высота = " << height << ")\n";
}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        bottom_left = other.bottom_left;
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        width = other.width;
        height = other.height;
        bottom_left = other.bottom_left;
        
        other.width = 0.0;
        other.height = 0.0;
        other.bottom_left = Point3D(0, 0, 0);
    }
    return *this;
}

void Rectangle::print(std::ostream& os) const {
    os << "Прямоугольник (ширина = " << width << ", высота = " << height << "):\n";
    os << "  Вершина 1: (" << bottom_left.x << ", " << bottom_left.y << ", " << bottom_left.z << ")\n";
    os << "  Вершина 2: (" << (bottom_left.x + width) << ", " << bottom_left.y << ", " << bottom_left.z << ")\n";
    os << "  Вершина 3: (" << (bottom_left.x + width) << ", " << (bottom_left.y + height) << ", " << bottom_left.z << ")\n";
    os << "  Вершина 4: (" << bottom_left.x << ", " << (bottom_left.y + height) << ", " << bottom_left.z << ")";
}

void Rectangle::input(std::istream& is) {
    std::cout << "Введите ширину прямоугольника: ";
    is >> width;
    std::cout << "Введите высоту прямоугольника: ";
    is >> height;
    std::cout << "Введите координату X левой нижней вершины: ";
    is >> bottom_left.x;
}

Point3D Rectangle::calc_center() const {
    return Point3D(bottom_left.x + width / 2.0, 0.0, 0.0);
}

double Rectangle::calc_square() const {
    return width * height;
}

Rectangle::operator double() const {
    return calc_square();
}