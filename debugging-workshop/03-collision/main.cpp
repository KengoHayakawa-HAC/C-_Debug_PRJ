#include "cases.hpp"

int main() {
    return console::menu(run_cases, [] {
        std::vector<int> v;
        if (!console::read("Ax Ay 半径A Bx By 半径B (座標:-1000～1000、半径:0～1000)",
                           {-1000,-1000,0,-1000,-1000,0}, {1000,1000,1000,1000,1000,1000}, v)) return false;
        const bool actual = collision::overlaps({v[0],v[1],v[2]}, {v[3],v[4],v[5]});
        std::cout << "入力: A=(" << v[0] << ',' << v[1] << ", r=" << v[2]
                  << ") B=(" << v[3] << ',' << v[4] << ", r=" << v[5] << ")\n";
        std::cout << "実際の判定: " << (actual ? "当たっている (1)" : "当たっていない (0)")
                  << "\n期待する判定を図や数式で確認しましょう。\n";
        return true;
    });
}
