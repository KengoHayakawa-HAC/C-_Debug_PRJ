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

## Windows / Visual Studio 2022：ソリューションで開く

1. Visual Studio Installerで「C++によるデスクトップ開発」をインストールします。MSVC v143とWindows SDKを含めます。CTestも使う場合は「Windows用C++ CMakeツール」を含めます。Visual Studio Codeとは別の製品です。
2. `distribution` ブランチのZIPをダウンロードし、**フォルダー全体を展開**します。
3. **[DebuggingWorkshop.sln](DebuggingWorkshop.sln)** をダブルクリックするか、Visual Studioの「プロジェクトやソリューションを開く」で選びます。`.sln` だけを別の場所へ移動しないでください。
4. 上部の構成を **Debug**、プラットフォームを **x64** にします。このソリューションではプリセット `advanced` の選択は不要です。
5. 「ビルド → ソリューションのビルド」（Ctrl+Shift+B）を実行します。全5課題が対象です。
6. ソリューションエクスプローラーで課題フォルダーを展開し、例えば `hp_demo` を右クリック →「スタートアッププロジェクトに設定」。**Ctrl+F5** で実行します。
7. 修正後は保存し、実行を停止してから再ビルドします。デバッグ中の停止はShift+F5です。

`*_demo` が操作・観察用、`*_tests` が自動テスト用です。出力先は次の形式です。

```text
build-vs/x64/Debug/hp_demo/hp_demo.exe
build-vs/x64/Debug/hp_tests/hp_tests.exe
```

Release構成では `Debug` が `Release` に変わります。各プロジェクトのソースは既存課題のファイルを参照しているため、CMake方式と同じ `exercise.cpp` を修正します。

### ソリューションでビルドした結果をテストする

Developer PowerShell for VS 2022を開き、`debugging-workshop` フォルダーへ移動します。

```powershell
# Visual StudioのGUIでビルド済みなら、このmsbuildコマンドは不要
msbuild .\DebuggingWorkshop.sln /m /p:Configuration=Debug /p:Platform=x64

# 全7項目のテスト
ctest --test-dir visual-studio -C Debug --output-on-failure

# 課題を選ぶ例
ctest --test-dir visual-studio -C Debug --output-on-failure -R '^hp_spec$'
ctest --test-dir visual-studio -C Debug --output-on-failure -R '^boss_'
ctest --test-dir visual-studio -C Debug --output-on-failure -R '^move_'
```

Releaseでビルドした場合は `-C Release` を指定します。CTestは再ビルドしないため、修正後は保存・ビルドを先に行います。各課題のREADME冒頭に個別のコマンドがあります。

CTestを使わず、テストプログラムを直接実行することもできます。

```powershell
.\build-vs\x64\Debug\hp_tests\hp_tests.exe
.\build-vs\x64\Debug\boss_tests\boss_tests.exe storage
.\build-vs\x64\Debug\boss_tests\boss_tests.exe initialization
.\build-vs\x64\Debug\move_tests\move_tests.exe transfer
.\build-vs\x64\Debug\move_tests\move_tests.exe data
```

Visual Studioから `boss_tests` を直接起動した場合の既定引数は `storage`、`move_tests` は `transfer` です。別項目へ切り替えるにはプロジェクトの「プロパティ → 構成プロパティ → デバッグ → コマンド引数」を変更します。通常は上記のCTestが便利です。

## CMake方式でビルドする（Windows / Linux / VS Code）

`.sln` を使う方法とは別のビルド方法です。Visual Studioで使う場合は「ファイル → 開く → フォルダー」で `debugging-workshop` を開き、CMakeプリセットを選択します。VS Codeでも同じフォルダーを開き、以下のコマンドを使います。

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

## CMake方式での修正後の確認

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
| MSVC v143やWindows SDKが見つからない | VS InstallerでC++ワークロードと該当コンポーネントを追加する |
| プリセットがない（CMake方式） | 開いたフォルダーが `debugging-workshop` か確認する |
| 実行ファイルがない | 構成だけでなくビルドが成功したか確認する |
| 修正が反映されない | 保存、実行停止、再ビルド、実行ターゲットを確認する |
| 日本語が文字化けする | UTF-8で保存し、Windows Terminal等を使う。ターミナルでは `chcp 65001` も試す |
| ビルド設定が衝突する | 記録を退避してから該当する生成物の `build` または `build-advanced` だけを削除し再構成する |
| テストが失敗する | 期待と実際の差を確認する。コンパイルエラーとは区別する |

Linuxでのビルド・実行を確認済みです。ソリューションの参照先とテスト設定を検証していますが、Windows / Visual Studio実機でのMSBuild・実行は未検証です。

## ファイル構成

```text
debugging-workshop/
├── README.md
├── DebuggingWorkshop.sln
├── visual-studio/       Visual StudioプロジェクトとCTest設定
├── CMakeLists.txt / CMakePresets.json
├── common/
├── 01-hp/
├── 02-chase/
├── 03-collision/
├── 04-boss/
├── 05-move/
└── docs/advanced-primer.md
```
