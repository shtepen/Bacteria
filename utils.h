#ifndef UTILITY_H
#define UTILITY_H

namespace evol {

struct Vector {
    double x{0.0};
    double y{0.0};
    double length() const;
    Vector operator+(const Vector& v_) const;
    Vector operator-(const Vector& v_) const;
    bool operator>=(const Vector& v_) const;
    bool operator<(const Vector& v_) const;
};

}

#endif // UTILITY_H
