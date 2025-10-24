#pragma once

#include "figure.h"
#include "point3d.h"
#include <iostream>

class Rectangle : public Figure {
protected:
    virtual void print(std::ostream& os) const override;
    virtual void input(std::istream& is) override;
public:
    Rectangle();
    Rectangle(double w, double h, Point3D bl = Point3D(0, 0, 0));

    ~Rectangle();

    virtual Point3D calc_center() const override;
    virtual double calc_square() const override;

    explicit virtual operator double() const override;

    Rectangle& operator=(const Rectangle& right_operand); 

    
    Rectangle& operator=(Rectangle&& right_operand) noexcept; 

private:
    double width;
    double height;
    Point3D bottom_left;
};