# cat
My implementation of cat utility (C language).
Implementation of some flags was done as in Ubuntu OS (e.g. "long" flags like --number or displaying of non-printing symbols)

### cat Usage

Usage of the utility:

`s21_cat [OPTION] [FILE]...`

### cat Options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only non-empty lines |
| 2 | -e implies -v (GNU only: -E the same, but without implying -v) | but also displays end-of-line characters as $  |
| 3 | -n (GNU: --number) | number all output lines |
| 4 | -s (GNU: --squeeze-blank) | squeeze multiple adjacent blank lines |
| 5 | -t implies -v (GNU: -T the same, but without implying -v) | but also displays tabs as ^I 
| 6 | --help | displays help info and list of available flags
| 7 | no option | repeats text sent to stdin

### cat Tests
There are two types of tests available:
* Comparison of the results of my cat and standard cat utility. For the reference was taken work of cat utility in OS Ubuntu ver 22.04. So if you're testing it in MAC OS, you'll have a lot of failed tests - it's normal.
* Tests for memory leaks check made via checking valgrind utility's results. 

Tests can be launched via command `make tests` and `make leakscheck` respectively.
