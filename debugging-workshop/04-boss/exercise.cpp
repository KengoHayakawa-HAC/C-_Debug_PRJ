#include "exercise.hpp"
#include <stdexcept>

namespace boss {
Enemy::Enemy() {
    configure();
}

std::string Enemy::attack() const {
    return "Normal attack";
}

int Enemy::power() const {
    return power_;
}

void Enemy::configure() {
    power_ = 10;
}

Boss::Boss() = default;

std::string Boss::attack() const {
    return "Laser attack";
}

void Boss::configure() {
    power_ = 100;
}

void EnemyManager::add(std::unique_ptr<Enemy> enemy) {
    if (!enemy) throw std::invalid_argument("enemy must not be null");
    enemies_.push_back(*enemy);
}

std::size_t EnemyManager::size() const {
    return enemies_.size();
}

std::string EnemyManager::attack(std::size_t index) const {
    return enemies_.at(index).attack();
}

int EnemyManager::power(std::size_t index) const {
    return enemies_.at(index).power();
}
}
