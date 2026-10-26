# 運営者用解答：04：ボスキャラクターの能力が消える

参加者向けに配布しない資料です。以下は仕様を満たす修正例であり、同じコードだけが正解ではありません。

**問題A1：オブジェクトスライシング**

`Boss` を `std::vector<Enemy>` にコピーすると、保存されるのは基底部分から構築された `Enemy` オブジェクトです。管理経由の攻撃は `Normal attack` となります。元の `Boss` に `virtual` や `override` があっても、保存されたオブジェクトはボスではありません。

保存先を `std::vector<std::unique_ptr<Enemy>>` にし、渡された所有権を管理側へ移します。参照時は `->` を使います。既存の仮想デストラクタとnullチェックを維持します。生ポインタを放置する方法は採用しません。

**問題A2：構築中の仮想関数呼び出し**

`Enemy` のコンストラクタから呼ばれる `configure()` は `Enemy::configure()` です。基底の構築中に、より派生した `Boss` の処理へディスパッチされません。これは未定義動作ではなく言語の構築規則です。直接生成したボスでも威力が100ではなく10になります。

例では `Boss` のコンストラクタ本体から `configure()` を呼びます。この時点では `Boss::configure()` が実行されます。より明示的な設計として、初期能力値を基底コンストラクタへ渡し、構築時の仮想呼び出しに依存しない設計も可能です。

A1だけの修正で `boss_storage` が成功し、`boss_initialization` は失敗します。A2だけなら逆になります。両方を直すと、攻撃7/7、初期化5/5が成功します。確認：`ctest --preset advanced -R '^boss_'`。

## 修正例

以下のパスは `debugging-workshop/` からの相対パスです。運営者の別コピーで該当ファイルを置き換えて検証できます。公開テストは変更しません。

### `04-boss/exercise.cpp`

```cpp
#include "exercise.hpp"
#include <stdexcept>
#include <utility>

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

Boss::Boss() {
    configure();
}

std::string Boss::attack() const {
    return "Laser attack";
}

void Boss::configure() {
    power_ = 100;
}

void EnemyManager::add(std::unique_ptr<Enemy> enemy) {
    if (!enemy) throw std::invalid_argument("enemy must not be null");
    enemies_.push_back(std::move(enemy));
}

std::size_t EnemyManager::size() const {
    return enemies_.size();
}

std::string EnemyManager::attack(std::size_t index) const {
    return enemies_.at(index)->attack();
}

int EnemyManager::power(std::size_t index) const {
    return enemies_.at(index)->power();
}
}
```

### `04-boss/exercise.hpp`

```cpp
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
    std::vector<std::unique_ptr<Enemy>> enemies_;
};
}
```
