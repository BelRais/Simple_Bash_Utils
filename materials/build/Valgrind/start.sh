#!/bin/bash

# make s21_string.a
# gcc -g test_s21_string.c s21_string.a -o test -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
# valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
cd ./grep
#cd ./cat
# make s21_grep
gcc -std=c11 -D_GNU_SOURCE -Wall -Werror -Wextra s21_grep.c -o test
#gcc -Wall -Werror -Wextra s21_catLast.c -o test
# gcc -g  s21_grep.c  -o test -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
# valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test -e
#valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test while -e void s21_grep.c Makefile -ohn -f test_ptrn_grep.txt
# valgrind --log-file="valgrind_s21_grep.log" --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all
#bash test_valgrind_cat.sh
bash test_valgrind_grep.sh


# grep regex -e ^print s21_grep.c -o -f test_ptrn_grep.txt



#grep for -e ^int s21_grep.c -n -o

#grep for -e ^int s21_grep.c s21_grep.h Makefile -h -o

#grep for -e ^int s21_grep.c -o -n

#grep regex -e ^print s21_grep.c -o -n -f test_ptrn_grep.txt