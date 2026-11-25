#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

int build_input_path(char *path, int year, int day, const char *version) {
  return snprintf(path, 256, "../inputs/%d/%d/%s.txt", year, day,
                  (version == NULL) ? "full" : version);
}

const char *read_input(int year, int day, const char *version) {
  char path[256];
  if (build_input_path(path, year, day, version) < 0) {
    print_error_help_message(
        "failed to build input for year: %d, day: %d, version: %s", year, day,
        (version == NULL) ? "full" : version);
  }

  FILE *fp = fopen(path, "rb");
  if (fp == NULL) {
    char *err_msg = strerror(errno);
    print_error_help_message("failed to open file '%s': %s\n", path, err_msg);
    return NULL;
  }
  fseek(fp, 0, SEEK_END);
  long fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *input = malloc(fsize + 1);
  long read_bytes = fread(input, 1, fsize, fp);
  if (read_bytes != fsize) {
    printf("Read: %ld, size: %ld\n", read_bytes, fsize);
    printf("\nInput:\n%s\n", input);
    char *err_msg = strerror(errno);
    print_error_help_message("failed to read file '%s': %s\n", path, err_msg);
    return NULL;
  }
  fclose(fp);
  input[fsize] = '\0';
  return input;
}
