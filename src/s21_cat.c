#include "s21_cat.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    s21CatNoArguments();
  } else {
    s21CatWithArguments(argc, argv);
  }
  return EXIT_SUCCESS;
}

void s21CatNoArguments() {
  const int bufferSize = 4096;
  char buffer[bufferSize];

  while (fgets(buffer, bufferSize, stdin)) {
    printf("%s", buffer);
  }
}

void s21CatWithArguments(int argc, char *argv[]) {
  struct s21CatFlags flagsValues = {0, 0, 0, 0, 0, 0, 0};
  s21CatFlagsParsing(argc, argv, &flagsValues);
  s21CatFlagsProcessing(optind, argc, argv, &flagsValues);
}

void s21CatFlagsParsing(int argc, char *argv[],
                        struct s21CatFlags *flagsValues) {
  int currentOption = 0;

  const char *short_options = "beEnvstT";

  const struct option long_options[] = {
      {"number-nonblank", no_argument, &flagsValues->bFlag, 1},
      {"number", no_argument, &flagsValues->nFlag, 1},
      {"squeeze-blank", no_argument, &flagsValues->sFlag, 1},
      {"help", no_argument, &flagsValues->helpFlag, 1}};

  while ((currentOption = getopt_long(argc, argv, short_options, long_options,
                                      NULL)) != -1) {
    switch (currentOption) {
      case 'b':
        flagsValues->bFlag = 1;
        break;
      case 'e':
        flagsValues->eFlag = 1;
        flagsValues->vFlag = 1;
        break;
      case 'E':
        flagsValues->eFlag = 1;
        break;
      case 'n':
        flagsValues->nFlag = 1;
        break;
      case 's':
        flagsValues->sFlag = 1;
        break;
      case 't':
        flagsValues->tFlag = 1;
        flagsValues->vFlag = 1;
        break;
      case 'T':
        flagsValues->tFlag = 1;
        break;
      case 'v':
        flagsValues->vFlag = 1;
        break;
      case '?':
        if (!flagsValues->helpFlag) {
          printf("Try 's21_cat --help' for more information.\n");
          exit(EXIT_FAILURE);
        }
    }
  }
}

void s21CatFlagsProcessing(int optind, int argc, char *argv[],
                           struct s21CatFlags *flagsValues) {
  if (flagsValues->helpFlag) {
    s21HelpInfo();
    exit(EXIT_SUCCESS);
  }

  int lineNum = 1;  // it's for -n check on Ubuntu; comment for MACOS
  int currChar, prevChar = '\n';

  for (int curFileInArgList = optind; curFileInArgList < argc;
       curFileInArgList++) {
    FILE *currentFile = fopen(argv[curFileInArgList], "rb");

    if (currentFile == NULL) {
      // printf("%s: %s: No such file or directory\n", argv[0],
      // argv[curFileInArgList]);
      fprintf(stderr, "cat: %s: No such file or directory\n",
              argv[curFileInArgList]);
      continue;
    }

    // int lineNum = 1;  // uncomment for check -n & -b on MACOS
    int isEmptyLineAgain = 0;

    while ((currChar = getc(currentFile)) != EOF) {
      if (prevChar == '\n') {
        if (flagsValues->sFlag) {
          if (currChar == '\n') {
            if (isEmptyLineAgain) {
              continue;
            }
            isEmptyLineAgain = 1;
          } else {
            isEmptyLineAgain = 0;
          }
        }

        if ((flagsValues->nFlag && !flagsValues->bFlag) ||
            (flagsValues->bFlag && currChar != '\n')) {
          printf("%6d\t", lineNum++);
        }
      }

      prevChar = currChar;

      if (flagsValues->tFlag && currChar == '\t') {
        putchar('^');
        putchar('I');
        continue;
      }

      if (flagsValues->eFlag && currChar == '\n') {
        putchar('$');
      }

      if (flagsValues->vFlag && currChar != '\t' && currChar != '\n') {
        if (currChar < 32) {
          putchar('^');
          putchar(currChar + 64);
          continue;
        }
        if (currChar == 127) {
          putchar('^');
          putchar('?');
          continue;
        }
        if (currChar > 127) {
          putchar('M');
          putchar('-');

          if (currChar < 128 + 32) {
            putchar('^');
            putchar(currChar - 128 + 64);
            continue;
          }

          if (currChar >= 128 + 127) {
            putchar('^');
            putchar('?');
            continue;
          }

          putchar(currChar - 128);
          continue;
        }
      }

      putchar(currChar);
    }

    fclose(currentFile);
  }
}

void s21HelpInfo() {
  printf(
      "Usage: ./s21_cat [OPTION]... [FILE]...\n"
      "Concatenate FILE(s) to standard output.\n\n"
      "With no FILE, read standard input.\n\n"
      "  -b, --number-nonblank    number nonempty output lines, overrides -n\n"
      "  -e                       equivalent to -vE\n"
      "  -E,                      display $ at end of each line\n"
      "  -n, --number             number all output lines\n"
      "  -s, --squeeze-blank      suppress repeated empty output lines\n"
      "  -t                       equivalent to -vT\n"
      "  -T,                      display TAB characters as ^I\n"
      "  -v,                      use ^ and M- notation, except for LFD and "
      "TAB\n"
      "      --help               display this help and exit\n\n"
      "Examples:\n"
      "  ./s21_cat        Copy standard input to standard output.\n"
      "  ./s21_cat f g    Output f's contents, then g's contents.\n");
}