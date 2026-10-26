#pragma once
#include <ostream>
namespace chase {
struct Point { int x; int y; };
inline bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }
inline std::ostream& operator<<(std::ostream& out, Point p) {
    return out << '(' << p.x << ", " << p.y << ')';
}
Point step(Point enemy, Point player);
}
