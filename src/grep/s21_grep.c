
#include "s21_grep.h"

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  struct str_options options = {0};
  parser(argc, argv, &options);
}
void out_consol(char **pattern, char **file, struct str_options *options,
                int count, int count_pattern, bool flag_does_not_exists) {
  char str[526] = "";
  int value;
  FILE *fp = NULL;
  regex_t reegex;
  bool func_for_o_was = false;
  // bool new_file = false;
  for (int i = 0; i < count; i++) {
    fp = fopen(file[i], "r");
    if (fp) {
      int kol_strok = 0;
      int curr_stroka = 0;
      int equals_strok = 0;

      while (!feof(fp)) {
        value = 2;
        if (fgets(str, 526, fp)) {
          kol_strok++;
          if (options->e == 1 || options->v == 1 || options->c == 1 ||
              options->l == 1 || options->n == 1 || options->f == 1 ||
              options->h == 1 || flag_does_not_exists || options->i == 1) {
            if (options->i == 0) {
              for (int k = 0; k < count_pattern && value != 0; k++) {
                if (strcmp(str, "\n") != 0 || strcmp(pattern[k], "\n") == 0) {
                  if (regcomp(&reegex, pattern[k], 0) != 0) {
                    fclose(fp);
                    regfree(&reegex);
                    exit(1);
                  }
                  // value = regcomp(&reegex, pattern[k], 0);
                  value = regexec(&reegex, str, 0, NULL, 0);
                  regfree(&reegex);
                }
              }
            } else {
              for (int k = 0; k < count_pattern && value != 0; k++) {
                if (strcmp(str, "\n") != 0 || strcmp(pattern[k], "\n") == 0) {
                  // value = regcomp(&reegex, pattern[k], REG_ICASE);
                  if (regcomp(&reegex, pattern[k], REG_ICASE) != 0) {
                    fprintf(stderr, "error regix");
                    fclose(fp);
                    regfree(&reegex);
                    exit(1);
                  }
                  value = regexec(&reegex, str, 0, NULL, REG_ICASE);
                  regfree(&reegex);
                }
              }
            }
          }
          if (value == 0 && options->v == 0) {
            equals_strok++;
          }
          if (value != 0 && options->v == 1) {
            equals_strok++;
          }

          if (options->o == 1 && options->c == 0 && options->v == 0 &&
              options->l == 0) {
            func_for_o_was = true;
            int k = 0;
            curr_stroka = kol_strok;
            char *buff_copy = str;
            int count_mathes_for_o = 0;
            while (k < count_pattern) {
              value = regcomp(&reegex, pattern[k], 0);
              if (value == 0) {
                regmatch_t pmatch[2];
                while (regexec(&reegex, buff_copy, 1, pmatch, 0) == 0) {
                  // printf("%s\n", buff_copy);
                  int size = pmatch[0].rm_eo - pmatch[0].rm_so;
                  if ((count >= 2) && (options->h == 0) &&
                      (count_mathes_for_o == 0)) {
                    printf("%s:", file[i]);
                  }
                  if (options->n && count_mathes_for_o == 0) {
                    printf("%d:", curr_stroka);
                  }
                  printf("%.*s\n", (int)size, buff_copy + pmatch[0].rm_so);
                  buff_copy += pmatch[0].rm_eo;
                  count_mathes_for_o++;
                }
              }
              k++;
              regfree(&reegex);
            }
          }

          if ((value == 0 && (options->v == 0) && (options->c == 0) &&
               (options->l == 0) && (options->o == 0) &&
               (options->e == 1 || options->i == 1 || options->f == 1 ||
                options->n == 1 || options->h == 1 || flag_does_not_exists))) {
            curr_stroka = kol_strok;
            if (options->h == 0) {
              if (count > 1) {
                printf("%s:", file[i]);
              }
            }
            if (options->n == 1) {
              printf("%d:", curr_stroka);
            }
            printf("%s", str);
          }
          if (value != 0 && (options->v == 1) && (options->l == 0) &&
              (options->c == 0)) {
            curr_stroka = kol_strok;
            if (options->h == 0) {
              if (count > 1) {
                printf("%s:", file[i]);
              }
            }
            if (options->n == 1) {
              printf("%d:", curr_stroka);
            }
            printf("%s", str);
          }
        }
      }
      if (options->c == 1) {
        if (options->h == 0) {
          if (count > 1) {
            printf("%s:", file[i]);
          }
        }

        if (options->l == 1) {
          if (equals_strok > 0)
            printf("%d\n", 1);
          else
            printf("%d\n", 0);
        } else {
          printf("%d\n", equals_strok);
        }
      }
      if (options->l == 1) {
        if (equals_strok > 0) printf("%s\n", file[i]);
      }
      // printf("%d", str[strlen(str) - 1]);

      if (func_for_o_was == false && curr_stroka == kol_strok &&
          curr_stroka != 0 && str[strlen(str) - 1] != 10) {
        printf("\n");
      }
      fclose(fp);
    } else {
      if (options->s == 0)
        fprintf(stderr, "grep: %s: No such file or directory\n", file[i]);
    }
  }
}
void parser(int argc, char *argv[], struct str_options *options) {
  int count = 0;
  int count_pattern = 0;
  int min_flag = 0;
  int flag_e_f = 0;
  char **pattern = NULL;
  char **file = NULL;
  bool pattern_was = false;
  bool flag_does_not_exists = true;
  for (int j = 1; j < argc; j++) {
    if (argv[j][0] == '-') {
      flag_does_not_exists = false;
      for (size_t k = 1; k < strlen(argv[j]); k++) {
        if (argv[j][k] == 'e' || argv[j][k] == 'f') {
          flag_e_f = 1;  // flag -e -f существует вприницпе
        }
      }
    }
  }
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if ((argv[i][1] == 'e' || argv[i][1] == 'f')) {
        if (strlen(argv[i]) > 2) {
          if (argv[i][1] == 'e') {
            pattern = for_flags_e(argv[i], pattern, &count_pattern);
          }
          if (argv[i][1] == 'f') {
            pattern = for_flags_f(argv[i], &count_pattern, pattern);
          }
          pattern_was = true;
        } else {
          pattern_was = false;
          min_flag = 1;  // флаг е или f есть в данный момент
        }
        full_switch(argv[i][1], options);
      } else {
        for (size_t k = 1; k < (size_t)strlen(argv[i]); k++) {
          if (argv[i][k] == 'e' || argv[i][k] == 'f') {
            min_flag = 1;
          }
          full_switch(argv[i][k], options);
        }
        pattern_was = false;
      }
    } else {
      if (min_flag == 1 ||
          (!pattern_was && flag_e_f == 0)) {  // тут обяз быть паттерн
        min_flag = 0;
        pattern_was = 1;
        if (argv[i - 1][1] == 'f') {
          pattern = flag_f_func(argv[i], &count_pattern, pattern);
        } else {
          pattern = for_fill_patterns(argv[i], pattern, &count_pattern);
        }
      } else {  // всегда файл
        file = for_fill_files(argv[i], file, &count);
      }
    }
  }
  out_consol(pattern, file, options, count, count_pattern,
             flag_does_not_exists);
  if (count_pattern != 0) {
    for (int k = 0; k < count_pattern; k++) free(pattern[k]);
    free(pattern);
  }
  if (count != 0) {
    for (int k = 0; k < count; k++) free(file[k]);
    free(file);
  }
}
void full_switch(char a, struct str_options *options) {
  switch (a) {
    case 'e':
      options->e = 1;
      break;
    case 'i':
      options->i = 1;
      break;
    case 'v':
      options->v = 1;
      break;
    case 'c':
      options->c = 1;
      break;
    case 'l':
      options->l = 1;
      break;
    case 'n':
      options->n = 1;
      break;
    case 'h':
      options->h = 1;
      break;
    case 's':
      options->s = 1;
      break;
    case 'f':
      options->f = 1;
      break;
    case 'o':
      options->o = 1;
      break;
  }
}

char **for_flags_e(char *str, char **pattern, int *count_pattern) {
  if (strlen(str) > 2) {
    int i = 2;
    *count_pattern = *count_pattern + 1;
    if ((*count_pattern) == 1)
      pattern = (char **)malloc(*count_pattern * sizeof(char *));
    else
      pattern = (char **)realloc(pattern, *count_pattern * sizeof(char *));
    pattern[*count_pattern - 1] =
        (char *)malloc((strlen(str) + 1 - 2) * sizeof(char));
    while (str[i] != '\0') {
      pattern[*count_pattern - 1][i - 2] = str[i];
      i++;
    }
    pattern[*count_pattern - 1][i - 2] = str[i];
  }
  return pattern;
}
char **flag_f_func(char *file, int *count_pattern, char **pattern) {
  char str[256];
  FILE *fp = NULL;
  fp = fopen(file, "r");
  char *pos = NULL;
  while (!feof(fp)) {
    if (fgets(str, 255, fp)) {
      if (str[0] != '\n' && (pos = strchr(str, '\n')) != NULL) {
        *pos = '\0';
      }
      *count_pattern = *count_pattern + 1;
      if ((*count_pattern) == 1)
        pattern = (char **)malloc(*count_pattern * sizeof(char *));
      else
        pattern = (char **)realloc(pattern, *count_pattern * sizeof(char *));
      pattern[*count_pattern - 1] =
          (char *)malloc((strlen(str) + 1) * sizeof(char));
      strcpy(pattern[*count_pattern - 1], str);
    }
  }
  fclose(fp);
  return pattern;
}
char **for_flags_f(char *str, int *count_pattern, char **pattern) {
  char *str_for_file = NULL;
  if (strlen(str) > 2) {
    int i = 2;
    str_for_file = (char *)malloc(((strlen(str) + 1) - 2) * sizeof(char));
    while (str[i] != '\0') {
      str_for_file[i - 2] = str[i];
      i++;
    }
    str_for_file[i - 2] = str[i];
    pattern = flag_f_func(str_for_file, count_pattern, pattern);
    free(str_for_file);
  }
  return pattern;
}
char **for_fill_patterns(char *str, char **pattern, int *count_pattern) {
  *count_pattern = *count_pattern + 1;
  if ((*count_pattern) == 1)
    pattern = (char **)malloc(*count_pattern * sizeof(char *));
  else
    pattern = (char **)realloc(pattern, *count_pattern * sizeof(char *));
  pattern[*count_pattern - 1] =
      (char *)malloc((strlen(str) + 1) * sizeof(char));
  strcpy(pattern[*count_pattern - 1], str);
  return pattern;
}
char **for_fill_files(char *str, char **file, int *count) {
  *count = *count + 1;
  if ((*count) == 1)
    file = (char **)malloc(*count * sizeof(char *));
  else
    file = (char **)realloc(file, *count * sizeof(char *));
  file[*count - 1] = (char *)malloc((strlen(str) + 1) * sizeof(char));
  strcpy(file[*count - 1], str);
  return file;
}
