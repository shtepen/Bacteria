#ifndef MAPOBJECT_H
#define MAPOBJECT_H
#include "utils.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "environment.h"

class MapObject {
public:
    MapObject(evol::Vector position_, double radius_, double angle_);
    evol::Vector position;
    double radius;
    double angle;
    int boundary_flag{0};
    void setBoundaryFlag(evol::Vector curr_pos, evol::Vector tl_b, evol::Vector br_b);
    const double movement_const{1};
    static evol::Vector top_left;
    static evol::Vector bottom_right;
    void set_boundaries(const Environment& world);
    evol::Vector get_position();
    double get_radius();
    void brownian_motion();
    virtual void step() = 0;
};

#endif // MAPOBJECT_H
