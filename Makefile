TARGET1=build/s21_cat

CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11

SOURCES1 = src/s21_cat.c

.PHONY: tests

all: s21_cat

s21_cat: $(SOURCES1)
	$(CC) $(CFLAGS) $(SOURCES1) -o $(TARGET1)

clean:
	rm -rf src/*.o src/*.out src/s21_cat build/* tmp*

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SOURCES1)

formatcheck:
	clang-format -style=google -n src/*.c
	clang-format -style=google -n src/*.h

formatcorrect:
	clang-format -style=google -i src/*.c
	clang-format -style=google -i src/*.h

tests:
	chmod +x tests/tests_cat.sh
	./tests/tests_cat.sh

leakscheck:
	chmod +x tests/test_leaks_cat.sh
	./tests/test_leaks_cat.sh

rebuild: clean all
