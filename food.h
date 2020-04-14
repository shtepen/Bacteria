#ifndef FOOD_H
#define FOOD_H

#include "mapobject.h"

class Food : public MapObject {
public:
    Food(evol::Vector position_, double radius_, double angle_);
    double nutrition_value;
    double nutr_const{5.0};
    bool is_eaten{false};
    void step() override;
};

#endif // FOOD_H
