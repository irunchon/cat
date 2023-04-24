#!/bin/bash

test_number=1

flags=(
    "-b"
    "-e"
    "-E"
    "-n"
    "-s"
    "-t"
    "-T"
    "-v"
    "--number-nonblank"
    "--number"
    "--squeeze-blank"
)

test_files=(
    "testfiles/testfiles_1.txt"
    "testfiles/testfiles_2.txt"
    "testfiles/testfiles_3.txt"
    "testfiles/testfiles_1.txt testfiles/testfiles_2.txt testfiles/testfiles_3.txt"
)

for flag in "${flags[@]}"
do
  for test_file in "${test_files[@]}"
  do
    echo "#$test_number: $flag $test_file"
    valgrind --show-leak-kinds=all ./s21_cat $flag $test_file > tmp_leaks.txt 2>&1
    tail -n4 ./tmp_leaks.txt
    echo " "
    rm tmp_leaks.txt
    test_number=$(( $test_number + 1 ))
  done
done
