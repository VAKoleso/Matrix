CFLAGS = -Wall -Werror -Wextra
CC_DEFAULT = gcc
CC=$(CC_DEFAULT) $(CFLAGS) 
OS := $(shell uname -s)

all: clean s21_matrix.a test

s21_matrix.o : 
	$(CC) -c s21_matrix.c -o s21_matrix.o

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o

clean: 
	rm -rf *.o *.gc* report *.a test test.info a.out

test.o:
	$(CC) -c test.c -o test.o

test: s21_matrix.a test.o
ifeq ($(OS), Darwin)
	$(CC) test.o s21_matrix.a -o test -lcheck
	./test
else
	$(CC) test.o s21_matrix.a -o test -lcheck -lsubunit -lrt -lpthread -lm
	./test
endif

gcov:
ifeq ($(OS), Darwin)
	$(CC) --coverage s21_matrix.c test.c -o test -lcheck
else
	$(CC) --coverage s21_matrix.c test.c -o test -lcheck -lsubunit -lrt -lpthread -lm
endif

gcov_report: clean gcov
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

cpplint:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	rm -rf CPPLINT.cfg

cppcheck: 
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

leaks:
	CK_FORK=no leaks --atExit -- ./test

check: cpplint cppcheck leaks
