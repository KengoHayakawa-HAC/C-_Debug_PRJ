#pragma once
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace boss {
class Enemy {
public:
    Enemy();
    virtual ~Enemy() = default;
    virtual std::string attack() const;
    int power() const;
protected:
    virtual void configure();
    int power_ = 0;
};

class Boss : public Enemy {
public:
    Boss();
    std::string attack() const override;
protected:
    void configure() override;
};

class EnemyManager {
public:
    void add(std::unique_ptr<Enemy> enemy);
    std::size_t size() const;
    std::string attack(std::size_t index) const;
    int power(std::size_t index) const;
private:
    std::vector<Enemy> enemies_;
};
}
