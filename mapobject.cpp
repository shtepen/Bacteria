#include "mapobject.h"

MapObject::MapObject(evol::Vector position_, double radius_, double angle_) {
    position = position_;
    radius = radius_;
    angle = angle_;
}

evol::Vector MapObject::get_position() {
    return this->position;
}

double MapObject::get_radius() {
    return this->radius;
}

void MapObject::setBoundaryFlag(evol::Vector curr_pos, evol::Vector tl_b, evol::Vector br_b) {
    if ((curr_pos.y > tl_b.y) || (curr_pos.y < br_b.y))
        boundary_flag = 1;
    else if ((curr_pos.x < tl_b.x) || (curr_pos.x > br_b.x))
        boundary_flag = -1;
    else boundary_flag = 0;
}


void MapObject::brownian_motion() {
    position.x += cos(angle) * movement_const / radius;
    position.y += sin(angle) * movement_const / radius;
    angle = 2 * M_PI * rand() / RAND_MAX;
    setBoundaryFlag(position, top_left, bottom_right);
    if (boundary_flag != 0) {
        if (position.x < top_left.x)
            position.x = top_left.x;
        else if (position.x > bottom_right.x)
            position.x = bottom_right.x;
        if (position.y > top_left.y)
            position.y = top_left.y;
        else if (position.y < bottom_right.y)
            position.y = bottom_right.y;
    }
}

evol::Vector MapObject::top_left;
evol::Vector MapObject::bottom_right;


void MapObject::set_boundaries(const Environment &world) {
    top_left = world.tl_bound;
    bottom_right = world.br_bound;
}

