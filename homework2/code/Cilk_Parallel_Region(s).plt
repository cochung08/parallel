# Uncomment 2 lines below to create a .png file instead of displaying using X
#set terminal png size 600, 600
#set output "Cilk_Parallel_Region(s).png"
# Set aspect ration, zoom factor
set size square 1.0, 1.0
# Set plot title
set title "Trial results for Cilk Parallel Region(s)"
# Set X, Y axis titles
set xlabel "Worker Count"
set ylabel "Speedup"
# Specify where key is to be displayed
set key left top box
# Make points a bit bigger than the defaultset pointsize 1.8
set xrange [0:16]
set yrange [0:16]
# Plot the data
plot x title 'Parallelism' lt 2, \
26902.239354 notitle lt 2, \
'-' title 'Burdened Parallelism' with lines lt 1
1 1.000000
2 1.900000
3 2.850000
4 3.800000
5 4.750000
6 5.700000
7 6.650000
8 7.600000
9 8.550000
10 9.500000
11 10.405179
12 11.290054
13 12.165461
14 13.031552
15 13.888475
16 14.736374
e
