#pragma once
#include "exercise.hpp"
#include "../common/console.hpp"

inline int run_storage() {
    using namespace boss;
    int passed = 0;
    Enemy normal;
    Boss leader;
    passed += console::compare("通常敵を直接操作", std::string("Normal attack"), normal.attack());
    passed += console::compare("ボスを直接操作", std::string("Laser attack"), leader.attack());
    EnemyManager manager;
    passed += console::compare("登録前の件数", std::size_t{0}, manager.size());
    manager.add(std::make_unique<Enemy>());
    manager.add(std::make_unique<Boss>());
    manager.add(std::make_unique<Boss>());
    passed += console::compare("混在登録後の件数", std::size_t{3}, manager.size());
    passed += console::compare("登録した通常敵", std::string("Normal attack"), manager.attack(0));
    passed += console::compare("登録したボス1", std::string("Laser attack"), manager.attack(1));
    passed += console::compare("登録したボス2", std::string("Laser attack"), manager.attack(2));
    return console::summary(passed, 7);
}

inline int run_initialization() {
    using namespace boss;
    int passed = 0;
    Enemy normal;
    Boss leader;
    passed += console::compare("通常敵の生成直後の威力", 10, normal.power());
    passed += console::compare("ボスの生成直後の威力", 100, leader.power());
    leader.attack();
    passed += console::compare("攻撃しても威力は変わらない", 100, leader.power());
    EnemyManager manager;
    manager.add(std::make_unique<Enemy>());
    manager.add(std::make_unique<Boss>());
    passed += console::compare("管理中の通常敵の威力", 10, manager.power(0));
    passed += console::compare("管理中のボスの威力", 100, manager.power(1));
    return console::summary(passed, 5);
}
