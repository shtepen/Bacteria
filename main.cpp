#include "bacteria.h"
#include "food.h"
#include "environment.h"
#include <iostream>

int main() {
    using namespace evol;
    Environment w1({0.0, 10.0}, {10.0, 0.0});
    Bacteria b1({1.0, 9.0}, 2.0, 3 * M_PI/4, 10.0);         //position, radius, angle, velocity
    b1.set_boundaries(w1);
//    Food f1({3.0, 2.0}, 1.0, 0.0), f2({4.0, 1.0}, 1.5, 0.0);
//    f1.set_boundaries(w1);
    std::cout << "Boundaries are: top left (" << b1.top_left.x << ", " << b1.top_left.y << "); bottom right ("
              << b1.bottom_right.x << ", " << b1.bottom_right.y << ");\n";
   /* std::cout << "Bacteria has eaten " << b1.food_collected << " nutritions\n";
    std::cout << "Bacteria can " << (b1.canEat(f1) ? "" : "not") << " eat food1\n";
    std::cout << "Bacteria has eaten " << b1.food_collected << " nutritions\n";
    std::cout << "Bacteria can " << (b1.canEat(f2) ? "" : "not") << " eat food2\n";
    std::cout << "Bacteria has eaten " << b1.food_collected << " nutritions\n";
*/
//    b1.reflect(1);
    std::cout << "Direction in rad of bacteria with coordinates (" << b1.position.x << ", "
              << b1.position.y <<") is " << b1.angle / M_PI << "PI\n";
    std::cout << "Movement value is " << b1.movement_value << std::endl;
    b1.active_motion(b1.top_left, b1.bottom_right);
    std::cout << "Direction in rad of bacteria with coordinates (" << b1.position.x << ", "
              << b1.position.y <<") is " << b1.angle / M_PI << "PI\n";
    return 0;
}
