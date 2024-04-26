#!/bin/bash

/usr/local/mpich-3.4.1/bin/mpicc scal.c -o scal
/usr/local/mpich-3.4.1/bin/mpicc scal2.c -o scal2
i=1
j=9600
while [ $i -le 128 ]
do
/usr/local/mpich-3.4.1/bin/mpirun -n $i ./scal $j >> 17b.dat
/usr/local/mpich-3.4.1/bin/mpirun -n $i ./scal 9600 >> 17.dat
/usr/local/mpich-3.4.1/bin/mpirun -n $i ./scal2 $j >> 18b.dat
/usr/local/mpich-3.4.1/bin/mpirun -n $i ./scal2 9600 >> 18.dat
i=$(( i*2 ))
j=$(( j*2 ))
done