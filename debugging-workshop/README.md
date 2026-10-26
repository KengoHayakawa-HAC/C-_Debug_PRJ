# AI vs 人間 デバッグ対決

2時間で、ゲームの小さな不具合を「観察 → 仮説 → 調査 → 修正 → テスト」する教材です。C++初心者から経験者まで、学年を混ぜた2～4人のチームで取り組みます。速さだけでなく、説明と検証を評価します。

**初期状態はコンパイルに成功し、テストには失敗します。意図された教材の状態です。** このディレクトリだけで独立してビルドします。通常のリポジトリCIへの組み込みは行っていません。

## 最初に開く資料

| 課題 | 難易度・目安 | Visual Studioで選ぶ実行ターゲット | 内容 |
|---|---|---|---|
| [1: HP計算](01-hp/README.md) | 初級・15～20分 | `hp_demo.exe` | ダメージ、回復、HPの範囲 |
| [2: 敵の追尾](02-chase/README.md) | 中級・25～35分 | `chase_demo.exe` | 座標と、繰り返したときの動き |
| [3: 円の当たり判定](03-collision/README.md) | 上級・25～35分 | `collision_demo.exe` | 通常条件と境界条件の比較 |

04・05は**任意の発展課題**です。通常の120分の進行には追加しません。01～03を使う `workshop` 構成の内容も変わりません。

| 発展課題 | 難易度・目安 | 実行ターゲット |
|---|---|---|
| [04: ボスキャラクターの能力が消える](04-boss/README.md) | 上級・40～60分 | `boss_demo.exe` |
| [05: std::moveしたのにコピーが発生する](05-move/README.md) | 上級・30～45分 | `move_demo.exe` |

[短い前提知識](docs/advanced-primer.md)から取り組めます。[追加課題の検証記録](docs/advanced-validation.md)も用意しています。04は攻撃の保持と初期化を別々に、05はコピー・ムーブ回数とデータ内容を別々にテストします。

Visual Studioで追加課題を使う場合は構成 `advanced` を選択してビルドし、上の実行ターゲットをCtrl+F5で実行します。コマンドは教材フォルダーから次のとおりです。

```sh
cmake --preset advanced
cmake --build --preset advanced --parallel 2
ctest --preset advanced
ctest --preset advanced -R '^boss_'
ctest --preset advanced -R '^move_'
```

`advanced` のCTestプリセットは04・05だけを選択します。全5課題をまとめて確認する場合は `ctest --test-dir build-advanced --output-on-failure` を使用します。初期状態の失敗は意図されたものです。各課題単独のビルド・テスト手順は個別READMEを参照してください。

追加課題のデモは固定ケースを表示して終了します。以下にある入力メニューの説明は01～03向けです。04・05ではクラスやAPIの設計を扱うため、`exercise.hpp` も修正できます。公開テストと05の計測処理は維持してください。

[比較記録テンプレート](docs/record-template.md)をチームごとにコピーします。運営者は[進行資料](docs/facilitator.md)も確認してください。

## Windows / Visual Studio 2022（標準環境）

準備は活動前に済ませてください。Visual Studio Codeとは別の製品です。

1. Visual Studio Installerで、Visual Studio 2022の**「C++によるデスクトップ開発」**をインストールします。「Windows SDK」「MSVC v143」「Windows用C++ CMakeツール」を含めます。
2. リポジトリをクローン、またはGitHubの「Code → Download ZIP」でダウンロードして展開します。書き込み可能なローカルフォルダーを使います。
3. Visual Studioで「ファイル → 開く → フォルダー」を選び、**`debugging-workshop` フォルダーそのもの**を開きます。`.sln` の作成は不要です。
4. CMakeの構成が完了するまで待ちます。構成の選択欄で `workshop` を選択します。プリセットが認識されない場合は「ツール → オプション → CMake」でCMakePresets.jsonの利用を有効にし、フォルダーを開き直します（表示名はVSの版により異なります）。
5. 「ビルド → すべてビルド」を実行します。
6. 上部のスタートアップ項目から `hp_demo.exe` を選び、**Ctrl+F5（デバッグなしで開始）**で実行します。他の課題も同じ手順です。
7. 終了はメニューで `0` とEnter。修正時はプログラムを終了して保存し、再ビルドしてから再実行します。

F5でデバッグする場合は、実行したい `*_demo.exe` または `*_tests.exe` を選びます。行の左端にブレークポイントを置き、F10で1行ずつ進み、「ローカル」や「ウォッチ」で値を確認できます。デバッガを使わず、`std::cout` で途中の値を表示しても構いません。

### Windowsでのコマンド操作・自動テスト

スタートメニューから **「Developer PowerShell for VS 2022」** を開きます。VSの通常のターミナルでコンパイラが見つからない場合もこちらを利用します。以下はすべて `debugging-workshop` をカレントフォルダーとして実行します。

```powershell
cd C:\実際の保存先\C-_Debug_PRJ\debugging-workshop
cmake --preset workshop
cmake --build --preset workshop --parallel 2
.\build\01-hp\hp_demo.exe
ctest --preset workshop
```

個別のテストは以下です。

```powershell
ctest --preset workshop -R '^hp_spec$'
ctest --preset workshop -R '^chase_spec$'
ctest --preset workshop -R '^collision_spec$'
```

テスト結果を短く直接見るには、例えば `.\build\01-hp\hp_tests.exe` を実行します。`*_demo` は観察用で、表示にFAILがあっても正常終了します。**合否判定には `*_tests` またはCTestを使います。** テストプログラムは失敗時に終了コード1、成功時に0を返します。CTestも失敗時は非ゼロです。

## Linux（補助環境）

C++17対応コンパイラ（例: GCC 9以降）、CMake 3.20以降、Ninjaが必要です。Ubuntu/Debianの一般的な環境なら `sudo apt install g++ cmake ninja-build` で導入できます。管理権限のない環境では管理者に準備を依頼してください。

```sh
cd /実際の保存先/C-_Debug_PRJ/debugging-workshop
cmake --preset workshop
cmake --build --preset workshop --parallel 2
./build/01-hp/hp_demo
ctest --preset workshop
ctest --preset workshop -R '^hp_spec$'
```

本教材はC++17に固定しています。外部C++ライブラリ、Python、AIのAPIキー、ネット接続はビルド・実行に不要です。Web検索・AI利用の際のみネット接続が必要です。

## 実行結果の見方

起動すると用意されたケースを順に表示します。コンソールを上へスクロールして、入力値・期待値・実際の値を読みます。

```text
入力: HP=80 最大HP=100 回復=30
ケース: 最大HPを超える回復
期待: 100
実際: 110
結果: FAIL (仕様との差があります)
```

`PASS` はそのケースの結果が仕様と一致、`FAIL` は不一致です。FAILは原因の場所を示すものではありません。複数の失敗が1つの原因で起きることもあります。衝突判定では `1` が当たっている、`0` が当たっていない、です。

その後のメニューで `1` は再表示、`2` は任意入力、`0` は終了です。入力は**半角整数・半角スペース**を使います。個数違い、文字、範囲外の数は再入力になります。任意入力の期待値は、実行前に仕様から手で計算して記録してください。プログラムが示す値をそのまま正解にしないようにしましょう。

## 調査と修正の進め方

1. 仕様と入力を読み、期待値を説明する。
2. 成功する例と失敗する例の違いを探す。
3. 仮説を1つ書き、途中の変数を表示するかデバッガで調べる。
4. 各課題の `exercise.cpp` を修正する。公開テストを通すために `cases.hpp` やテストを変更しない。
5. 再ビルドし、その課題のCTestを実行する。成功したら別の入力でも調べる。

`exercise.hpp` は関数とデータの形、`main.cpp` は表示・入力、`cases.hpp` は仕様を確認する入力と期待値、`tests.cpp` は自動テストの入口です。`common/` は入力・表示・ビルドの共通処理で、課題の修正対象ではありません。既存関数の呼び出し方を保てば、仕様に合う修正方法は複数認めます。

人間だけで調べる段階Aでは、Web検索・C++リファレンス・デバッガは利用可、生成AIによる解答・AI補完・検索画面のAI要約は利用しません。段階BでAIを解禁します。詳細は[進行資料](docs/facilitator.md)を参照してください。

## 課題ごとに独立してビルドする

全体ビルドができれば通常は不要ですが、各課題単独でも構成できます。以下は `debugging-workshop` から実行します。WindowsではDeveloper PowerShellを使います。

```sh
cmake -S 01-hp -B build-hp -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-hp --parallel 2
ctest --test-dir build-hp --output-on-failure
```

実行ファイルは Windowsでは `build-hp\hp_demo.exe`、Linuxでは `build-hp/hp_demo` です。課題2は `01-hp` / `build-hp` / `hp` を `02-chase` / `build-chase` / `chase` に、課題3は `03-collision` / `build-collision` / `collision` に置き換えます。`common/` を使用するため、配布時は教材フォルダー全体を渡してください。

CMakeを使わない場合の例（Linux / g++、教材フォルダーから）:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic 01-hp/exercise.cpp 01-hp/main.cpp -o /tmp/hp_demo
/tmp/hp_demo
```

WindowsではVisual Studio付属のMSVCでの実施を標準とし、MinGWとの混在を避けます。

## 修正前後・AI利用前後の記録

再ビルド後、次のようにテストのログを保存できます。`build/` 内はGit管理対象外です。別名を使えば上書きを防げます。

```sh
ctest --preset workshop --output-log build/before.txt
# 調査と修正後にビルドしてから:
cmake --build --preset workshop --parallel 2
ctest --preset workshop --output-log build/after.txt
```

VSで2ファイルを開いて比較できます。Git利用者は `git diff -- debugging-workshop` でも変更を確認できます。AI解禁前にはコードもチーム専用の別フォルダーへコピーし、記録シートと一緒に保管します。**解答コードを共有リポジトリにpushしないでください。** ZIP利用者もコピーで記録できます。

## トラブルシューティング

| 症状 | 確認すること |
|---|---|
| `cmake` / `ninja` / C++コンパイラが見つからない | VS Installerで必要項目を追加し、Developer PowerShellを開き直す。Linuxはツールを導入する |
| プリセットが表示されない | 開いたフォルダーが `debugging-workshop` か、VSが更新済みか、プリセット利用設定を確認。上記コマンド操作でも実行可能 |
| `.exe` が見つからない | 構成だけでなくビルドも完了したか確認。記載のパスはNinjaの `workshop` プリセット用 |
| ジェネレーターやコンパイラが違うというエラー | この教材の生成物 `build/` だけを削除し、同じ開発用シェルから再構成。ソースや記録は先に保護する |
| 日本語が文字化けする | UTF-8で保存。MSVCの `/utf-8` はCMakeで設定済み。Windows Terminal等を使用。ターミナルやCTest表示には `chcp 65001` も試す |
| 実行後すぐ画面が閉じる | VSでCtrl+F5、または既に開いたターミナルから実行。メニューの0で終了 |
| 更新したはずの結果が変わらない | ファイル保存、実行停止、再ビルド、選択中のターゲットと出力先を確認 |
| テストが赤い | 配布直後は正常。入力・期待・実際を読む。コンパイルエラーとは別 |
| CTestが「No tests were found」 | 正しいフォルダーで構成し、`ctest --preset workshop` または正しい `--test-dir` を使用。0件は成功扱いにしない |
| 入力が受け付けられない | 半角数字、項目数、範囲を確認。小数は今回の仕様外 |
| AIが標準を変える／外部ライブラリを勧める | C++17・外部依存なし・公開テスト維持の制約を伝える |

参加者向けブランチには完全な解答は含めていません。この `Techer` ブランチには[運営者用の解答資料](teacher/README.md)を追加しています。公開ヒントは運営者の案内で1段階ずつ読みます。Linuxでの検証結果は[検証記録](docs/validation.md)を参照してください。Windows実機の最終確認は開催前に運営者が行ってください。

## ファイル構成

```text
debugging-workshop/
├── README.md
├── CMakeLists.txt / CMakePresets.json
├── common/              入力・表示・ビルドの共通処理
├── 01-hp/               HP課題
├── 02-chase/            追尾課題
├── 03-collision/        当たり判定課題
├── 04-boss/             ボスの能力（任意）
├── 05-move/             リソース転送（任意）
├── hints/               各課題の3段階ヒント
└── docs/                記録テンプレート・進行資料・検証記録
```

各課題フォルダーには `README.md`、`CMakeLists.txt`、`exercise.hpp`、`exercise.cpp`、`main.cpp`、`cases.hpp`、`tests.cpp` があります。
