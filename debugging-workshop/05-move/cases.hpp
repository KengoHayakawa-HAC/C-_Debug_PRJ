#pragma once
#include "exercise.hpp"
#include "../common/console.hpp"

inline std::vector<std::vector<int>> inputs() {
    return {{}, {7}, {3,1,4,1,5}, {-5,0,5}, std::vector<int>(4096, 42)};
}

inline int run_transfer() {
    int passed = 0;
    for (const auto& input : inputs()) {
        std::cout << "入力要素数: " << input.size() << '\n';
        const auto report = resource::run_transfer(input);
        passed += console::compare("転送操作のコピー回数", 0, report.operations.copies);
        passed += console::compare("転送操作のムーブ回数", 1, report.operations.moves);
    }
    return console::summary(passed, 10);
}

inline int run_data() {
    int passed = 0;
    for (const auto& input : inputs()) {
        std::cout << "入力要素数: " << input.size() << '\n';
        const auto report = resource::run_transfer(input);
        passed += console::compare("全要素と順序が一致", true, report.data == input);
    }
    return console::summary(passed, 5);
}
