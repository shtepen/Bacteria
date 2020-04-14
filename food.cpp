#include "food.h"

/**
 * @brief Food::Food -- конструктор элемента класса Food
 * @param position_ -- положение в среде
 * @param radius_ -- линейный размер
 * @param angle_ -- направление движения
 */
Food::Food(evol::Vector position_, double radius_, double angle_) : MapObject(position_, radius_, angle_) {
    nutrition_value = nutr_const * radius_ * radius_;
}

/**
 * @brief Food::step -- осуществление броуновского движения питательной частицы
 */
void Food::step() {
    brownian_motion();
}
