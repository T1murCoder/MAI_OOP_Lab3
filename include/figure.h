#pragma once

#include "point3d.h"
#include <iostream>

class Figure {
    friend std::ostream& operator<<(std::ostream& os, const Figure& obj);
    friend std::istream& operator>>(std::istream& is, Figure& obj);
protected:
    Figure() = default;
    // Для использования в friend operator<<
    virtual void print(std::ostream& os) const = 0;
    // Для использования в friend operator>>
    virtual void input(std::istream& is) = 0;
public:
    virtual ~Figure() = default;
    
    // Чистая виртуальная функция для вычисления центра фигуры вращения
    virtual Point3D calc_center() const = 0;
    // Чистая виртуальная функция для вычисления площади фигуры
    virtual double calc_square() const = 0;

    // Чистый виртуальный оператор, при приведении к double возвращает площадь из calc_square()
    explicit virtual operator double() const = 0;
    bool operator==(const Figure& other) const;

};

std::ostream& operator<<(std::ostream& os, const Figure& fig);
std::istream& operator>>(std::istream& is, Figure& fig);