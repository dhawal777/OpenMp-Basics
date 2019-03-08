set title "CPU Core data"
set xlabel "threads"
set ylabel "time"
set grid
plot "observation.dat" u (column(0)):2:xtic(1) w l title ""
