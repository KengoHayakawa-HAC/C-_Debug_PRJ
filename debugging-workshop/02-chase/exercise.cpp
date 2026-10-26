#include "exercise.hpp"

namespace {
int move_axis(int current, int target) {
    if (current < target) return current + 2;
    if (current > target) return current - 2;
    return current;
}
}

chase::Point chase::step(Point enemy, Point player) {
    enemy.x = move_axis(enemy.x, player.x);
    enemy.y = move_axis(enemy.y, player.x);
    return enemy;
}
