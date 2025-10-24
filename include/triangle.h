#pragma once

#include "figure.h"
#include "point3d.h"
#include <iostream>

class Triangle : public Figure {
protected:
    virtual void print(std::ostream& os) const override;
    virtual void input(std::istream& is) override;
public:
    Triangle();
    Triangle(double b, double h, Point3D o = Point3D(0, 0, 0));
    ~Triangle();

    virtual Point3D calc_center() const override;
    virtual double calc_square() const override;

    explicit virtual operator double() const override;

    Triangle& operator=(const Triangle& right_operand);
    
    Triangle& operator=(Triangle&& right_operand) noexcept;

private:
    double base;
    double height;
    Point3D origin; // вершина прямого угла
};