#include "cases.hpp"

int main() {
    console::setup();
    std::cout << "課題05: std::moveしたのにコピーが発生する\n"
              << "転送先の構築中の履歴と回数を表示します。\n\n";
    std::cout << "--- 転送操作の回数 ---\n";
    run_transfer();
    std::cout << "\n--- 転送先データの内容 ---\n";
    run_data();
    std::cout << "\nコピー回数0、ムーブ回数1、全データ一致が期待されます。\n";
    return 0;
}
