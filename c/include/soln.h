#ifndef AOCC_SOLN_H
#define AOCC_SOLN_H

typedef struct {
  const char *input;
} SolutionCtx;

typedef int (*SolutionFn)(SolutionCtx *);

typedef struct {
  int year;
  int day;
  SolutionFn part_one;
  SolutionFn part_two;
} Solution;

#endif
