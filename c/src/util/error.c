#include <stdarg.h>
#include <stdio.h>

#include "util.h"

// clang-format off
const char *help_message =
"Advent of Code Runner\n"
"\n"
"Usage: aocc [OPTIONS] [COMMAND]\n"
"\n"
"Commands:\n"
"\trun        Runs the solution for specific year and day\n"
"\thelp       Show this help message\n"
;


const char *run_help_message =
"Advent of Code Runner\n"
"\n"
"Usage: aocc run --year <year> --day <day> [OPTIONS]\n"
"\n"
"Options:\n"
"\t-y, --year <year>       Year (required)\n"
"\t-d, --day  <day>        Day  (required)\n"
"\t-p, --part <part>       Part\n"
"\t-v, --ver  <version>    Input version to run against\n"
;

// clang-format on

void print_help_message(Command cmd) {
  switch (cmd) {
  case cmd_none:
    fputs(help_message, stderr);
    break;
  case cmd_run:
    fputs(run_help_message, stderr);
    break;
  case cmd_help:
    fputs(help_message, stderr);
    break;
  case cmd_unknown:
    print_error_help_message("unknown command");
    break;
  }
}

void print_error_help_message(const char *msg_fmt, ...) {
  va_list args;
  va_start(args, msg_fmt);
  vfprintf(stderr, msg_fmt, args);
  fprintf(stderr, "\n%s", help_message);
}
