set datafile separator ','
set key below
set key autotitle columnhead
set timefmt "%s"
set format x "%H:%M"     # or anything else
set xlabel "time (UTC)"
set xdata time

plot "tic.csv" us 1:2 wi li, '' us 1:3 wi li, '' us 1:4 wi li, '' us 1:5 wi li, '' us 1:6 wi li, '' us 1:7 wi li, '' us 1:8 wi li
