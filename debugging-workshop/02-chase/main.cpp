#include "cases.hpp"

int main() {
    return console::menu(run_cases, [] {
        std::vector<int> v;
        if (!console::read("敵x 敵y プレイヤーx プレイヤーy ステップ数 (座標:-1000～1000、回数:1～20)",
                           {-1000,-1000,-1000,-1000,1}, {1000,1000,1000,1000,20}, v)) return false;
        chase::Point enemy{v[0],v[1]};
        const chase::Point player{v[2],v[3]};
        std::cout << "初期位置: " << enemy << " プレイヤー: " << player << '\n';
        for (int i = 1; i <= v[4]; ++i) {
            enemy = chase::step(enemy, player);
            std::cout << "ステップ " << i << ": " << enemy << '\n';
        }
        std::cout << "期待する経路を仕様から計算して比較しましょう。\n";
        return true;
    });
}
