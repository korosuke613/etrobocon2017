# hoge.sh
# y = sin(x) を描画
g++-7 -w ../src/Pid.cpp ../src/SpeedControl.cpp ../src/TurnControl.cpp ../src/LineTracerWalker.cpp ../src/SelfLocalization.cpp example_SelfLocalization.cpp -I../include
./a.out
gnuplot -persist << EOF
set size ratio -1
p 'traveling_route.txt', x, x * 0.5 + 250, x * 0.75
EOF