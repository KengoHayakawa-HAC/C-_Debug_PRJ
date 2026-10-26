# 運営者用解答：05：std::moveしたのにコピーが発生する

参加者向けに配布しない資料です。以下は仕様を満たす修正例であり、同じコードだけが正解ではありません。

`std::move` はムーブ処理そのものではなく、式を右辺値として扱うためのキャストです。`const` は取り除きません。

配布コードの転送元と受け取り側は変更禁止です。`std::move(source)` は `const Resource&&` となり、変更可能な `Resource&&` を要求するムーブコンストラクタには渡せません。一方、コピーコンストラクタの `const Resource&` は受け取れるため、コピー1回・ムーブ0回になります。

例では転送元の `const` を外し、APIを `Resource transfer(Resource&& source)` に変更します。宣言と定義を合わせて変更します。元データを転送後に利用しない契約に基づく設計で、`const_cast` は使いません。`const` を外すだけで引数側の制約を残しても解決しません。

計測は転送元の準備後にリセットし、転送先の構築直後に読み取ります。この位置、コンストラクタのカウンタ、データ処理は変更しません。入力準備と確認用レポートへのvectorコピーは計測外です。

`return Resource(std::move(source));` では名前のある既存オブジェクトから1回構築します。そのprvalueから転送先までの余分な構築はC++17で省略されるため、任意のNRVOに回数を依存させていません。ムーブ後の元データが必ず空とは仮定しません。

確認：`ctest --preset advanced -R '^move_'`。転送回数10/10、データ5/5が成功し、各入力でコピー0回・ムーブ1回、全データ一致になります。値渡し等の別APIでは回数の契約が変わる場合があるため、今回の1回転送とは区別して議論します。

## 修正例

以下のパスは `debugging-workshop/` からの相対パスです。運営者の別コピーで該当ファイルを置き換えて検証できます。公開テストは変更しません。

### `05-move/exercise.cpp`

```cpp
#include "exercise.hpp"
#include <cstdio>
#include <utility>

namespace resource {
Resource::Resource(std::vector<int> data) : data_(std::move(data)) {}

Resource::Resource(const Resource& other) : data_(other.data_) {
    ++counts_.copies;
    std::puts("Resource(const Resource&) : COPY");
}

Resource::Resource(Resource&& other) noexcept : data_(std::move(other.data_)) {
    ++counts_.moves;
    std::puts("Resource(Resource&&) : MOVE");
}

const std::vector<int>& Resource::data() const {
    return data_;
}

void Resource::reset_counts() {
    counts_ = {};
}

Counts Resource::counts() {
    return counts_;
}

Resource transfer(Resource&& source) {
    return Resource(std::move(source));
}

TransferReport run_transfer(const std::vector<int>& input) {
    Resource source(input);
    // Measurement covers construction of the destination Resource only.
    Resource::reset_counts();
    Resource destination = transfer(std::move(source));
    const Counts measured = Resource::counts();
    // Exporting the report is outside the measurement interval.
    return {measured, destination.data()};
}
}
```

### `05-move/exercise.hpp`

```cpp
#pragma once
#include <vector>

namespace resource {
struct Counts {
    int copies = 0;
    int moves = 0;
};

class Resource {
public:
    explicit Resource(std::vector<int> data);
    Resource(const Resource& other);
    Resource(Resource&& other) noexcept;
    const std::vector<int>& data() const;
    static void reset_counts();
    static Counts counts();
private:
    std::vector<int> data_;
    inline static Counts counts_{};
};

struct TransferReport {
    Counts operations;
    std::vector<int> data;
};

Resource transfer(Resource&& source);
TransferReport run_transfer(const std::vector<int>& input);
}
```
