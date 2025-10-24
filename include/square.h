#pragma once

#include "figure.h"
#include "point3d.h"
#include <iostream>

class Square : public Figure {
protected:
    virtual void print(std::ostream& os) const override;
    virtual void input(std::istream& is) override;
public:
    Square();
    explicit Square(double s, Point3D bl = Point3D(0, 0, 0));
    ~Square();

    virtual Point3D calc_center() const override;
    virtual double calc_square() const override;

    explicit virtual operator double() const override;

    Square& operator=(const Square& right_operand);
    Square& operator=(Square&& right_operand) noexcept;

private:
    double side;
    Point3D bottom_left;
};