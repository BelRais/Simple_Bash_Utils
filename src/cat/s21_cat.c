#include <getopt.h>
#include <stdio.h>
struct str_options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int T;
  int E;
};
void no_flags(int argc, char *argv[]);
void process(int argc, char *argv[], struct str_options options);
int main(int argc, char *argv[]) {
  struct str_options options = {0};
  const char *short_options = "+benvstTE";
  const struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                        {"number", 0, 0, 'n'},
                                        {"squeeze-blank", 0, 0, 's'},
                                        {0, 0, 0, 0}};
  int rez;
  int option_index;
  while ((rez = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (rez) {
      case 'b':
        options.b = 1;
        break;
      case 'e':
        options.e = 1;
        options.v = 1;
        break;
      case 'n':
        options.n = 1;
        break;
      case 's':
        options.s = 1;
        break;
      case 't':
        options.t = 1;
        options.v = 1;
        break;
      case 'T':
        options.t = 1;
        break;
      case 'E':
        options.e = 1;
        break;
      case 'v':
        options.v = 1;
        break;
    }
    //    printf("%d", options.b);
  }

  process(argc, argv, options);
}
void no_flags(int argc, char *argv[]) {
  char cur;
  FILE *fp = NULL;
  while (optind < argc) {
    fp = fopen(argv[optind], "r");
    if (fp) {
      while ((cur = fgetc(fp)) != EOF) {
        printf("%c", cur);
      }
    }
    fclose(fp);
    optind++;
  }
}
void process(int argc, char *argv[], struct str_options options) {
  if (options.b == 1 && options.n == 1) {
    options.n = 0;
  }
  if (optind == 1) {
    no_flags(argc, argv);
    return;
  }
  FILE *fp = NULL;
  while (optind++ < argc) {
    fp = fopen(argv[optind - 1], "r");
    if (fp) {
      int cur;          /// рисует текст
      int num_cir = 0;  /// нумерация
      int out_str = 1;  /// конец строк
      int s_flag = 0;   /// для s счетчик строк
      while ((cur = fgetc(fp)) != EOF) {
        if (options.s == 1) {  //// тут идет -s (работает)
          if (cur == '\n') {
            s_flag += 1;
          } else {
            s_flag = 0;
          }
        }
        if (options.b == 1) {  //// Тут идет -b (работает)
          if (cur != '\n') {
            if (out_str == 1) {
              printf("%6d\t", ++num_cir);
              out_str = 0;
            }
          } else {
            out_str = 1;
          }
        }
        if (options.n == 1) {  //// Тут идет -n (работает)
          if (out_str == 1) {
            if (options.s == 0 ||
                (options.s == 1 && (s_flag >= 0 && s_flag <= 2))) {
              printf("%6d\t", ++num_cir);
            }
            out_str = 0;
          }
          if (cur == '\n') {
            out_str = 1;
          }
        }
        if (s_flag == 3) continue;
        if (options.e == 1) {  ///// Тут идет -e (работает)
          if (cur == '\n') {
            if (options.s == 0 ||
                (options.s == 1 && (s_flag >= 0 && s_flag <= 2))) {
              printf("%c", '$');
            }
          }
        }
        if (options.t == 1) {  //// -t (работает)
          if (cur == '\t') {
            printf("^%c", cur + 64);
            continue;
          }
        }
        if (options.v == 1) {  /// тут идет -v (работает)
          if (cur >= 0 && cur < 32 && cur != '\n' && cur != '\t') {
            printf("^%c", cur + 64);
            continue;
          } else {
            if (cur == 127) {
              printf("^?");
              continue;
            }
          }
        }
        if (optind != 2 && s_flag >= 0 && s_flag <= 2) {
          if (options.t == 1) {
            if (cur != '\t' && cur != '\v') {
              printf("%c", cur);
            }
          } else {
            printf("%c", cur);
          }
        }
      }
    }
  }
  fclose(fp);
}
