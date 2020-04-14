#include "food.h"

Food::Food(evol::Vector position_, double radius_, double angle_) : MapObject(position_, radius_, angle_) {
    nutrition_value = nutr_const * radius_ * radius_;
}

void Food::step() {
    brownian_motion();
}
