#ifndef BACTERIA_H
#define BACTERIA_H

#include "mapobject.h"
#include "food.h"

class Bacteria : public MapObject {
public:
    Bacteria(evol::Vector position_, double radius_, double angle_, double velocity_);
    bool canEat(Food& f);    void reflect(int b_f);           //b_f is for boundary_flag
    void active_motion(evol::Vector tl, evol::Vector br);
    void step() override;
    double movement_value;
    double first_bound_cross(evol::Vector br_b, evol::Vector tl_b);
private:
    double velocity;
    double food_collected{0.0};
};

#endif // BACTERIA_H
