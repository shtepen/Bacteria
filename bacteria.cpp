#include "bacteria.h"
#include <iostream>
#include <cassert>

/**
 * @brief Bacteria::Bacteria -- конструктор элемента класса Bacteria
 * @param position_ -- положение в среде
 * @param radius_ -- линейный размер бактерии
 * @param angle_ -- направление движения в радианах
 * @param velocity_ -- скорость движения бактерий
 */
Bacteria::Bacteria(evol::Vector position_, double radius_, double angle_, double velocity_)
                  : MapObject(position_, radius_, angle_), velocity{velocity_} {
    assert(velocity > 0);
    movement_value = movement_const * velocity_ / (radius_ * radius_);
}

/**
 * @brief Bacteria::canEat -- проверяет, может ли бактерия съесть данную питательную частицу
 *        (при подхождении на достаточное расстояние) и при возможности осуществляет съедение
 * @param f -- частица еды
 * @return есть ли возможность съесть
 */
bool Bacteria::canEat(Food& f) {
    if ((position - f.get_position()).length() < get_radius()) {
        food_collected += f.nutrition_value;
        f.is_eaten = true;
    }
    return  ((position - f.get_position()).length() < get_radius());
}

/**
 * @brief Bacteria::get_movement_value -- возвращает длину одного хода
 * @return длина одного хода
 */
double Bacteria::get_movement_value() {
    return movement_value;
}

double Bacteria::get_food_collected() {
    return food_collected;
}

/**
 * @brief Bacteria::first_bound_cross -- находит, какая из границ будет пересечена раньше при
 *        заданном направлении движения и возвращает расстояние до этой границы по данному направлению
 * @param br_b -- правая нижняя граница
 * @param tl_b -- левая верхняя граница
 * @return расстояние до ближайшей границы по заданному направлению
 */
double Bacteria::first_bound_cross(evol::Vector br_b, evol::Vector tl_b) {                    // returns distance to nearest bound and changes boundary_flag to value on crossing that bound
    if (get_angle() < (M_PI / 2)) {
        if (((tl_b.y - position.y) / sin(get_angle())) < ((br_b.x - position.x) / cos(get_angle()))) {
            boundary_flag = 1;
            return ((tl_b.y - position.y) / sin(get_angle()));
        }
        else  {
            boundary_flag = -1;
            return ((br_b.x - position.x) / cos(get_angle()));
        }
    }
    else if (get_angle() < M_PI) {
        if (((tl_b.y - position.y) / sin(get_angle())) < ((tl_b.x - position.x) / cos(get_angle()))) {
            boundary_flag = 1;
            return ((tl_b.y - position.y) / sin(get_angle()));
        }
        else {
            boundary_flag = -1;
            return ((tl_b.x - position.x) /cos(get_angle()));
        }
    }
    else if (get_angle() < (3 * M_PI / 2)) {
        if (((br_b.y - position.y) / sin(get_angle())) < ((tl_b.x - position.x) / cos(get_angle()))) {
            boundary_flag = 1;
            return ((br_b.y - position.y) / sin(get_angle()));
        }
        else {
            boundary_flag = -1;
            return ((tl_b.x - position.x) / cos(get_angle()));
        }
    }
    else {
        if (((br_b.y - position.y) / sin(get_angle())) < ((br_b.x - position.x) / cos(get_angle()))) {
            boundary_flag = 1;
            return ((br_b.y - position.y) / sin(get_angle()));
        }
        else {
            boundary_flag = -1;
            return ((br_b.x - position.x) / cos(get_angle()));
        }
    }
}

/**
 * @brief Bacteria::active_motion -- реализует активное движение
 * @param tl_b -- левая верхняя граница
 * @param br_b -- правая нижняя граница
 */
void Bacteria::active_motion(evol::Vector tl_b, evol::Vector br_b) {
    double dx = movement_value * cos(get_angle());
    double dy = movement_value * sin(get_angle());
    evol::Vector dpos{dx, dy}; /** Сколько пройдёт бактерия без учета границ */
    setBoundaryFlag(position + dpos, tl_b, br_b); /** Узнаём, не выходит ли при движении
                                                    * по прямой бактерия за границы среды
                                                    */
    while (boundary_flag != 0) { /** Ели выходит: */
        double dmov;
        dmov = first_bound_cross(br_b, tl_b); /** Узнаём, сколько она пройдёт до ближайшей
                                                * границы по направлению
                                                */
        position.x += dmov * cos(get_angle()); /** Передвигаем частицу до этой границы */
        position.y += dmov * sin(get_angle());
        movement_value -= dmov; /** Уменьшаем длину оставшегося хода */
        reflect(boundary_flag); /** Отражаем направление движения частицы от границы */
        dx = movement_value * cos(get_angle());
        dy = movement_value * sin(get_angle());
        dpos = {dx, dy}; /** Перерассчитываем продолжение ходя по прямой */
        setBoundaryFlag(position + dpos, tl_b, br_b);
    }
    position = position + dpos; /** Передвигаемся в конечную точку */
}

/**
 * @brief Bacteria::step -- реализует движение бактерии, состоящее из реактивного и броуновского движений */
void Bacteria::step() {
    active_motion(top_left, bottom_right);
    brownian_motion();
}

/**
 * @brief Bacteria::bactest -- проверяет корректность основных умений класса Bacteria
 */
void Bacteria::bactest() {
//    Environment w({0.0, 100.0}, {100.0, 0.0});
    Bacteria b1({12.0, 10.0}, 2.0, M_PI / 4, 1.0);
//    b1.set_boundaries(w);
    Food f1({2.0, 3.0}, 2.0, 0.0);
//    f1.set_boundaries(w);
    Food f({12.0, 9.0}, 1.0, 0.0);
//    f.set_boundaries(w);
    std::cout << "Bacteria's position is: (" << b1.position.x << ", " << b1.position.y <<"), it's angle is " << b1.get_angle() / M_PI <<" PI\n";
    std::cout << "Food-1's position is: (" << f1.get_position().x << ", " << f1.get_position().y <<"), n_v = " << f1.nutrition_value << "\n";
    std::cout << "Food-2's position is: (" << f.get_position().x << ", " << f.get_position().y <<"), n_v = " << f.nutrition_value << "\n";
    std::cout << "Bacteria has " << b1.get_food_collected() << " nutritions\n";
    std::cout << "Bacteria can " << (b1.canEat(f1) ? "eat food-1\n" : "not eat food-1\n");
    std::cout << "Bacteria can " << (b1.canEat(f) ? "eat food-2\n" : "not eat food-2\n");
    std::cout << "Now bacteria has " << b1.food_collected << " nutritions\n";
    b1.step();
    std::cout << "Bacteria moved to (" << b1.position.x << ", " << b1.position.y <<"), it's angle changed to " << b1.get_angle() << "\n";

    Bacteria b({1.0, 2.0}, 2.0, 5 * M_PI / 4, 6.0);
    std::cout << "\nNew bacteria's position is: (" << b.position.x << ", " << b.position.y <<"), it's angle is " << b.get_angle() / M_PI <<" PI\n";
    b.active_motion(b.top_left, b.bottom_right);
    std::cout << "Bacteria actioned to (" << b.position.x << ", " << b.position.y <<"), it's angle changed to " << b.get_angle() / M_PI << " PI\n";
    b.brownian_motion();
    std::cout << "Bacteria b_moved to (" << b.position.x << ", " << b.position.y <<"), it's angle changed to " << b.get_angle() / M_PI << " PI\n";


/*
    Bacteria b2({120.0, 10.0}, 2.0, M_PI / 4, 1.0);
    b2.set_boundaries(w);

    Bacteria b3({12.0, 10.0}, -1.0, M_PI / 4, 1.0);
    b3.set_boundaries(w);

    Bacteria b4({12.0, 180.0}, 2.0, M_PI / 4, 1.0);
    b4.set_boundaries(w);

    Bacteria b5({10.0, 10.0}, 2.0, 40 * M_PI / 4, 1.0);
    b5.set_boundaries(w);

    Food f2({-1.0, 0.0}, 1.0, 0.0);
    f2.set_boundaries(w);

    Food f3({3.0, 1000.0}, 1.0, 0.0);
    f3.set_boundaries(w);

    Food f4({5.0, 0.0}, 1.0, 100.0);
    f4.set_boundaries(w);

    Food f5({5.0, 0.0}, -5.0, 0.0);
    f5.set_boundaries(w);
*/
}
