# 運営者用解答：02：敵の追尾

参加者向けに配布しない資料です。以下は仕様を満たす修正例であり、同じコードだけが正解ではありません。

不具合は、y軸に渡す目標座標の取り違えと、残り距離にかかわらず2移動することです。

- 敵(0,3)、プレイヤー(4,3)：1歩後の期待(2,3)、配布版(2,5)。
- 敵(0,0)、プレイヤー(1,1)：期待は到着後停止。配布版は(2,2)と(0,0)を往復。

y軸には `player.y` を渡します。各軸で距離が2未満なら目標位置へ移動し、一致していれば動きません。斜めの速度の正規化は今回の仕様外です。

確認：`ctest --test-dir build-advanced --output-on-failure -R '^chase_spec$'`。24/24判定が成功します。横のみ・縦のみ・負座標・到着後も調べます。

## 修正例

以下のパスは `debugging-workshop/` からの相対パスです。運営者の別コピーで該当ファイルを置き換えて検証できます。公開テストは変更しません。

### `02-chase/exercise.cpp`

```cpp
#include "exercise.hpp"

namespace {
int move_axis(int current, int target) {
    if (current < target) return target - current < 2 ? target : current + 2;
    if (current > target) return current - target < 2 ? target : current - 2;
    return current;
}
}

chase::Point chase::step(Point enemy, Point player) {
    enemy.x = move_axis(enemy.x, player.x);
    enemy.y = move_axis(enemy.y, player.y);
    return enemy;
}
```
