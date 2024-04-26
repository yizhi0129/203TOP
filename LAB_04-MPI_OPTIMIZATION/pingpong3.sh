#!/bin/bash

/usr/local/mpich-3.4.1/bin/mpicc pingpong3.c -o pingpong3

i=32
while [ $i -le 9600 ]
do

j=1
while [ $j -le 5 ]
do
/usr/local/mpich-3.4.1/bin/mpirun -n 2 ./pingpong3 $i >> 13.dat
j=$(( $j + 1 ))
done

i=$(( $i + 32 ))
done