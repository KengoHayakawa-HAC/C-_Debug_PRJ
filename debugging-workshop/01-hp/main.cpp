#include "cases.hpp"

int main() {
    return console::menu(run_cases, [] {
        std::vector<int> v;
        if (!console::read("最大HP (1～1000)", {1}, {1000}, v)) return false;
        const int maximum = v[0];
        if (!console::read("現在HP、操作 (0:ダメージ / 1:回復)、量を空白区切りで入力。量は0～1000。",
                           {0, 0, 0}, {maximum, 1, 1000}, v)) return false;
        std::cout << "入力: HP=" << v[0] << " 最大HP=" << maximum << " 操作=" << v[1] << " 量=" << v[2] << '\n';
        const int actual = v[1] == 1 ? hp::heal(v[0], maximum, v[2]) : hp::damage(v[0], v[2]);
        std::cout << "実際のHP: " << actual << " (期待値は仕様から自分で計算しましょう)\n";
        return true;
    });
}
