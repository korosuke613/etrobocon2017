gnuplot -persist << EOF

set size ratio -1
p "hirakoba.png" binary filetype=png dx=0.27 dy=0.27 origin=(-320,-70) with rgbimage, 'traveling_route.txt'
EOF