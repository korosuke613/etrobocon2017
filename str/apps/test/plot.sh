# hoge.sh
# y = sin(x) を描画
g++-7 SelfLocalizationTest.cpp ../src/SelfLocalization.cpp gtest_main.o gtest-all.o -I../include -I../../googletest/googletest/include
./a.out
gnuplot -persist << EOF
set size ratio -1
p 'traveling_route.txt'
EOF