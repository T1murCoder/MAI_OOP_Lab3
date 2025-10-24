#include <iostream>
#include <iomanip>
#include "include/figure_array.h"
#include "include/square.h"
#include "include/rectangle.h"
#include "include/triangle.h"

void printMenu() {
    std::cout << "\n=== Меню работы с фигурами ===" << std::endl;
    std::cout << "1. Добавить фигуру" << std::endl;
    std::cout << "2. Вывести все фигуры" << std::endl;
    std::cout << "3. Показать центры и площади всех фигур" << std::endl;
    std::cout << "4. Вычислить общую площадь всех фигур" << std::endl;
    std::cout << "5. Сравнить две фигуры" << std::endl;
    std::cout << "6. Удалить фигуру по индексу" << std::endl;
    std::cout << "7. Очистить все фигуры" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выберите действие: ";
}

void addFigure(FigureArray& array) {
    std::cout << "\nВыберите тип фигуры:" << std::endl;
    std::cout << "1. Квадрат" << std::endl;
    std::cout << "2. Прямоугольник" << std::endl;
    std::cout << "3. Треугольник" << std::endl;
    std::cout << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Ошибка ввода!" << std::endl;
        return;
    }
    
    Figure* figure = nullptr;
    
    try {
        switch (choice) {
            case 1: {
                Square* sq = new Square();
                std::cin >> *sq;
                figure = sq;
                break;
            }
            case 2: {
                Rectangle* rect = new Rectangle();
                std::cin >> *rect;
                figure = rect;
                break;
            }
            case 3: {
                Triangle* tr = new Triangle();
                std::cin >> *tr;
                figure = tr;
                break;
            }
            default:
                std::cout << "Неверный выбор!" << std::endl;
                return;
        }
        
        if (figure != nullptr) {
            array.add(figure);
            std::cout << "Фигура успешно добавлена! Всего фигур: " << array.get_size() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        if (figure != nullptr) {
            delete figure;
        }
    }
}

void compareFigures(const FigureArray& array) {
    if (array.get_size() < 2) {
        std::cout << "\nНедостаточно фигур для сравнения! Требуется минимум 2." << std::endl;
        return;
    }
    
    std::cout << "\nВведите индексы двух фигур для сравнения (0-" << (array.get_size() - 1) << "): ";
    size_t idx1, idx2;
    std::cin >> idx1 >> idx2;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Ошибка ввода!" << std::endl;
        return;
    }
    
    try {
        if (array.compare(idx1, idx2)) {
            std::cout << "Фигуры #" << idx1 << " и #" << idx2 << " равны" << std::endl;
        } else {
            std::cout << "Фигуры #" << idx1 << " и #" << idx2 << " не равны" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void deleteFigure(FigureArray& array) {
    if (array.empty()) {
        std::cout << "\nМассив фигур пуст!" << std::endl;
        return;
    }
    
    std::cout << "\nВведите индекс фигуры для удаления (0-" << (array.get_size() - 1) << "): ";
    size_t idx;
    std::cin >> idx;
    
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Ошибка ввода!" << std::endl;
        return;
    }
    
    try {
        array.remove(idx);
        std::cout << "Фигура #" << idx << " успешно удалена! Осталось фигур: " << array.get_size() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    FigureArray array;
    int choice;
    
    std::cout << "Программа для работы с геометрическими фигурами" << std::endl;
    std::cout << "Используется динамический массив Figure*" << std::endl;
    
    while (true) {
        printMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка ввода! Попробуйте снова." << std::endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                addFigure(array);
                break;
            case 2:
                array.print_all();
                break;
            case 3:
                array.print_centers_and_areas();
                break;
            case 4: {
                if (array.empty()) {
                    std::cout << "\nМассив фигур пуст!" << std::endl;
                } else {
                    std::cout << std::fixed << std::setprecision(2);
                    std::cout << "\nОбщая площадь всех фигур: " << array.total_area() << std::endl;
                }
                break;
            }
            case 5:
                compareFigures(array);
                break;
            case 6:
                deleteFigure(array);
                break;
            case 7:
                array.clear();
                std::cout << "\nВсе фигуры удалены!" << std::endl;
                break;
            case 0:
                std::cout << "\nВыход из программы..." << std::endl;
                return 0;
            default:
                std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
        }
    }
    
    return 0;
}