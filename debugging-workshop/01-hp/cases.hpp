#pragma once
#include "exercise.hpp"
#include "../common/console.hpp"

inline int run_cases() {
    struct Case { const char* name; bool healing; int current, maximum, amount, expected; };
    const Case cases[] = {
        {"通常のダメージ", false, 80, 100, 30, 50},
        {"HPと同じダメージ", false, 30, 100, 30, 0},
        {"HPを超えるダメージ", false, 20, 100, 35, 0},
        {"HPゼロへのダメージ", false, 0, 100, 1, 0},
        {"通常の回復", true, 40, 100, 20, 60},
        {"最大HPを超える回復", true, 80, 100, 30, 100},
        {"最大HPでの回復", true, 100, 100, 1, 100},
        {"HPゼロからの回復", true, 0, 100, 10, 10},
        {"回復量ゼロ", true, 60, 100, 0, 60},
        {"ダメージ量ゼロ", false, 60, 100, 0, 60},
        {"最大HPが1", true, 0, 1, 2, 1}
    };
    int passed = 0;
    for (const auto& c : cases) {
        std::cout << "入力: HP=" << c.current << " 最大HP=" << c.maximum
                  << (c.healing ? " 回復=" : " ダメージ=") << c.amount << '\n';
        const int actual = c.healing ? hp::heal(c.current, c.maximum, c.amount)
                                     : hp::damage(c.current, c.amount);
        passed += console::compare(c.name, c.expected, actual);
    }
    return console::summary(passed, 11);
}
