#ifndef BACTERIA_H
#define BACTERIA_H

#include "mapobject.h"
#include "food.h"

/**
 * @brief Класс Bacteria -- объект на карте, способный активно двигаться и поглощать питательные вещества
 */
class Bacteria : public MapObject {
public:
    Bacteria(evol::Vector position_, double radius_, double angle_, double velocity_);
    bool canEat(Food& f);  /** Проверяет, может ли бактерия съесть данный кусок пищи */
    void step() override;  /** Реализует функцию движения, объединяющую реактивное и броуновское двиения */
    double get_movement_value(); /** Рассчитывает длину шага */
    double get_food_collected();

    static void bactest();

private:
    double velocity; /** Скорость движения бактерии, влияет на длину шага */
    double movement_value; /** Длина шага */
    double food_collected{0.0}; /** Собранные данной бактерией за  всю эмуляцию питательные вещества */

    void active_motion(evol::Vector tl, evol::Vector br); /** Осуществляет активное движение в заданном направлении */
    double first_bound_cross(evol::Vector br_b, evol::Vector tl_b); /** Определяет, какая граница была преодолена
                                                                      * раньше при переходе за пределы среды                                                                      */
};

#endif // BACTERIA_H
