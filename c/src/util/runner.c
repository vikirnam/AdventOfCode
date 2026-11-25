#include <stdio.h>

#include "util.h"

void run_part(SolutionFn part_fn, SolutionCtx *ctx) {
  if (part_fn) {
    printf("%d", part_fn(ctx));
  } else {
    printf("Solution Not Found");
  }
}
