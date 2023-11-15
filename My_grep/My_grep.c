#include "My_grep.h"

int main(int argc, char *argv[]) {
  my_grep_opt opt = {0};
  if (argc == 1) {
    fprintf(stderr, "grep: missing operand\n");
  } else {
    if (!(parse_opts(argc, argv, &opt))) {
      output_file(argc, argv, opt);
    }
  }
  return 0;
}

int parse_opts(int argc, char *argv[], my_grep_opt *opt) {
  int back_char;
  while ((back_char = getopt_long(argc, argv, "inhlce:vf:", NULL, NULL)) !=
         -1) {
    switch (back_char) {
      case 'i':
        opt->i = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 'h':
        opt->h = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 'l':
        opt->l = 1;
        break;
      case 'c':
        opt->c = 1;
        break;
      case 'e':
        opt->e = 1;
        e_pattern(optarg, opt);
        break;
      case 'f':
        opt->f = 1;
        f_pattern(optarg, opt);
        break;
      case 'o':
        opt->o = 1;
        break;
      default:
        fprintf(stderr, "grep: illegal option -- %c\n", back_char);
        return 1;
    }
  }
  return 0;
}

void e_pattern(char *optarg, my_grep_opt *opt) {
  if (opt->pattern_count) strcat(opt->pattern_str, "|");
  strcat(opt->pattern_str, optarg);
  ++(opt->pattern_count);
}

void f_pattern(char *optarg, my_grep_opt *opt) {
  FILE *pattern_file;
  if ((pattern_file = fopen(optarg, "r")) == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
  } else {
    char pattern_str[BUFF_SIZE];
    while (fgets(pattern_str, BUFF_SIZE, pattern_file) != NULL) {
      if (opt->pattern_count) strcat(opt->pattern_str, "|");
      if (pattern_str[0] == '\n')
        strcat(opt->pattern_str, ".");
      else {
        if (pattern_str[strlen(pattern_str) - 1] == '\n')
          pattern_str[strlen(pattern_str) - 1] = '\0';
        strcat(opt->pattern_str, pattern_str);
      }
      ++(opt->pattern_count);
    }
  }
}

void output_file(int argc, char *argv[], my_grep_opt opt) {
  if (!opt.pattern_count) strcat(opt.pattern_str, argv[optind++]);
  regex_t pattern_struct = {0};
  regmatch_t match = {0};
  int reg_param = REG_EXTENDED;
  if (opt.i) reg_param = REG_EXTENDED | REG_ICASE;
  regcomp(&pattern_struct, opt.pattern_str, reg_param);
  FILE *file_name;
  for (int i = optind; i < argc; ++i) {
    if ((file_name = fopen(argv[i], "r")) == NULL) {
      if (!opt.s)
        fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
    } else {
      char file_str[BUFF_SIZE];
      int str_num = 1;
      int count_match = 0;
      while (fgets(file_str, BUFF_SIZE, file_name) != NULL) {
        int res_of_match = regexec(&pattern_struct, file_str, 1, &match, 0);
        if (file_str[strlen(file_str) - 1] == '\n')
          file_str[strlen(file_str) - 1] = '\0';
        if (opt.v) res_of_match = !res_of_match;
        if (!res_of_match) {
          ++count_match;
          if (!opt.c && !opt.l) {
            if (!opt.h && argc - optind > 1) printf("%s:", argv[i]);
            if (opt.n) printf("%d:", str_num);
            printf("%s\n", file_str);
          }
        }
        ++str_num;
      }
      if (opt.c) {
        if (!opt.h && argc - optind > 1) printf("%s:", argv[i]);
        printf("%d\n", count_match);
      }
      if (opt.l && count_match) printf("%s\n", argv[i]);

      fclose(file_name);
    }
  }
  regfree(&pattern_struct);
}
