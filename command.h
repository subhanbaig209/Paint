#ifndef COMMAND_H
#define COMMAND_H

typedef struct Board_struct {
  int num_rows;
  int num_cols;
  char** board;
} Board;


void print_help();
char **create_board(int num_rows, int num_cols);
void print_board(Board *bd);
void create_game(Board *bd);
void display_board(Board *board);
void free_board(Board *bd);
void quit(Board *bd);
void save(Board *bd, char* file_name);
void write_board(Board *bd, int row_start, int col_start, int row_end, int col_end);
void single_write(Board *bd, int row, int col);
void horizontal_write(Board *bd, int row, int col_start, int col_end);
void vertical_write(Board *bd, int col, int row_start, int row_end);
void diagonal(Board *bd, int row_start, int col_start, int row_end, int col_end);
void erase_char(Board *bd, int row, int col);
bool isNumber(char number[]);
void resize(Board *bd, int rows, int cols);
void add(Board *bd, char r_or_c, int num);
void delete_rc(Board *bd, char r_or_c, int num);
void load(Board* bd, char* file_name);
void choose_command(Board *bd);
void play_game(Board *bd);
void noArgsGame(Board *bd);
void wrongNumCommandLineArgs(Board *bd);
void checkValidInput(Board *bd,  char** argv);
void checkTerminalArgs(int argc, char **argv, Board *bd);
int checkIfFileExists(char* filename);



#endif
