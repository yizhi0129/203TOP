#!/bin/bash

/usr/local/mpich-3.4.1/bin/mpicc pingpong.c -o pingpong
i=65300
while [ $i -le 65400 ]
do
/usr/local/mpich-3.4.1/bin/mpirun -n 2 ./pingpong $i >> 8.dat
i=$(( $i + 10 ))
done