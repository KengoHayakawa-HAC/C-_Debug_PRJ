#include "exercise.hpp"

int hp::damage(int current, int amount) {
    return current - amount;
}

int hp::heal(int current, int maximum, int amount) {
    (void)maximum;
    return current + amount;
}
