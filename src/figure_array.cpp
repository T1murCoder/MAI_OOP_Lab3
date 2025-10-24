#include "../include/figure_array.h"
#include "../include/point3d.h"
#include <stdexcept>
#include <algorithm>

FigureArray::FigureArray() : figures(nullptr), size(0), capacity(0) {}

FigureArray::FigureArray(size_t initial_capacity) 
    : figures(nullptr), size(0), capacity(initial_capacity) {
    if (capacity > 0) {
        figures = new Figure*[capacity];
    }
}

FigureArray::~FigureArray() {
    clear();
    delete[] figures;
}

void FigureArray::resize() {
    size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
    Figure** new_figures = new Figure*[new_capacity];
    
    // Копируем указатели
    for (size_t i = 0; i < size; ++i) {
        new_figures[i] = figures[i];
    }
    
    delete[] figures;
    figures = new_figures;
    capacity = new_capacity;
}

void FigureArray::add(Figure* figure) {
    if (figure == nullptr) {
        throw std::invalid_argument("Попытка добавить nullptr");
    }
    
    if (size >= capacity) {
        resize();
    }
    
    figures[size++] = figure;
}

Figure* FigureArray::get(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Индекс выходит за границы массива");
    }
    return figures[index];
}

void FigureArray::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Индекс выходит за границы массива");
    }
    
    // Удаляем фигуру
    delete figures[index];
    
    // Сдвигаем элементы влево
    for (size_t i = index; i < size - 1; ++i) {
        figures[i] = figures[i + 1];
    }
    
    --size;
}

void FigureArray::clear() {
    for (size_t i = 0; i < size; ++i) {
        delete figures[i];
    }
    size = 0;
}

size_t FigureArray::get_size() const {
    return size;
}

size_t FigureArray::get_capacity() const {
    return capacity;
}

bool FigureArray::empty() const {
    return size == 0;
}

double FigureArray::total_area() const {
    double total = 0.0;
    for (size_t i = 0; i < size; ++i) {
        total += figures[i]->calc_square();
    }
    return total;
}

void FigureArray::print_all(std::ostream& os) const {
    if (empty()) {
        os << "Массив фигур пуст!" << std::endl;
        return;
    }

    os << "=== Все фигуры ===" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        os << "Фигура #" << i << ":" << std::endl;
        os << *figures[i] << std::endl;
    }
}

void FigureArray::print_centers_and_areas(std::ostream& os) const {
    if (empty()) {
        os << "Массив фигур пуст!" << std::endl;
        return;
    }

    os << "=== Центры и площади фигур ===" << std::endl;

    for (size_t i = 0; i < size; ++i) {
        Point3D center = figures[i]->calc_center();
        double area = figures[i]->calc_square();

        os << "Фигура #" << i << ":" << std::endl;
        os << "  Центр: (" << center.x << ", " << center.y << ", " << center.z << ")" << std::endl;
        os << "  Площадь: " << area << std::endl;
        os << *figures[i] << std::endl;
    }
}

bool FigureArray::compare(size_t idx1, size_t idx2) const {
    if (idx1 >= size || idx2 >= size) {
        throw std::out_of_range("Индекс выходит за границы массива");
    }
    return *figures[idx1] == *figures[idx2];
}