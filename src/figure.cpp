#include "../include/figure.h"
#include <cmath>

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.input(is);
    return is;
}

// Сравниваем по площади
bool Figure::operator==(const Figure& other) const {
    return std::abs(calc_square() - other.calc_square()) < 1e-9; // Точность сравнения
}