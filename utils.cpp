#include "utils.h"

#include <functional>
#include <cmath>

namespace evol {

double Vector::length() const {
    return std::sqrt(x * x + y * y);
}

Vector Vector::operator+(const Vector& v_) const {
    return Vector{x + v_.x, y + v_.y};
}

Vector Vector::operator-(const Vector& v_) const {
    return Vector{x - v_.x, y - v_.y};
}

bool Vector::operator>=(const Vector& v_) const {
    return std::tie(x, y) >= std::tie(v_.x, v_.y);
}

bool Vector::operator<(const Vector& v_) const {
    return std::tie(x, y) < std::tie(v_.x, v_.y);
}

}
