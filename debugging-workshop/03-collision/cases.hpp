#pragma once
#include "exercise.hpp"
#include "../common/console.hpp"

inline int run_cases() {
    using collision::Circle;
    struct Case { const char* name; Circle a, b; bool expected; };
    const Case cases[] = {
        {"十分離れている", {0,0,2}, {10,0,2}, false},
        {"深く重なっている", {0,0,2}, {1,0,2}, true},
        {"浅く重なっている", {0,0,2}, {3,0,2}, true},
        {"外側で接している", {0,0,2}, {4,0,2}, true},
        {"接する位置の外側", {0,0,2}, {5,0,2}, false},
        {"同じ中心", {2,-3,2}, {2,-3,5}, true},
        {"包含されている", {0,0,5}, {1,0,1}, true},
        {"斜めに接している", {0,0,2}, {3,4,3}, true},
        {"負の座標", {-5,-5,2}, {-2,-5,2}, true},
        {"半径ゼロの点が円周上", {0,0,0}, {2,0,2}, true},
        {"同じ点同士", {0,0,0}, {0,0,0}, true},
        {"別の点同士", {0,0,0}, {1,0,0}, false},
        {"入力範囲の端", {-1000,-1000,1000}, {1000,1000,1000}, false}
    };
    int passed = 0;
    int total = 0;
    for (const auto& c : cases) {
        std::cout << "入力: A=(" << c.a.x << ',' << c.a.y << ", r=" << c.a.radius
                  << ") B=(" << c.b.x << ',' << c.b.y << ", r=" << c.b.radius << ")\n";
        passed += console::compare(c.name, c.expected, collision::overlaps(c.a,c.b));
        passed += console::compare("A/Bを入れ替えた判定", c.expected, collision::overlaps(c.b,c.a));
        total += 2;
    }
    return console::summary(passed, total);
}
