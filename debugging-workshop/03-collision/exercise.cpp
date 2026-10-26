#include "exercise.hpp"

bool collision::overlaps(Circle a, Circle b) {
    const int dx = a.x - b.x;
    const int dy = a.y - b.y;
    const int distance_squared = dx * dx + dy * dy;
    const int reach_squared = a.radius * a.radius + b.radius * b.radius;
    return distance_squared < reach_squared;
}
