# hoge.sh
# y = sin(x) を描画
g++-7 -g -w ../src/Pid.cpp ../src/SpeedControl.cpp ../src/TurnControl.cpp ../src/LineTracerWalker.cpp ../src/SelfLocalization.cpp ../src/Navigation.cpp example_Navigation.cpp -I../include
./a.out
gnuplot -persist << EOF
set xrange [] reverse
set yrange [] reverse 
set size ratio -1
p 'traveling_route.txt' with line
EOF
# "hirakoba.png" binary filetype=png dx=0.45 dy=0.45 origin=(-60,-760) with rgbimage,