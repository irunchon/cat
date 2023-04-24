#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct s21CatFlags {
  int bFlag, eFlag, nFlag, sFlag, tFlag, vFlag, helpFlag;
};

void s21CatNoArguments();
void s21CatWithArguments(int argc, char *argv[]);
void s21CatFlagsProcessing(int optind, int argc, char *argv[],
                           struct s21CatFlags *flagsValues);
void s21CatFlagsParsing(int argc, char *argv[],
                        struct s21CatFlags *flagsValues);
void s21HelpInfo();

#endif  // SRC_CAT_S21_CAT_H_