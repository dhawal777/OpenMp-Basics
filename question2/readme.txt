Commands to run program and plot graph

gcc -o pi_mc pi_mc.c random_par.c random.h -fopenmp

time ./pi_mc

gnuplot

load "graph.plt"
