# Google Testの使い方
ここではCygwinでのGoogle Testの使い方について説明します。
わかってしまえばそんなに難しくないですが、ちょっと手間取りますから気を付けてください。

## 長い前置き
その前に簡単にGoogle Testとは何ぞやという説明だけさらっとしておきます。
簡単に言えばC++のJUnitバージョンです。
最初はCppUnitっていうのがC++でのデファクトスタンダートだったらしいですが、余りにも機能がシンプルすぎて使いづらいという話がちらほら出ていたそうです。
そこで、Googleが「俺の考えた最強のC++単体テストツール」を作ったみたいです。
そしてこれがなかなか便利なものでして、次の2点が有用な点として挙げられます。
* 使いやすく、ドキュメントも豊富 -> 他の単体テストツールでは使いづらかったり、ドキュメントが乏しかったりするらしい
* Mockが使える -> ちょっと調べた感じでは、C++でモックオブジェクトを作るのは難しいらしく、ほとんどないが、Google Testではデフォルトでモックを作ってくれるツールもセット、お得だね！
ってな感じなので、使ってみましたよってことです。

ただ、インターネット情報では2年前くらいのバージョン1.xシリーズの説明しかなく、現在のバージョン2.x系列のコンパイルや使い方の日本語での説明がほぼほぼなかったため、頑張って使い方を調べました。
これであなたもGoogle Testプロになれます、かねぇ？


## コンパイルしよう
自分は最近までJavaやPerlばっかりの生活だったせいで、コンパイルをするという動作を完全に忘れてしまってました。
そのせいで悪戦苦闘したので、まずはコンパイルをどうするかを丁寧に説明しようと思います。
くどいかもしれませんが、ご了承ください。


1. GitHubに上がっているGoogle Testを取ってくる。

大事ですね、でもここから説明しておきます。
その前に、カレントディレクトリを移動しておきましょう。
これからgit cloneするわけですが、カレントディレクトリ直下に配置するので（もちろん、gitのコマンドでカレントディレクトリ以外に置くこともできますが）、どこに置いておきたいかを考えてください。
ちなみに、テスト用ツールをコンパイルする際に、このディレクトリを参照するので、あまり遠くに置かないほうがいいと思います。

```
$ git clone https://github.com/google/googletest.git
```

これで、カレントディレクトリ直下に配置されます。
疑っているのなら、lsでもしてみましょう。

```
$ ls
googletest そのほかのファイルやディレクトリ
```

もしかしたらgoogleさんがgoogletestリポジトリから移動させちゃったりしているかもしれませんが、その時は探してください、きっと見つかりますよ。

さて、苦労して入手できたら、いよいよコンパイルです。
コンパイルしなければならないのは2つです。
* gtest\_main.cc
* gtest-all.cc
2つとも同じ場所にありますから、まずはその場所まで移動しましょう。

```
$ cd googletest/googletest/src
$ ls
gtest.cc       gtest-all.cc         gtest-filepath.cc     gtest-port.cc      gtest-test-part.cc
gtest_main.cc  gtest-death-test.cc  gtest-internal-inl.h  gtest-printers.cc  gtest-typed-test.cc
```

どうですか？
ちゃんとgtest\_main.ccとgtest-all.ccが見つかったでしょうか？

さて、それではコンパイルです。
Makefileとかcmakeとかは知りません、ごり押しです。
まずはgtest\_main.ccからです。

```
$ g++ -I. -I../include -c gtest_main.cc
```

やけにすんなり通ってくれましたね。
lsをすればgtest\_main.oがカレントディレクトリに入っていると思います。

次はgtest-all.ccです。

```
$ g++ -I. -I.. -I../include -c gtest-all.cc
```

オプションとして-I..が追加されていることに注意してください。
これで、gtest-all.oもできているはずです。

さて、実はgtest-all.ccのコンパイルを最初はしていませんでした！
なぜかというと、僕はこの-I..を付けていないがために、エラーをボカボカ出しました。
それでの解決策として、ソースコードを直接いじるという愚行を犯してしまいました。
とはいえそんなに難しくはありません。

\#include "src/hogehoge.cc"がエラーだよ

との説明を受けたので、じゃあsrc/を消せばいいじゃんと考えました、はい。
そんなことを4ファイルくらいしてコンパイルを通しました。
皆さんはやらないほうがいいと思います。


__注意__

g++でコンパイルに失敗する人が多数いるそうです！
自分がどうしてうまくいったのか調べたところ、Straberry Perl（WindowsでPerlを使えるようにするツール群）をインストールした際に、一緒に入っていたg++プログラムを呼び出してコンパイルしていました。
ただし、これが正しいとはとても思えないので、もっといい方法が見つかったら教えてください。

32bit版Cygwinにおいて、コンパイルに失敗する原因は、stddef.hを見つけられないというエラーでした。
そこでfindコマンドで検索してみたところ、次のディレクトリが見つかりました。

```
$ find / -name stddef.h
/home/katlabPC/ev3rt-beta7-release/hrp2/hrp2/target/ev3_gcc/drivers/common/virtual-linux-kernel/include/linux/stddef.h
/home/katlabPC/ev3rt-beta7-release/hrp2/target/ev3_gcc/drivers/common/virtual-linux-kernel/include/linux/stddef.h
/lib/gcc/i686-pc-cygwin/6.3.0/include/stddef.h
/usr/lib/gcc/i686-pc-cygwin/6.3.0/include/stddef.h
```

よって、次のコマンドで無事コンパイルが確認できました。

```
$ g++ -I. -I../include -I/lib/gcc/i686-pc-cygwin/6.3.0/include -c gtest_main.cc
$ g++ -I. -I.. -I../include -I/lib/gcc/i686-pc-cygwin/6.3.0/include -c gtest-all.cc
```

また、コンパイルの失敗は確認できませんでしたが、テストファイル./a.exe実行時に何も表示されないというバグが発生しているようです。
g++とgccのバージョンを同じものにすると動くという情報があります。
例えば、次のような時にはうまく動作してくれました。

```
$ gcc --version
6.3.0

$ g++ --version
6.3.0
```



2. できたgtest\_main.oとgtest-all.oファイルをテストコードがあるディレクトリにコピー

これはそんなに難しくないよね。

```
$ cp \*.o 置きたいディレクトリ
```

とすれば移動します。
ETロボコンでは、次のディレクトリに置きました。

~/ev3rt-beta7-release/hrp2/sdk/etrobocon2017/str/test

結局この辺りが無難ですよね。
ちなみに、etrobocon2017ディレクトリ内は次の通りです。

```
etrobocon2017
|-- Makefile
|-- str
    |-- app.cpp
    |-- app.cfg
    |-- app.h
    |-- Makefile.inc
    |-- 細かいファイルは省略
    |-- app
    |   |-- SonarAlert.cpp
    |   |-- SonarAlert.h
    |   |-- 省略
    |-- googletest
    |   |-- googletest
    |       |-- include
    |       |-- src
    |       |-- 省略
    |-- test
        |-- gtest_main.o
        |-- gtest-all.o
        |-- テストコード置き場
```

3. テストコードを書いてコンパイルしよう

テストコードの書き方は具体例のほうがわかりやすいと思うので、ここのファイルをどれか適当に選んでください。

最低限書かなければならないのは次の文です。

```
/**
 * AddTest.cpp
 * ヘッダファイルは書かなくてもいいらしい
 */

// googletest/googletest/include内のディレクトリおよびファイルをインクルードする。
#include <gtest/gtest.h>

// なんかのテストコード
int add( int x, int y )
{
    return x + y;
}

// テストケース名とテスト内容を記述する。
// テストケース名はこのテストクラス名、テスト内容は具体的なテストメソッド名を入れるといいかも。
TEST( AddTest, get3add1and2 )
{
    // みんな大好きassertEqual文
    // assertThat文に相当するものはないっぽいけど、ASSERT_EQ文でエラーが発生した時には、引数をコンソール上に表示してくれる完全上位互換
    ASSERT_EQ( add( 1, 2 ), 3 );
}
```

これをまずはコンパイルできるようにしましょう。
最低限使えるようなテストはこの後で行います。

まずはテストコードのコンパイルです。

```
$ pwd
~/ev3rt-beta7-release/hrp2/sdk/etrobocon2017/str/test
```

```
$ ls
AddTest.cpp gtest_main.o gtest-all.o

$ g++ AddTest.cpp gtest_main.o gtest-all.o -I../googletest/googletest/include
```

これでコンパイルが成功すると、a.exeがカレントディレクトリに出現します。
こいつを実行すれば、いい感じに色も付いたきれいなテスト結果が表示されます。
おめでとうございます！
これであなたもGoogle Testプロです。


4. せめて普通のクラスを単体テストしましょう

これで終われるはずはないわけです。
普通に考えれば、テストコードにテストしたい内容を埋め込むなんてことはあり得ません。
では、別のメソッドを呼び出しましょう。

その時のテストファイルはこちらです。

```
/**
 * SonarAlertTest.cpp
 */
#include <gtest/gtest.h>
#include <app/SonarAlert.h> // このヘッダファイルのcppファイルをテスト


// アラートする距離をコンストラクタで30にセットすると30を返す
TEST( detectBarrierTest, return30WhenSetAlertDistance30 )
{
    // コンストラクタの引数に30を入れると、30という数値を初期値とする定数に代入
    SonarAlert sonarAlert( 30 );
    // 最初に入れた定数を返してほしい
    ASSERT_EQ( sonarAlert.getDistanceBorder(), 30 );
}
```

```
/**
 * SonarAlert.cpp
 */
#include "SonarAlert.h"

SonarAlert::SonarAlert( int distanceBorder ):
    SONAR_ALERT_DISTANCE( distanceBorder ) {}
/*
 * SonarAlert::SonarAlert( int distanceBorder )
 * {
 *     SONAR_ALERT_DISTANCE = distanceBorder;
 * }
 * これではエラー！定数に代入はできないよ
 */

int SonarAlert::getDistanceBorder()
{
    return SONAR_ALERT_DISTANCE;
}
```

```
/**
 * SonarAlert.h
 */
#ifndef __SONARALERT__
#define __SONARALERT__

class SonarAlert {
public:
    SonarAlert( int );
    int getDistanceBorder();

private:
    const signed int SONAR_ALERT_DISTANCE;
};

#endif
```

一気にそれっぽいものができましたね、ではコンパイルです。

```
$ g++ ../app/SonarAlert.h ../app/SonarAlert.cpp SonarAlertTest.cpp gtest_main.o gtest-all.o -I.. -I../googletest/googletest/include
```

成功しましたか？
成功した -> おめでとうございます！
成功しなかった -> いくつか落とし穴があります、気を付けてみてください。
* SonarAlert.cppとSonarAlert.hはstr/appに入ってますか？
* コンパイル引数の順番は合ってますか？
* -I引数を間違えてませんか？

これで一通りのことはできると思います。
今度こそGoogle Testプロです！


## makeファイルくらい作ろう

まだできてません、頑張りますからもう少しお待ちください。

