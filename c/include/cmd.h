#ifndef AOCC_CMD_H
#define AOCC_CMD_H

typedef enum {
  cmd_none,
  cmd_run,
  cmd_help,
  cmd_unknown,
} Command;

typedef enum {
  cmd_run_pall,
  cmd_run_p1,
  cmd_run_p2,
} RunCmdPart;

typedef struct {
  int year;
  int day;
  RunCmdPart part;
  const char *input_version;
} RunOpt;

#endif
