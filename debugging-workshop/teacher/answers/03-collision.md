# 運営者用解答：03：円の当たり判定

参加者向けに配布しない資料です。以下は仕様を満たす修正例であり、同じコードだけが正解ではありません。

不具合は、半径の合計の2乗を各半径の2乗の和にしていることと、接触時の等号を含めないことです。

- 中心(0,0)と(3,0)、半径は両方2：重なるが配布版は非衝突。距離の2乗9を誤った閾値8と比較しています。
- 半径0の点(0,0)、中心(2,0)・半径2の円：円周上なので衝突だが配布版は非衝突。これは等号の問題を独立して観察できます。

比較は `dx*dx + dy*dy <= (rA+rB)*(rA+rB)` です。入力範囲は各座標−1000～1000、半径0～1000なので今回の整数演算は範囲内に収まります。

確認：`ctest --test-dir build-advanced --output-on-failure -R '^collision_spec$'`。26/26判定が成功します。浅い重なり、接触、接触の外側、半径0、A/B交換を確認します。

## 修正例

以下のパスは `debugging-workshop/` からの相対パスです。運営者の別コピーで該当ファイルを置き換えて検証できます。公開テストは変更しません。

### `03-collision/exercise.cpp`

```cpp
#include "exercise.hpp"

bool collision::overlaps(Circle a, Circle b) {
    const int dx = a.x - b.x;
    const int dy = a.y - b.y;
    const int distance_squared = dx * dx + dy * dy;
    const int reach_squared = (a.radius + b.radius) * (a.radius + b.radius);
    return distance_squared <= reach_squared;
}
```
