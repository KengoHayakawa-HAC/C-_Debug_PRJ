#include "cases.hpp"

int main() {
    console::setup();
    std::cout << "課題04: ボスキャラクターの能力が消える\n"
              << "攻撃の種類と生成時の威力を別々に観察します。\n\n";
    std::cout << "--- 管理システムを通す前と後 ---\n";
    run_storage();
    std::cout << "\n--- 初期化直後の能力 ---\n";
    run_initialization();
    std::cout << "\n観察用プログラムです。合否判定はCTestで確認してください。\n";
    return 0;
}
