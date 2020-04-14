#ifndef MAPOBJECT_H
#define MAPOBJECT_H
#include "utils.h"
#include <cmath>
//#include <math.h>
#include "environment.h"

/**
 * @brief Класс MapObject -- объекты среды любого типа
 */

class MapObject {

public:
    MapObject(evol::Vector position_, double radius_, double angle_);
    double movement_const{1.0}; /** Постоянная для расчёта продвижения за один шаг */

    static evol::Vector top_left; /** 2D-координаты левой верхней границы среды */
    static evol::Vector bottom_right; /** 2D-координаты правой нижней границы среды */
//    static void set_boundaries(const Environment& world); /** Сопоставляет характеристики мира (координаты) данным созданиям */

    evol::Vector get_position(); /** Возвращает текущее положение объекта */
    double get_radius(); /** Возвращает линейный размер объекта */
    double get_angle(); /** Возвращает направление движения объекта в радианах */

    virtual void step() = 0; /** Осуществляет перемещение объекта за один шаг эмуляции */
    virtual ~MapObject() = default;

protected:
    evol::Vector position; /** Текущее положение объекта, 2D-координата */
    double radius; /** Линейный размер объекта */
    double angle; /** Направление движения объекта в радианах */

    int boundary_flag{0}; /** boundary flag = 0, если объект находится в пределах среды,
                            * 1 -- если за горизонтальной границей, -1 -- за вертикальной границей
                            */

    void setBoundaryFlag(evol::Vector curr_pos, evol::Vector tl_b, evol::Vector br_b); /** Расчитывает boundary_flag для текущего положения */
    void brownian_motion(); /** Осуществляет броуновское движение объекта */

    char a[4]; /** Ничего не делает, для избегания ошибки padding_align */
};

#endif // MAPOBJECT_H
