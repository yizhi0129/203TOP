set terminal png

set output 'ws1.png'
set title 'Weak Scalability 9600 Bytes'

set xlabel 'number of processes'
set ylabel 'average execution time'

set logscale x 2
f(x) = 3.86e-05 / x

plot '17.dat' with points title 'real execution time', \
     f(x) with lines title 'reference'


set output 'ss1.png'
set title 'Strong Scalability Multiples 9600 Bytes'

set xlabel 'number of processes'
set ylabel 'average execution time'

set logscale x 2

f(x) = 2.975e-05 * x

plot '17b.dat' with points title 'real execution time', \
     f(x) with lines title 'reference'


set output 'ws2.png'
set title 'Weak Scalability 9600 Bytes'

set xlabel 'number of processes'
set ylabel 'average execution time'

set logscale x 2

f(x) = 0.0001183 / x

plot '18.dat' with points title 'real execution time', \
     f(x) with lines title 'reference'


set output 'ss2.png'
set title 'Strong Scalability Multiples 9600 Bytes'

set xlabel 'number of processes'
set ylabel 'average execution time'

set logscale x 2

f(x) = 8.17e-05

plot '18b.dat' with points title 'real execution time', \
     f(x) with lines title 'reference'