#ifndef S21_GREP_H
#define S21_GREP_H
#include <stdbool.h>
struct str_options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};
void print_curr_stroka(char *file, int count, int curr_stroka, char *str);
void flags(struct str_options *options);
void flags_null(struct str_options *options);
char **for_fill_patterns(char *str, char **pattern, int *count_pattern);
char **for_fill_files(char *str, char **file, int *count);
char **flag_f_func(char *file, int *count_pattern, char **pattern);
char **for_flags_f(char *str, int *count_pattern, char **pattern);
char **for_flags_e(char *str, char **pattern, int *count_pattern);
void printff(char *file, char *str, int count);
void out_consol(char **pattern, char **file, struct str_options *options,
                int count, int count_pattern, bool flag_does_not_exists);
void parser(int argc, char *argv[], struct str_options *options);
void full_switch(char a, struct str_options *options);
void process(int argc, char *argv[], struct str_options *options);

#endif  // S21_GREP_H
