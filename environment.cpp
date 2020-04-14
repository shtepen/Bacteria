#include "environment.h"

Environment::Environment(evol::Vector top_left_, evol::Vector bottom_right_) {
    tl_bound = top_left_;
    br_bound = bottom_right_;
}
