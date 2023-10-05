CC=gcc
CFLAGS= -c -std=c11 -Wall -Werror -Wextra

s21_cat: s21_cat.o
		$(CC) s21_cat.o -o s21_cat

test_cat: s21_cat.o
		$(CC) s21_cat.o -o ../cat/s21_cat
		../cat/test_func_cat.sh
test_cat_leak: s21_cat.o
		$(CC) s21_cat.o -o ../cat/s21_cat
		../cat/test_leak_cat.sh

s21_cat.o: s21_cat.c
		$(CC) $(CFLAGS) s21_cat.c
clang:
	cp ../../materials/linters/.clang-format ./
	clang-format -n *.c

clean:
		rm -rf *.o
		rm -rf s21_catc