#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace console {
inline void setup() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}
// Read a complete line. EOF ends input without looping forever.
inline bool read(const std::string& prompt, const std::vector<int>& low,
                 const std::vector<int>& high, std::vector<int>& values) {
    while (true) {
        std::cout << prompt << "\n> ";
        std::string line;
        if (!std::getline(std::cin, line)) return false;
        std::istringstream input(line);
        values.assign(low.size(), 0);
        bool valid = true;
        for (std::size_t i = 0; i < low.size(); ++i) {
            if (!(input >> values[i]) || values[i] < low[i] || values[i] > high[i]) {
                valid = false;
                break;
            }
        }
        std::string extra;
        if (valid && !(input >> extra)) return true;
        std::cout << "入力を確認してください。指定個数の整数を範囲内で入力します。\n";
    }
}
template<class Samples, class Custom>
int menu(Samples samples, Custom custom) {
    setup();
    samples();
    std::vector<int> choice;
    while (read("1: 用意されたケースを再実行  2: 自分で入力  0: 終了", {0}, {2}, choice)) {
        if (choice[0] == 0) break;
        if (choice[0] == 1) samples();
        if (choice[0] == 2 && !custom()) break;
    }
    return 0;
}
template<class T>
bool compare(const char* name, const T& expected, const T& actual) {
    const bool ok = expected == actual;
    std::cout << "ケース: " << name << "\n期待: " << expected << "\n実際: " << actual
              << "\n結果: " << (ok ? "PASS" : "FAIL (仕様との差があります)") << "\n\n";
    return ok;
}
inline int summary(int passed, int total) {
    std::cout << passed << "/" << total << " ケース成功\n";
    return passed == total ? 0 : 1;
}
}
