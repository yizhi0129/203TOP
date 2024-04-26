#!/bin/bash

/usr/local/mpich-3.4.1/bin/mpicc pingpong4.c -o pingpong4
/usr/local/mpich-3.4.1/bin/mpirun -n 2 ./pingpong4 >> 14.dat