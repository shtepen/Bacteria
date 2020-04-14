#ifndef FOOD_H
#define FOOD_H

#include "mapobject.h"

/**
 * @brief Класс Food -- питательные частицы с заданной питательной ценностью, участвуют только в броуновском движении
 */
class Food : public MapObject {
public:
    Food(evol::Vector position_, double radius_, double angle_);
    void step() override; /** Реализует перемещение частицы за шаг эмуляции, содержит броунвское движение */
    double nutrition_value; /** Питательная ценность данной частицы */
    bool is_eaten{false}; /** Флаг проверки, съедена ли частица на данный момент */

    char b[7]; /** Ничего не делает, нужна для устранения warning'a о padding_align */

private:
    double nutr_const{5.0}; /** Константа, участвующая в формуле расчета питательной ценности частицы */

};

#endif // FOOD_H
