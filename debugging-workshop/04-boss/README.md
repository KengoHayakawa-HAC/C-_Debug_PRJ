# 課題04：ボスキャラクターの能力が消える

## Visual Studioの.slnで実行する

教材ルートの [DebuggingWorkshop.sln](../DebuggingWorkshop.sln) を開き、`Debug / x64` でソリューションをビルドします。`boss_demo` をスタートアッププロジェクトに設定し、Ctrl+F5で実行してください。

修正を保存・再ビルドした後、Developer PowerShellで `debugging-workshop` からテストします。

```powershell
ctest --test-dir visual-studio -C Debug --output-on-failure -R '^boss_'
```

Releaseでビルドした場合は `-C Release` にします。詳しくは[共通手順](../README.md)を参照してください。以下にあるプリセット・`build-advanced`・`build-hp`等を使うコマンドは、別方式のCMakeビルド用です。

上級の発展課題です。課題01～03の完了は前提ではありません。

## ストーリーと仕様

通常敵とボスがいます。ボスを直接操作すると特殊攻撃をしますが、敵管理システムに登録した後の動きに違和感があります。生成直後の能力も調べてください。

| 種類 | 直接呼び出した攻撃 | 管理経由の攻撃 | 生成完了直後の威力 |
|---|---|---|---:|
| 通常敵 `Enemy` | `Normal attack` | `Normal attack` | 10 |
| ボス `Boss` | `Laser attack` | `Laser attack` | 100 |

- 管理システムには通常敵とボスを混在して登録でき、登録順を維持します。
- 登録後も各オブジェクトの攻撃と威力を保持します。呼び出し側による種類の判別や、テスト専用の分岐は不要な設計にしてください。
- 構築が完了した時点で能力設定が完了している必要があります。初めて攻撃したときに設定する仕様ではありません。
- `attack()` は能力を変更せず、攻撃の名前を返します。
- `add` に渡す `unique_ptr` の所有権は管理側へ渡ります。渡した側がそのポインタを使い続けることは想定しません。管理側は安全に寿命を管理してください。
- 今回のテストは有効な登録位置を使います。nullの登録は `std::invalid_argument`、範囲外の参照は `std::out_of_range` になる既存の保護処理を維持します。

## 実行・ビルド

Visual Studio 2022で教材ルート `debugging-workshop` を開き、構成に **`advanced`** を選択して「すべてビルド」。スタートアップ項目を `boss_demo.exe` にし、Ctrl+F5で実行します。構成が見えない場合はフォルダーを開き直してください。

コマンドの場合はWindowsのDeveloper PowerShell、Linuxのターミナルで、教材ルートから次を実行します。

```sh
cmake --preset advanced
cmake --build --preset advanced --parallel 2
ctest --preset advanced -R '^boss_'
```

Windowsでの実行：`.\build-advanced\04-boss\boss_demo.exe`

Linuxでの実行：`./build-advanced/04-boss/boss_demo`

デモは決められた比較を表示して終了します。01～03のような入力メニューはありません。VSのCtrl+F5または既に開いたターミナルから実行して結果を読みます。表示のFAILがあってもデモは終了コード0です。合否はテストで確認してください。

単独ビルド（教材ルートから）：

```sh
cmake -S 04-boss -B build-boss -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-boss --parallel 2
ctest --test-dir build-boss --output-on-failure
```

この場合の実行ファイルはWindowsでは `build-boss\boss_demo.exe`、Linuxでは `build-boss/boss_demo` です。配布には `common/` を含む教材フォルダー全体を使います。

## 観察とテスト

`exercise.hpp` にクラスの形、`exercise.cpp` に動作があります。両方を修正できます。`main.cpp` は表示、`cases.hpp` と `tests.cpp` は仕様の確認です。公開テストは変更しません。

| CTest名 | 確認すること | 初期状態 |
|---|---|---|
| `boss_storage` | 直接操作・管理経由の攻撃、混在登録と件数 | 失敗 |
| `boss_initialization` | 直接生成直後・管理中の威力、攻撃前後の安定性 | 失敗 |

```sh
ctest --preset advanced -R '^boss_storage$'
ctest --preset advanced -R '^boss_initialization$'
```


VSでテストを直接実行する場合、Developer PowerShellから `.\build-advanced\04-boss\boss_tests.exe storage` または末尾を `initialization` にして実行します。引数がない・不正な場合は終了コード2になります。通常はCTestを利用してください。

## 完了条件

- 2つのテストが成功し、上の表の動作を満たす。
- 「どの時点で、どのオブジェクトのどの処理が実行されたか」をC++の仕様に基づいて説明する。
- 修正後の所有権と破棄のタイミングを説明する。生ポインタの放置、解放後の参照、型名に応じた攻撃の決め打ちは解決にしない。

## 発展問題

- `std::unique_ptr` で多態的なオブジェクトを所有する場合、コピーしたい管理システムはどう設計するか。
- `override` は何をコンパイル時に確認するか。付けただけで今回の仕様をすべて満たせるか。
- 基底クラスのポインタを通して破棄する場合、仮想デストラクタはなぜ必要か。危険なコードを実行せず仕様で説明する。
- 値で保存する設計とポインタで保存する設計の、コピー・寿命・所有権の違いを比較する。
- 3種類目の敵を追加するなら、管理システムやテストはどこを変えるか。

[前提知識](../docs/advanced-primer.md)
