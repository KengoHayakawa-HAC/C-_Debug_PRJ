#pragma once
namespace collision {
struct Circle { int x; int y; int radius; };
bool overlaps(Circle a, Circle b);
}
