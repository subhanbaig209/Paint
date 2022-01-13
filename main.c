#include <stdio.h>
#include <stdbool.h>
#include "command.h"

int main(int argc, char *argv[]) {
  Board board;
  board.num_rows = 10;
  board.num_cols = 10;

  checkTerminalArgs(argc, argv, &board);

  return 0;
}
