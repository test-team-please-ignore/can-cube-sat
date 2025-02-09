set datafile separator comma

set xlabel "Время от старта (минуты)" font ",16"
set xtics 10 nomirror font ",16"
set mxtics

set ylabel "Давление по BME280 (Па)" font ",16"
set ytics 10000 nomirror font ",16"
set yrange [25000:110000]
set mytics

set xzeroaxis
set yzeroaxis

set border 1+2
set grid xtics ytics


set key off


set terminal png size 1920,1080
set output 'PLD_BME280_DATA-13-0-pressure.png'

plot 'PLD_BME280_DATA-13-0.csv' using 'time_from_start_min':'pressure' axis x1y1 
pause mouse close
