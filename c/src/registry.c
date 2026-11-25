#include "registry.h"
#include "soln.h"
#include <stdlib.h>

// Declare Solutions here
// int soln_y2025_d1_p1(SolutionCtx *);

static const Solution solutions[] = {
    // {2025, 1, soln_y2025_d1_p1, NULL}
    //
};

const Solution *find_solution(int year, int day) {
  int num_solutions = sizeof(solutions) / sizeof(solutions[0]);
  for (int i = 0; i < num_solutions; i++) {
    if (solutions[i].year == year && solutions[i].day == day) {
      return &solutions[i];
    }
  }
  return NULL;
}
