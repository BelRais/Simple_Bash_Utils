CC=gcc

CFLAGS = -c -std=c11 -Wall -Werror -Wextra


s21_grep: s21_grep.o 
	$(CC) s21_grep.o -o s21_grep

s21_grep.o: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) s21_grep.c 

check_format:
	clang-format -i *.c *.h

clang:
	cp ../../materials/linters/.clang-format ./
	clang-format -n *.c *.h

clean:
	rm -rf *.o 
	rm -rf s21_grep