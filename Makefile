CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
SOURCES=s21_calculator.c 
OBJECTS=$(SOURCES:.c=.o)
OS = $(shell uname)
TEST_FILE_NAME = s21_tests_calc.c

ifeq ($(OS), Darwin)
 TEST_LIBS=-lcheck
else
 TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
endif

all: gcov_report install

install:  uninstall
	$(CC) $(CFLAGS) -c -o s21_calculator.o s21_calculator.c
	mkdir build
	cd build && cmake build ../Calculator
	make -C ./build
	open ./build/Calculator.app/Contents/MacOs/Calculator

uninstall:
	rm -rf build/
	rm -rf Calculator.tar
	rm -rf s21_calculator.o

dist:
	tar -cf ./Calculator.tar ./build/Calculator.app/Contents/MacOs/Calculator

s21_calculator.a: clean $(OBJECTS)
	ar -rcs s21_calculator.a $(OBJECTS)

tests: $(TEST_FILE_NAME) s21_calculator.a
	$(CC) $(CFLAGS) $(TEST_FILE_NAME) $(SOURCES) -o test $(TEST_LIBS) -L. --coverage
	./test

gcov_report: tests
	/Users/ghostgar/goinfre/homebrew/bin/lcov -t "test" -o test.info -c -d .
	/Users/ghostgar/goinfre/homebrew/bin/genhtml -o report test.info
	open report/index.html

dvi:
	open ReadMe.md

clean:
	make uninstall
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt test.info test.dSYM *.tar

# install lcov:
#  curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
#  brew install lcov
