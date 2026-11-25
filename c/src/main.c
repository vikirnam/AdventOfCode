#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"
#include "registry.h"
#include "soln.h"
#include "util.h"

void run_cmd(int arg_len, const char *args[]);
void run_cmd_run(RunOpt *opt);

Command parse_cmd(const char *);
void run_cmd_help(int, const char **);
RunOpt *parse_cmd_run(int, const char **);

int main(int argc, const char *argv[]) {
  if (argc == 1) {
    print_help_message(cmd_none);
    exit(0);
  }
  run_cmd(argc - 1, argv + 1);
  return 0;
}

Command parse_cmd(const char *cmd_str) {
  if (strcmp(cmd_str, "help") == 0) {
    return cmd_help;
  } else if (strcmp(cmd_str, "run") == 0) {
    return cmd_run;
  } else {
    return cmd_unknown;
  }
}

void run_cmd(int arg_len, const char *args[]) {
  Command cmd = parse_cmd(args[0]);
  const char **opts = (arg_len == 1) ? NULL : &args[1];
  switch (cmd) {
  case cmd_none:
    break;
  case cmd_help:
    run_cmd_help(arg_len - 1, opts);
    break;
  case cmd_run: {
    RunOpt *opt = parse_cmd_run(arg_len - 1, opts);
    if (opt == NULL) {
      exit(64);
    }
    run_cmd_run(opt);
    break;
  }
  case cmd_unknown:
    print_error_help_message("no such command: `%s`", cmd);
    exit(64);
  }
}

void run_cmd_run(RunOpt *opt) {
  const Solution *soln = find_solution(opt->year, opt->day);
  if (soln == NULL) {
    print_error_help_message("[Year: %d, Day: %d]: Solution Not Found\n",
                             opt->year, opt->day);
    exit(65);
  }
  SolutionCtx ctx = {0};
  ctx.input = read_input(opt->year, opt->day, opt->input_version);
  if (ctx.input == NULL) {
    exit(65);
  }
  switch (opt->part) {
  case cmd_run_pall:
    printf("Year: %d, Day: %d\n", opt->year, opt->day);
    printf("\tPart One: ");
    run_part(soln->part_one, &ctx);
    printf("\n\tPart Two: ");
    run_part(soln->part_two, &ctx);
    printf("\n");
    break;
  case cmd_run_p1:
    printf("Year: %d, Day: %d\n", opt->year, opt->day);
    printf("\tPart One: ");
    run_part(soln->part_one, &ctx);
    break;
  case cmd_run_p2:
    printf("Year: %d, Day: %d\n", opt->year, opt->day);
    printf("\tPart Two: ");
    run_part(soln->part_two, &ctx);
    break;
  }
}

void run_cmd_help(int opt_len, const char **opt) {
  if (opt_len == 0) {
    print_help_message(cmd_none);
    return;
  }
  Command cmd = parse_cmd(opt[0]);
  print_help_message(cmd);
}

RunOpt *parse_cmd_run(int opt_len, const char **options) {
  int opt_idx = 0;
  RunOpt *opt = (RunOpt *)malloc(sizeof(RunOpt));
  opt->year = 0;
  opt->day = 0;
  opt->part = cmd_run_pall;
  opt->input_version = NULL;
  while (opt_idx < opt_len) {
    const char *opt_str = options[opt_idx++];
    if (strcmp(opt_str, "-y") == 0 || strcmp(opt_str, "--year") == 0) {
      if (opt_idx >= opt_len) {
        print_error_help_message("--year takes an integer argument");
        return NULL;
      }
      int year = atoi(options[opt_idx++]);
      if (year == 0) {
        print_error_help_message("invalid year: '%s'", options[opt_idx - 1]);
        return NULL;
      }
      opt->year = year;
    } else if (strcmp(opt_str, "-d") == 0 || strcmp(opt_str, "--day") == 0) {
      if (opt_idx >= opt_len) {
        print_error_help_message("--day takes an integer argument");
        return NULL;
      }
      int day = atoi(options[opt_idx++]);
      if (day == 0) {
        print_error_help_message("invalid day: '%s'", options[opt_idx - 1]);
        return NULL;
      }
      opt->day = day;
    } else if (strcmp(opt_str, "-p") == 0 || strcmp(opt_str, "--part") == 0) {
      if (opt_idx >= opt_len) {
        print_error_help_message("--part takes an integer argument");
        return NULL;
      }
      int part = atoi(options[opt_idx++]);
      switch (part) {
      case 1:
        opt->part = cmd_run_p1;
        break;
      case 2:
        opt->part = cmd_run_p2;
        break;
      default:
        print_error_help_message("invalid part: '%s'\ndefaulting to both\n",
                                 options[opt_idx - 1]);
        opt->part = cmd_run_pall;
      }
    } else if (strcmp(opt_str, "-v") == 0 || strcmp(opt_str, "--ver") == 0) {
      if (opt_idx >= opt_len) {
        print_error_help_message("--part takes an integer argument");
        return NULL;
      }
      opt->input_version = options[opt_idx++];
    } else {
      print_error_help_message("unknown option %s", opt_str);
      return NULL;
    }
  }

  if (opt->year == 0) {
    print_error_help_message("option '--year' not supplied");
    return NULL;
  } else if (opt->day == 0) {
    print_error_help_message("option '--day' not supplied");
  }
  return opt;
}
