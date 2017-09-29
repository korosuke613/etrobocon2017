# etrobocon2017

master [![Build Status](https://travis-ci.org/korosuke613/etrobocon2017.svg?branch=master)](https://travis-ci.org/korosuke613/etrobocon2017) [![codecov](https://codecov.io/gh/korosuke613/etrobocon2017/branch/master/graph/badge.svg)](https://codecov.io/gh/korosuke613/etrobocon2017)

dev [![Build Status](https://travis-ci.org/korosuke613/etrobocon2017.svg?branch=dev)](https://travis-ci.org/korosuke613/etrobocon2017) [![codecov](https://codecov.io/gh/korosuke613/etrobocon2017/branch/dev/graph/badge.svg)](https://codecov.io/gh/korosuke613/etrobocon2017)

ようこそ

このページは[片山研究所モデルベース開発推進事業部](http://earth.cs.miyazaki-u.ac.jp "http://earth.cs.miyazaki-u.ac.jp")が開発している、ETロボコン2017デベロッパー部門アドバンスドコースのソースコードのリポジトリです。

## 開発者

* 平木場 （チームリーダの寮長）
* 佐竹 （自称Sirius）
* 山脇 （はんだ付けの王）
* 宮地 （粋がったC++プロ）
* 佐藤 （ネタ勢デュエリスト）
* 立山 （イギリス帰りのカタンの女王）
* 森 （プロマネ兼使いっ走り）

## ソースコードのドキュメント
**[こちら](https://korosuke613.github.io/etrobocon2017/annotated.html "https://korosuke613.github.io/etrobocon2017/annotated.html")** にのっています。

参考 [Doxygenの特殊コマンド](http://www.doxygen.jp/commands.html "https://korosuke613.github.io/etrobocon2017/annotated.html")

## 大事な変数の型とか
|何をするか|型|範囲|参照|備考|
|:--|:--|:--|:--|:--|
|モーターのPWM(パワー)|int|100 ~ -100|Motor.h||
|モーターの角位置(DEG)|int32\_t|-2,147,483,648 ~ 2,147,483,647|Motor.h||
