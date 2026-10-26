#pragma once
#include "exercise.hpp"
#include "../common/console.hpp"

inline int run_cases() {
    using chase::Point;
    struct Case { const char* name; Point enemy, player; std::vector<Point> expected; };
    const Case cases[] = {
        {"右上へ2ずつ", {0,0}, {4,4}, {{2,2},{4,4},{4,4}}},
        {"左下へ2ずつ", {4,4}, {0,0}, {{2,2},{0,0},{0,0}}},
        {"横方向のみ", {0,3}, {4,3}, {{2,3},{4,3},{4,3}}},
        {"縦方向のみ", {3,0}, {3,4}, {{3,2},{3,4},{3,4}}},
        {"残り1の移動", {0,0}, {1,1}, {{1,1},{1,1},{1,1}}},
        {"負の座標から接近", {-4,-4}, {-1,-1}, {{-2,-2},{-1,-1},{-1,-1}}},
        {"既に同じ位置", {2,5}, {2,5}, {{2,5},{2,5},{2,5}}},
        {"軸ごとに逆向き", {4,0}, {0,4}, {{2,2},{0,4},{0,4}}}
    };
    int passed = 0;
    int total = 0;
    for (const auto& c : cases) {
        Point actual = c.enemy;
        std::cout << "入力: 敵=" << actual << " プレイヤー=" << c.player << '\n';
        for (std::size_t i = 0; i < c.expected.size(); ++i) {
            actual = chase::step(actual, c.player);
            std::cout << "ステップ " << i + 1 << '\n';
            passed += console::compare(c.name, c.expected[i], actual);
            ++total;
        }
    }
    return console::summary(passed, total);
}
