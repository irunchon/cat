#!/bin/bash

test_number=1
success=0
fail=0

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
    "testfiles/testfiles_1.txt testfiles/testfiles_2.txt"
    "testfiles/testfiles_1.txt testfiles/testfiles_3.txt"
    "testfiles/testfiles_2.txt testfiles/testfiles_3.txt"
    "testfiles/testfiles_1.txt testfiles/testfiles_2.txt testfiles/testfiles_3.txt"
)

for flag in "${flags[@]}"
do
  for test_file in "${test_files[@]}"
  do
    ./s21_cat $flag $test_file > tmp_1.txt
    cat $flag $test_file > tmp_2.txt
    cmp_result="$(diff -s tmp_1.txt tmp_2.txt)"
    if [ "$cmp_result" == "Files tmp_1.txt and tmp_2.txt are identical" ]
    then
      result="Success"
      success=$(( $success + 1 ))
    else
      result="Fail"
      fail=$(( $fail + 1 ))
    fi
    rm tmp_*.txt
    echo "#$test_number: $result: $flag $test_file"
    test_number=$(( $test_number + 1 ))
  done
done

for flag1 in "${flags[@]}"
do
  for flag2 in "${flags[@]}"
  do
    if [ $flag1 != $flag2 ]
    then
      for test_file in "${test_files[@]}"
      do
        ./s21_cat $flag1 $flag2 $test_file > tmp_1.txt
        cat $flag1 $flag2 $test_file > tmp_2.txt
        cmp_result="$(diff -s tmp_1.txt tmp_2.txt)"
        if [ "$cmp_result" == "Files tmp_1.txt and tmp_2.txt are identical" ]
        then
          result="Success"
          success=$(( $success + 1 ))
        else
          result="Fail"
          fail=$(( $fail + 1 ))
        fi
        rm tmp_*.txt
        echo "#$test_number: $result: $flag1 $flag2 $test_file"
        test_number=$(( $test_number + 1 ))
      done
    fi
  done
done

test_number=$(( $test_number - 1 ))
echo " "
echo "Total: $test_number"
echo "Successful: $success"
echo "Failed: $fail"
