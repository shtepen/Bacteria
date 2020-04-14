#include "bacteria.h"
#include <iostream>

Bacteria::Bacteria(evol::Vector position_, double radius_, double angle_, double velocity_)
                  : MapObject(position_, radius_, angle_), velocity{velocity_} {
    movement_value = movement_const * velocity_ / (radius_ * radius_);
}

bool Bacteria::canEat(Food& f) {
    if ((position - f.position).length() < radius)
        food_collected += f.nutrition_value;
    f.is_eaten = true;
    return  ((position - f.position).length() < radius);
}

void Bacteria::reflect(int b_f) {
    if (b_f == 1)                          //reflect from horizontal boundaries
        angle = 2 * M_PI - angle;
    else {                                 //reflect from vertical boundaries
        if (angle <= M_PI)
            angle = M_PI - angle;
        else
            angle = 3 * M_PI - angle;
    }
}

double Bacteria::first_bound_cross(evol::Vector br_b, evol::Vector tl_b) {                    // returns distance to nearest bound and changes boundary_flag to value on crossing that bound
    if (angle < (M_PI / 2)) {
        if (((tl_b.y - position.y) / sin(angle)) < ((br_b.x - position.x) / cos(angle))) {
            boundary_flag = 1;
            return ((tl_b.y - position.y) / sin(angle));
        }
        else  {
            boundary_flag = -1;
            return ((br_b.x - position.x) / cos(angle));
        }
    }
    else if (angle < M_PI) {
        if (((tl_b.y - position.y) / sin(angle)) < ((tl_b.x - position.x) / cos(angle))) {
            boundary_flag = 1;
            return ((tl_b.y - position.y) / sin(angle));
        }
        else {
            boundary_flag = -1;
            return ((tl_b.x - position.x) /cos(angle));
        }
    }
    else if (angle < (3 * M_PI / 2)) {
        if (((br_b.y - position.y) / sin(angle)) < ((tl_b.x - position.x) / cos(angle))) {
            boundary_flag = 1;
            return ((br_b.y - position.y) / sin(angle));
        }
        else {
            boundary_flag = -1;
            return ((tl_b.x - position.x) / cos(angle));
        }
    }
    else {
        if (((br_b.y - position.y) / sin(angle)) < ((br_b.x - position.x) / cos(angle))) {
            boundary_flag = 1;
            return ((br_b.y - position.y) / sin(angle));
        }
        else {
            boundary_flag = -1;
            return ((br_b.x - position.x) / cos(angle));
        }
    }
}

void Bacteria::active_motion(evol::Vector tl_b, evol::Vector br_b) {
    double dx = movement_value * cos(angle);
    double dy = movement_value * sin(angle);
    evol::Vector dpos{dx, dy};
    setBoundaryFlag(position + dpos, tl_b, br_b);
    while (boundary_flag != 0) {
        double dmov;
        dmov = first_bound_cross(br_b, tl_b);
        position.x += dmov * cos(angle);
        position.y += dmov * sin(angle);
        movement_value -= dmov;
        reflect(boundary_flag);
        dx = movement_value * cos(angle);
        dy = movement_value * sin(angle);
        dpos = {dx, dy};
        setBoundaryFlag(position + dpos, tl_b, br_b);
    }
    position = position + dpos;
}

void Bacteria::step() {
    active_motion(top_left, bottom_right);
    brownian_motion();
}

/*void Bacteria::motion(evol::Vector tl_b, evol::Vector br_b) {
    double dx = movement_value * cos(angle);
    double dy = movement_value * sin(angle);
    evol::Vector dpos{dx, dy};
    setBoundaryFlag(position + dpos, tl_b, br_b);
    if (boundary_flag == 0)
        position = position + dpos;
    else {
        if (boundary_flag == 1) {
            position.x += dx;
            if (dy > 0)
                position.y = 2 * tl_b.y - position.y - dy;
            else
                position.y = 2 * br_b.y - position.y - dy;
        }
        else {
            position.y += dy;
            if (dx > 0)
                position.x = 2 * br_b.x - position.x - dx;
            else
                position.x = 2 * tl_b.x - position.x - dx;
        }
        reflect(boundary_flag);
    }

}
*/
