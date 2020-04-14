#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "utils.h"

/**
 * @brief Класс Environment -- среда с объектами
 */
class Environment {
public:
    Environment(evol::Vector top_left_, evol::Vector bottom_right_);
    evol::Vector tl_bound; /** 2D-координата левой верхней границы среды */
    evol::Vector br_bound; /** 2D-координата правой нижней границы среды */
};

#endif // ENVIRONMENT_H
