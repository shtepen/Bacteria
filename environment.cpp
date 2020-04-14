#include "environment.h"

/**
 * @brief Environment::Environment -- конструктор прямоугольной среды
 * @param top_left_ -- левая верхняя граница
 * @param bottom_right_ -- правая нижняя граница
 */
Environment::Environment(evol::Vector top_left_, evol::Vector bottom_right_) {
    tl_bound = top_left_;
    br_bound = bottom_right_;
}
