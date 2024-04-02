/usr/local/bin/gcc-13 -g -Wall -Wextra -Werror -fdump-tree-all main.c

sleep 3

rm -fR a* *.dSYM

sleep 1

/usr/local/bin/gcc-13 -g -Wall -Wextra -Werror -o main main.c 
./main

sleep 1
rm -f main

# gdb -q main