#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "utils.h"

class Environment {
public:
    Environment(evol::Vector top_left_, evol::Vector bottom_right_);
    evol::Vector tl_bound;
    evol::Vector br_bound;
};

#endif // ENVIRONMENT_H
