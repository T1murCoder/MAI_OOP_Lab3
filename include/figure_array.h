#pragma once

#include <iostream>
#include "figure.h"

class FigureArray {
public:
    // Конструктор и деструктор
    FigureArray();
    explicit FigureArray(size_t initial_capacity);
    ~FigureArray();

    void add(Figure* figure);

    Figure* get(size_t index) const;

    void remove(size_t index);

    void clear();

    size_t get_size() const;

    size_t get_capacity() const;

    bool empty() const;

    double total_area() const;

    void print_all(std::ostream& os = std::cout) const;

    void print_centers_and_areas(std::ostream& os = std::cout) const;

    bool compare(size_t idx1, size_t idx2) const;
private:
    Figure** figures;
    size_t size;
    size_t capacity;

    void resize();
};