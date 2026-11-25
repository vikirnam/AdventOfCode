#ifndef AOCC_UTIL_H
#define AOCC_UTIL_H

#include "cmd.h"
#include "soln.h"

// util/error.c
void print_help_message(Command);
void print_error_help_message(const char *msg_fmt, ...);

// util/input.c
const char *read_input(int year, int day, const char *version);
int build_input_path(char *path, int year, int day, const char *version);

// util/runner.c
void run_part(SolutionFn part_fn, SolutionCtx *ctx);

#endif
