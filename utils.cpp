#include "utils.h"

#include <functional>
#include <cmath>

namespace evol {

/**
 * @brief Vector::length -- расчёт длины вектора
 * @return длина 2-вектора
 */
double Vector::length() const {
    return std::sqrt(x * x + y * y);
}

/**
 * @brief Vector::operator + -- реализует сложение двух 2-векторов
 * @param v_ -- прибавляемый 2-вектор
 * @return суммарный 2-вектор
 */
Vector Vector::operator+(const Vector& v_) const {
    return Vector{x + v_.x, y + v_.y};
}

/**
 * @brief Vector::operator - -- реализует вычитание из вектора другого вектора
 * @param v_ -- вычитаемый вектор
 * @return разность векторов
 */
Vector Vector::operator-(const Vector& v_) const {
    return Vector{x - v_.x, y - v_.y};
}

}
