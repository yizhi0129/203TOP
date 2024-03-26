/usr/local/bin/gcc-13 -g -Wall -Wextra -Werror -fdump-tree-all main.c
rm -f a*

/usr/local/bin/gcc-13 -g -Wall -Wextra -Werror -o main main.c 
./main

gdb -q main