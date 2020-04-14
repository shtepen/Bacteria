#ifndef UTILITY_H
#define UTILITY_H

namespace evol {

/**
 * @brief Структура Vector для упрощения восприятия геометрических векторов
 */
struct Vector {
    double x{0.0}; /** x-координата 2D-вектора */
    double y{0.0}; /** y-координата 2D-вектора */
    double length() const; /** Рассчитывает длину вектора */
    Vector operator+(const Vector& v_) const; /** Реализует сложение векторов */
    Vector operator-(const Vector& v_) const; /** Реализует вычитание векторов */
};

}

#endif // UTILITY_H
