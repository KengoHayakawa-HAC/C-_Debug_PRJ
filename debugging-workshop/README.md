# C++デバッグ課題

C++17のコンソールプログラムを使い、仕様と実行結果を比較して不具合を修正する教材です。各課題は独立しています。

**初期状態はコンパイルに成功し、一部の自動テストに失敗します。意図された課題の状態です。** 仕様を満たす修正であれば、実装方法は複数認められます。公開テストの期待値や計測処理を変更せず取り組んでください。

## 課題一覧

| 課題 | 難易度 | 実行ターゲット |
|---|---|---|
| [01：HP計算](01-hp/README.md) | 初級 | `hp_demo.exe` |
| [02：敵の追尾](02-chase/README.md) | 中級 | `chase_demo.exe` |
| [03：円の当たり判定](03-collision/README.md) | 上級 | `collision_demo.exe` |
| [04：ボスキャラクターの能力が消える](04-boss/README.md) | 上級・発展 | `boss_demo.exe` |
| [05：std::moveしたのにコピーが発生する](05-move/README.md) | 上級・発展 | `move_demo.exe` |

04・05の基本用語は[前提知識](docs/advanced-primer.md)にまとめています。

## Windows / Visual Studio 2022

1. Visual Studio Installerで「C++によるデスクトップ開発」をインストールします。MSVC v143、Windows SDK、Windows用C++ CMakeツールを含めます。Visual Studio Codeとは別の製品です。
2. GitHubの `distribution` ブランチで「Code → Download ZIP」を選び、書き込み可能な場所へ展開します。
3. Visual Studioで「ファイル → 開く → フォルダー」から **`debugging-workshop`** を開きます。`.sln` の作成は不要です。
4. 構成を **`workshop`（01～03）** または **`advanced`（01～05）** にし、CMakeの構成完了を待ちます。
5. 「ビルド → すべてビルド」を実行します。
6. スタートアップ項目から上表の `*_demo.exe` を選び、**Ctrl+F5** で実行します。
7. 修正後は保存し、実行を停止してから再ビルドします。デバッグ中の停止はShift+F5です。

プリセットが表示されない場合は、開いたフォルダーとVSの更新状態を確認します。「ツール → オプション → CMake」のCMakePresets.json利用設定を確認して開き直してください。表示名はVSの版により異なります。

### コマンドでのビルド・テスト

スタートメニューから **Developer PowerShell for VS 2022** を開き、展開先の教材フォルダーへ移動します。以下の保存先は実際の場所に置き換えます。

```powershell
cd C:\保存先\C-_Debug_PRJ-distribution\debugging-workshop
cmake --preset workshop
cmake --build --preset workshop --parallel 2
.\build\01-hp\hp_demo.exe
ctest --preset workshop
```

04・05を含める場合：

```powershell
cmake --preset advanced
cmake --build --preset advanced --parallel 2
.\build-advanced\04-boss\boss_demo.exe
.\build-advanced\05-move\move_demo.exe
ctest --preset advanced
```

`ctest --preset advanced` は04・05のみをテストします。全5課題を確認する場合は次を使います。

```sh
ctest --test-dir build-advanced --output-on-failure
```

## Linux

C++17対応のg++、CMake 3.20以降、Ninjaが必要です。Ubuntu/Debianでは通常 `sudo apt install g++ cmake ninja-build` で導入できます。

```sh
cd /保存先/C-_Debug_PRJ-distribution/debugging-workshop
cmake --preset workshop
cmake --build --preset workshop --parallel 2
./build/01-hp/hp_demo
ctest --preset workshop
```

発展課題の構成・ビルド・テストコマンドはWindowsと同じです。実行時は `./build-advanced/04-boss/boss_demo`、`./build-advanced/05-move/move_demo` を使います。外部C++ライブラリやAPIキーは不要です。

## 結果の見方

デモには入力・期待値・実際の値が表示されます。`PASS` は一致、`FAIL` は不一致です。円の判定では1が衝突、0が非衝突です。

01～03では表示後にメニューが出ます。`1` は再表示、`2` は任意入力、`0` は終了です。半角整数と半角スペースを使い、画面の入力範囲を守ってください。任意入力では仕様から期待値を自分で計算します。

04・05は固定ケースを表示して終了し、入力メニューはありません。Ctrl+F5または既に開いたターミナルから実行すると結果を確認できます。

**デモはFAILがあっても終了コード0です。合否判定にはCTestを使用してください。** テストプログラムは合格時0、不合格時1を返します。04・05のテストを直接実行する際の引数は各課題のREADMEを参照してください。

## 修正後の確認

`exercise.cpp` が主な修正対象です。04・05では `exercise.hpp` も変更できます。`cases.hpp` と `tests.cpp` は公開テスト、`main.cpp` は表示処理、`common/` は共通処理です。

保存・再ビルド後、修正した課題を個別に確認します。

```sh
ctest --preset workshop -R '^hp_spec$'
ctest --preset workshop -R '^chase_spec$'
ctest --preset workshop -R '^collision_spec$'
ctest --preset advanced -R '^boss_'
ctest --preset advanced -R '^move_'
```

未修正の課題が失敗するのは正常です。`No tests were found` は動作確認の成功ではありません。必ず対象のテストが実行されたことを確認します。

課題単独のビルド例（教材フォルダーから）：

```sh
cmake -S 01-hp -B build-hp -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-hp --parallel 2
ctest --test-dir build-hp --output-on-failure
```

他の課題のコマンドは各READMEを参照してください。共通処理を参照するため、教材フォルダー全体を利用します。

## トラブルシューティング

| 症状 | 確認事項 |
|---|---|
| コンパイラ・CMake・Ninjaが見つからない | VSの必要コンポーネントを確認し、Developer PowerShellを開き直す |
| プリセットがない | 開いたフォルダーが `debugging-workshop` か確認する |
| 実行ファイルがない | 構成だけでなくビルドが成功したか確認する |
| 修正が反映されない | 保存、実行停止、再ビルド、実行ターゲットを確認する |
| 日本語が文字化けする | UTF-8で保存し、Windows Terminal等を使う。ターミナルでは `chcp 65001` も試す |
| ビルド設定が衝突する | 記録を退避してから該当する生成物の `build` または `build-advanced` だけを削除し再構成する |
| テストが失敗する | 期待と実際の差を確認する。コンパイルエラーとは区別する |

Linuxでのビルド・実行を確認済みです。Windows / Visual Studio実機での動作は未検証です。

## ファイル構成

```text
debugging-workshop/
├── README.md
├── CMakeLists.txt / CMakePresets.json
├── common/
├── 01-hp/
├── 02-chase/
├── 03-collision/
├── 04-boss/
├── 05-move/
└── docs/advanced-primer.md
```
