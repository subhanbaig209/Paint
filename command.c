#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "command.h"

void print_help(){
  char reset_stdin;
  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
  scanf("%c", &reset_stdin);
}


char **create_board(int num_rows, int num_cols)
{
    char star_char = '*';
    char **board = (char **)malloc(num_rows * sizeof(*board));
    for (int i = 0; i < num_rows; i++)
    {
        board[i] = (char *)malloc(num_cols * sizeof(char));
        for (int j = 0; j < num_cols; j++)
        {
            board[i][j] = star_char;
        }
    }
    return board;
}

void print_board(Board *bd)
{
  bool extra_space = false;
  if (bd->num_rows > 9 || bd->num_cols > 9) {
    extra_space = true;
  }
    for (int i = bd->num_rows - 1; i >= 0; i--)
    {
      if (extra_space == true) {
        printf("%2d ", i);
      }
      else {
        printf("%d", i);
      }
    
        for (int j = 0; j < bd->num_cols; j++)
        {
          if (extra_space == true) {
            printf(" %c ", bd->board[i][j]);
          }
          else {
            printf(" %c", bd->board[i][j]);
          }
        }
        if (extra_space == false) {
          printf(" \n");

        }
        else {
          printf("\n");
        }
        
    }
    if (extra_space == true) {
      printf("   ");
    }
    else {
      printf("  ");

    }
    for (int i = 0; i < bd->num_cols; i++)
    {
      if (extra_space == true) {
        printf("%2d ", i);
      }
      else { 
        printf("%d ", i);
      }
        
    }
    printf("\n");
}

void create_game(Board *bd)
{
    bd->board = create_board(bd->num_rows, bd->num_cols);
}

void display_board(Board *board)
{
    print_board(board);
}

void free_board(Board *bd) {
  for (int i = 0; i < bd->num_rows; ++i)
    {
      free(bd->board[i]);
    }
    bd->board = NULL;
    //free(bd);
    
  }

void quit(Board *bd) {
  free_board(bd);
  exit(1);
  }
  

void save(Board *bd, char* file_name) {
  FILE *fp;
  fp = fopen(file_name, "w");
  if (fp == NULL) {
    printf("Failed to open file: %s \n", file_name);
  }
  else {
    double num;
  

    fprintf(fp, "%d %d\n", bd->num_rows, bd->num_cols);

    for (int i = 0; i < bd->num_rows; i++) {
      for (int j = 0; j < bd->num_cols; j++ ) {
        fprintf(fp, "%c ", bd->board[i][j]);
      }
      fprintf(fp, "\n");
    }
    fclose(fp);

    }
  
  
  }
void single_write(Board *bd, int row, int col) {
  if (bd->board[row][col] == '*' || bd->board[row][col] == '-') {
    bd->board[row][col] = '-';
  }
  else {
    bd->board[row][col] = '+';
  }

}

void diagonal(Board *bd, int row_start, int col_start, int row_end, int col_end) {
  int increment = 0;
  int r_start;
  int r_end;
  int c_start;
  int c_end;
  double slope = (row_start - row_end) / (col_start - col_end);
  if (slope != 1.0 && slope != -1.0) {
    printf("Cannot draw the line as it is not straight.\n");
  }
  if (row_start > row_end) {
    r_start = row_end;
    r_end = row_start;
  }
  else {
    r_start = row_start;
    r_end = row_end;
  }
  if (col_start > col_end) {
    c_start = col_end;
    c_end = col_start;
  }
  else {
    c_start = col_start;
    c_end = col_end;
  }

  if (slope == 1){
    for (int i = r_start; i <= r_end; i++) {
      if (bd->board[i][c_start+increment] == '/' || bd->board[i][c_start+increment] == '*') {
        bd->board[i][c_start+increment] = '/';
      }
      else {
        bd->board[i][c_start+increment] = '+';
      }
      increment+=1;

    } 

  }
  else if (slope == -1) {
    increment = 0;
    for (int i = r_start; i <= r_end; i++) {
      if (bd->board[i][c_start-increment] == '\\' ||bd->board[i][c_end-increment] == '*' || bd->board[i][c_end-increment] == '|') {
        bd->board[i][c_end-increment] = '\\';
      
      }
      else if (bd->board[i][c_end-increment] == '*' || bd->board[i][c_end-increment] == '/') {
        bd->board[i][c_end-increment] = '+';
      }
      increment+=1;
    
    } 
  } 
  
}

void horizontal_write(Board *bd, int row, int col_start, int col_end) {
  int start;
  int end;
  if (col_start > col_end) {
    start = col_end;
    end = col_start;
  }
  else {
    start = col_start;
    end = col_end;
  }
  for (int i = start; i<=end; i++) {
    if(bd->board[row][i] == '*' || bd->board[row][i] == '-') {
      bd->board[row][i] = '-';
    }
    else {
      bd->board[row][i] = '+';
    }

  }
}
void vertical_write(Board *bd, int col, int row_start, int row_end) {
  int start;
  int end;
  if (row_start > row_end) {
    start = row_end;
    end = row_start;
  }
  else {
    start = row_start;
    end = row_end;
  }
  for (int i = start; i<=end; i++) {
    if(bd->board[i][col] == '*' || bd->board[i][col] == '|') {
      bd->board[i][col] = '|';
    }
    else {
      bd->board[i][col] = '+';
    }
    
  }
}

void write_board(Board *bd, int row_start, int col_start, int row_end, int col_end) {
  if (col_end > bd->num_cols) {
    printf("Improper draw command.\n");
  }
  else if (row_end < 0) {
    printf("Improper draw command.\n");
  }
  else if (col_start < 0) {
    printf("Improper draw command.\n");
  }
  else if (row_start > bd->num_rows) {
    printf("Improper draw command.\n");
  }

  else if (row_start == row_end) {
    if  (col_start == col_end){
      single_write(bd, row_start, col_start);
    }
    else if (col_start != col_end) {
      horizontal_write(bd, row_start, col_start, col_end);
    }
    
  }
  else if (col_start == col_end) {
    if (row_start != row_end) {
      vertical_write(bd, col_start, row_start, row_end);
    }
  }
  else if (row_start != row_end && col_start != col_end){
    diagonal(bd, row_start, col_start, row_end, col_end);
  }
  
}
void erase_char(Board *bd, int row, int col){
  if (col >= bd->num_cols) {
    printf("Improper erase command.\n");
  }
  else if (col < 0) {
    printf("Improper erase command.\n");
  }
  else if (row >= bd->num_rows) {
    printf("Improper erase command.\n");
  }
  else if (row < 0) {
    printf("Improper erase command.\n");
  }

  else {
    bd->board[row][col] = '*';
  }



}
void resize(Board *bd, int rows, int cols){
  if (rows < 1) {
    printf("Improper resize command.\r");
    return;
  }
  else if (cols < 1) {
    printf("Improper resize command.\n");
    return;
  }
  //free_board(bd);


  bd->board = realloc(bd->board, rows * sizeof(bd->board));
  for (int i = 0; i < rows; i++)
    {
        bd->board[i] = (char *)realloc(bd->board[i], cols * sizeof(char));
    }
  for (int i = bd->num_rows; i < rows; i++) {
    for (int j = 0; j < cols; j++)
        {
            bd->board[i][j] = '*';
         
        }
  }
  for (int i = 0; i < rows; i++) {
    for (int j = bd->num_cols; j < cols; j++)
        {
            bd->board[i][j] = '*';
        }
  }
    
  bd->num_rows = rows;
  bd->num_cols = cols;
  
}
void add(Board *bd, char r_or_c, int num){
  if (r_or_c == 'r') {
    if (num > bd->num_rows || num < 0) {
      printf("Improper add command.\n");
      return;
    }
  bd->num_rows = bd->num_rows + 1;
  bd->board = realloc(bd->board, bd->num_rows * sizeof(bd->board));
  for (int i = 0; i < bd->num_rows; i++)
    {
        bd->board[i] = (char *)realloc(bd->board[i], bd->num_cols * sizeof(bd->board[i]));
    }
    for (int i = bd->num_rows-1; i>num; i--){
      for (int j = 0; j < bd->num_cols; j++) {
        bd->board[i][j] = bd->board[i-1][j];
      }
      
    } 

    for (int j = 0; j < bd->num_cols; j++)
        {
            bd->board[num][j] = '*';
        }
    
  }
  else if (r_or_c == 'c') {
    if (num > bd->num_cols || num < 0) {
      printf("Improper add command.\n");
      return;
    }
    bd->num_cols = bd->num_cols + 1;
    bd->board = realloc(bd->board, bd->num_cols * sizeof(bd->board));

    for (int i = 0; i < bd->num_rows; i++)
    {
        bd->board[i] = (char *)realloc(bd->board[i], bd->num_cols * sizeof(bd->board[i]));
    }
    for (int i = 0; i < bd->num_rows; i++){
      for (int j = bd->num_cols-1; j > num; j--) {
        bd->board[i][j] = bd->board[i][j-1];
      }
      
    } 

    for (int j = 0; j < bd->num_rows; j++)
        {
            bd->board[j][num] = '*';
        }
    
  }

  else {
    printf("Improper add command.\n");
    return;
}

}

void delete_rc(Board *bd, char r_or_c, int num){
  if (r_or_c == 'r') {
    if (num >= bd->num_rows || num < 0) {
      printf("Improper delete command.\n");
      return;
    }
    for (int i = num; i<bd->num_rows-1; i++){
      for (int j = 0; j < bd->num_cols; j++) {
        bd->board[i][j] = bd->board[i+1][j];
      }
    }

    bd->num_rows = bd->num_rows-1;
    bd->board = realloc(bd->board, bd->num_rows * sizeof(bd->board));

  for (int i = 0; i < bd->num_rows; i++)
    {
        bd->board[i] = (char *)realloc(bd->board[i], bd->num_cols * sizeof(bd->board[i]));
    }

      

  }
  else if (r_or_c == 'c') {
    if (num >= bd->num_cols || num < 0) {
      printf("Improper delete command.\n");
      return;
    }
    for (int i = 0; i<bd->num_rows; i++){
      for (int j = num; j < bd->num_cols; j++) {
        bd->board[i][j] = bd->board[i][j+1];
      }
    }

    bd->num_cols = bd->num_cols-1;
    bd->board = realloc(bd->board, bd->num_rows * sizeof(bd->board));
    for (int i = 0; i < bd->num_rows; i++) {
      bd->board[i] = (char *)realloc(bd->board[i], bd->num_cols * sizeof(bd->board[i]));
    }
  

  }
  else {
    printf("Improper delete command.\n");
    return;

  }

}


void load(Board* bd, char* file_name){

  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) {
    printf("Failed to open file: %s\n", file_name);
    return;
  }

  free_board(bd);
  char c;


  fscanf(fp, "%d %d\n", &bd->num_rows, &bd->num_cols);
  bd->board = create_board(bd->num_rows, bd->num_cols);
  for (int i = 0; i < bd->num_rows; i++) {
    for (int j = 0; j < bd->num_cols; j++ ) {
      fscanf(fp, "%c ", &c);
      bd->board[i][j] = c;
    }
  }
  fclose(fp);
}

void choose_command(Board *bd) {
  char string[1000];
  char command, c2;
  int num[4];
  char r_or_c;
  char file_name[20];
  char reset_stdin;
  printf("Enter your command: ");
  scanf("%[^\n]s", string);
  sscanf(string, "%c", &command);
  

  switch(command){
    case 'h':
    if (strlen(string) > 1) {
      printf("Unrecognized command. Type h for help.\n");
      scanf("%c", &reset_stdin);
    }
    else {
      print_help();

    }
    
      break;
    case 'q':
    if (strlen(string) > 1) {
      printf("Unrecognized command. Type h for help.\n");
      scanf("%c", &reset_stdin);
    }
      else {
      quit(bd);

    }
    
      break;
    case 's':
      sscanf(string, "%c %s", &command, file_name);
      
        save(bd, file_name);
  
      scanf("%c", &reset_stdin);
      break;
    case 'w':
      sscanf(string, "%c %d %d %d %d", &command, &num[0],&num[1], &num[2], &num[3]);
      if (num[0] < 0 || num[0] >= bd->num_rows) {
        printf("Improper draw command.\n");
        scanf("%c", &reset_stdin);
        
      }
      
      else if (num[2] < 0 || num[2] >= bd->num_rows) {
        printf("Improper draw command.\n");
        scanf("%c", &reset_stdin);
      }
      else if (num[1] < 0 || num[1] >= bd->num_cols) {
        printf("Improper draw command.\n");
        scanf("%c", &reset_stdin);
      }
      else if (num[3] < 0 || num[3] >= bd->num_cols) {
        printf("Improper draw command.\n");
        scanf("%c", &reset_stdin);
      }
      else {
        write_board(bd, num[0],num[1], num[2], num[3]);
        scanf("%c", &reset_stdin);

      }
  
      break;
    case 'e':
      sscanf(string, "%c %d %d", &command, &num[0],&num[1]);
      erase_char(bd, num[0], num[1]);
      scanf("%c", &reset_stdin);
      break;
    case 'r':
      sscanf(string, "%c %d %d", &command, &num[0],&num[1]);
      resize(bd, num[0], num[1]);
      scanf("%c", &reset_stdin);
      break;
    case 'a': 
      sscanf(string, "%c %c %d", &command, &r_or_c, &num[0]);
      if ((string[3]) != ' ') {
        printf("Improper add command.\n");
        scanf("%c", &reset_stdin);
        break;
      }
      else {
        add(bd, r_or_c, num[0]);
        scanf("%c", &reset_stdin);
      }
      break;
    case 'd':
      sscanf(string, "%c %c %d", &command, &r_or_c, &num[0]);
      if (string[3] != ' ') {
        printf("Improper delete command.\n");
        scanf("%c", &reset_stdin);
        break;
      }
      else {
        delete_rc(bd, r_or_c, num[0]);
        scanf("%c", &reset_stdin);
      }
      break;
    case 'l':
      sscanf(string, "%c %s", &command, file_name);
      scanf("%c", &reset_stdin);
      load(bd, file_name);
      break;
    default:
      printf("Unrecognized command. Type h for help.\n");
      scanf("%c", &reset_stdin);
      break;
  }
}

void play_game(Board *bd)
{
  while (true) {
    display_board(bd);
    choose_command(bd);
  }

}

bool isNumber(char number[])
{
    int i = 0;
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

void noArgsGame(Board *bd) {
  create_game(bd);
  play_game(bd);
}

void wrongNumCommandLineArgs(Board *bd) {
  printf("Wrong number of command line arguements entered.\nUsage: ./paint.out [num_rows num_cols]\nMaking default board of 10 X 10.\n");
  create_game(bd);
  play_game(bd);
}

void checkValidInput(Board *bd,  char** argv) {
    if (!isNumber(argv[1])) {
      printf("The number of rows is not an integer.\n")
      ;
      printf("Making default board of 10 X 10.\n");
   
     
      
    } else if(atoi(argv[1]) < 1) {
      printf("The number of rows is less than 1.\n");
      printf("Making default board of 10 X 10.\n");
    
     
    } 
    else if (!isNumber(argv[2])) {
      printf("The number of columns is not an integer.\n");
      printf("Making default board of 10 X 10.\n");
   
    } 
    
    else if(atoi(argv[2]) < 1) {
      printf("The number of columns is less than 1.\n");
      printf("Making default board of 10 X 10.\n");
     
      
    }
    else {
      sscanf(argv[1], "%d", &bd->num_rows);
      sscanf(argv[2], "%d", &bd->num_cols);

    }

      create_game(bd);
      play_game(bd);

}
void checkTerminalArgs(int argc, char **argv, Board *bd){
  if (argc == 1) { 
    noArgsGame(bd);
    
  }
  if (argc == 2 || argc > 3) {
    wrongNumCommandLineArgs(bd);
  }

  if (argc == 3) {
    checkValidInput(bd, argv);
  }
}
