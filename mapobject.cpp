#include "mapobject.h"
#include <cassert>

/**
 * @brief MapObject::MapObject -- конструктор объекта в среде
 * @param position_ -- положение в среде
 * @param radius_ -- линейный размер объекта
 * @param angle_ -- направление движения объекта
 */
MapObject::MapObject(evol::Vector position_, double radius_, double angle_) {
    assert(position_.x >= top_left.x);
    assert(position_.x <= bottom_right.x);
    assert(position_.y <= top_left.y);
    assert(position_.y >= bottom_right.y);
    position = position_;
    assert(radius_ > 0);
    radius = radius_;
    assert(angle_ >= 0);
    assert(angle_ <= 2 * M_PI);
    angle = angle_;
}

/**
 * @brief MapObject::get_position -- возвращает положение объекта в среде
 * @return 2D-координата объекта
 */
evol::Vector MapObject::get_position() {
    return position;
}

/**
 * @brief MapObject::get_radius -- возвращает линейный размер объекта
 * @return линейный размер объекта (радиус круглого объекта)
 */
double MapObject::get_radius() {
    return radius;
}

/**
 * @brief MapObject::get_angle -- возвращает направление движения
 * @return направление движения объекта в радианах
 */
double MapObject::get_angle() {
    return angle;
}

/**
 * @brief MapObject::setBoundaryFlag -- изменяет boundary_flag -- информацию, пересёк ли
 *        объект границы среды, и если да, то какие: горизонтальные или вертикальные
 * @param curr_pos -- текущая (или предполагаемая) позиция объекта
 * @param tl_b -- левая верхняя граница среды
 * @param br_b -- правая нижняя граница среды
 */
void MapObject::setBoundaryFlag(evol::Vector curr_pos, evol::Vector tl_b, evol::Vector br_b) {
    if ((curr_pos.y > tl_b.y) || (curr_pos.y < br_b.y))
        boundary_flag = 1;
    else if ((curr_pos.x < tl_b.x) || (curr_pos.x > br_b.x))
        boundary_flag = -1;
    else boundary_flag = 0;
}

/**
 * @brief MapObject::brownian_motion -- реализация броуновского движения объектов
 */
void MapObject::brownian_motion() {
    position.x += cos(angle) * movement_const / radius; /** Движение на соответственную величину в старом направлении */
    position.y += sin(angle) * movement_const / radius;
    angle = 2 * M_PI * rand() / RAND_MAX; /** Случайное изменение угла на угол от 0 до 2 * M_PI */
    setBoundaryFlag(position, top_left, bottom_right); /** Вычисляем, не вышел ли объект за пределы среды */
    if (boundary_flag != 0) { /** Если да, смещаем до ближайшей границы */
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

evol::Vector MapObject::top_left{0.0, 100.0};
evol::Vector MapObject::bottom_right{100.0, 0.0};

// /**
// * @brief MapObject::set_boundaries -- сопоставляем объектам их мир
// * @param world -- мир с заданными границами
// */
//void MapObject::set_boundaries(const Environment &world) {
//    top_left = world.tl_bound;
//    bottom_right = world.br_bound;
//}

