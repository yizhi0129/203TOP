#/!bin/bash 

clang -v -o stencil stencil.c -fopenmp

for i in {1..5} 
do
    ./stencil 0 >> stencil_base.txt
    ./stencil 1 32 >> stencil_opt_32.txt
    ./stencil 1 64 >> stencil_opt_64.txt
    ./stencil 1 128 >> stencil_opt_128.txt
    ./stencil 1 512 >> stencil_opt_512.txt
    ./stencil 1 1024 >> stencil_opt_1024.txt
    ./stencil 1 2048 >> stencil_opt_2048.txt
    ./stencil 1 4096 >> stencil_opt_4096.txt
done