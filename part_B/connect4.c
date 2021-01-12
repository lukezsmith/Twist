//You can include any of headers defined in the C11 standard here. They are:
//assert.h, complex.h, ctype.h, errno.h, fenv.h, float.h, inttypes.h, iso646.h, limits.h, locale.h, math.h, setjmp.h, signal.h, stdalign.h, stdarg.h, stdatomic.h, stdbool.h, stddef.h, stdint.h, stdio.h, stdlib.h, stdnoreturn.h, string.h, tgmath.h, threads.h, time.h, uchar.h, wchar.h or wctype.h
//You may not include any other headers.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include"connect4.h"

struct board_structure {
  char (*rows)[512];
  int height;
  int width;
};

board setup_board(){
  // initial row and column size in order to play connect4
  int maxSize = 512;

  // allocate memory for board struct
  struct board_structure *B;
  B = (struct board_structure *) malloc(sizeof(struct board_structure));

  // dynamically allocate memory for dynamic amount of rows
  if (!(B->rows = malloc (maxSize * sizeof (char *)))) {
    // not enough memory to assign
    fprintf (stderr, "Error: Insufficient memory to store board.\n");
    exit(1);
  }

  B->height = 4;
  B->width = 4;

  // return board address
  return B;

}

void cleanup_board(board u){
  // free dynamically allocated board row memory
  free(u->rows);
  // free dynamically allocated board struct memory
  free(u);
}

void read_in_file(FILE *infile, board u){
  int n = 0;
  int lineLength = 0;
  int maxHeight = 4;
  int maxWidth = 512;
   
  // create pointer to char array of size 512
  char (*rows)[maxWidth] = NULL;

 
  // iterate through each line in infile
  while (n< maxHeight && fgets (u->rows[n], maxWidth, infile)) {
      // if first line
      if (n == 0){
        // set linelength for number of characters in first line
        lineLength = strlen(u->rows[n]) -1 ;
        u->width = lineLength;

        // incorrect board dimensions
        if (lineLength <4 || lineLength > 512){
          fprintf (stderr, "Error: Invalid board size.\n");
          exit(1);
        }          
      }

      // check all lines are same length
      if ((int) strlen(u->rows[n])-1 != lineLength){
          fprintf (stderr, "Error: Invalid board size.\n");
          exit(1);
      }
      // assign pointer to char array
      char *p = u->rows[n];
      // iterate until newline
      for (; *p && *p != '\n'; p++) {}
      // check line is not empty
      if (*p != '\n') {
        int chr;
        do {
        chr = fgetc(infile);
        // discard unwanted input
        } while ((chr != EOF) && (chr != '\n'));
      }
      // reset pointer
      *p = 0;
      // if maxHeight has been reached then we need to increase limit and allocate more memory
      if (++n == maxHeight) {
        // allocate more memory to temp pointer
        void *tmp = realloc (u->rows, 2 * maxHeight * sizeof *rows);
        // check that the allocation was possible
        if (!tmp) {
          fprintf (stderr, "Error: Insufficient memory to store board.\n");
          exit(1);
        }
        // assign larger memory block to LINES (RENAME????)
        u->rows = tmp;
        // update new height limit
        maxHeight *= 2;
      }
  }
  // set board height
  u->height = n;
}

void write_out_file(FILE *outfile, board u){
  char symbols[] =  {'x', 'o'};

  // check for winner
  for (int k = 0; k < 2; k++){
    // horizontal win check
    for (int j = 0; j<u->width-3 ; j++ ){
      for (int i = 0; i<u->height; i++){
        if (u->rows[i][j] == symbols[k] && u->rows[i][j+1] == symbols[k] && u->rows[i][j+2] == symbols[k] && u->rows[i][j+3] == symbols[k]){
          // capitalise symbols
          u->rows[i][j] = toupper(symbols[k]);
          u->rows[i][j+1] = toupper(symbols[k]);
          u->rows[i][j+2] = toupper(symbols[k]);
          u->rows[i][j+3] = toupper(symbols[k]);
            for (int i = 0; i < u->height; i++){
              fprintf (outfile, "%s\n", u->rows[i]);
          }
          return;
        }           
      }
    }
    // vertical win check
    for (int i = 0; i<u->height-3; i++ ){
      for (int j = 0; j<u->width; j++){
        if (u->rows[i][j] == symbols[k] && u->rows[i+1][j] == symbols[k] && u->rows[i+2][j] == symbols[k] && u->rows[i+3][j] == symbols[k]){
          // capitalise symbols
          u->rows[i][j] = toupper(symbols[k]);
          u->rows[i+1][j] = toupper(symbols[k]);
          u->rows[i+2][j] = toupper(symbols[k]);
          u->rows[i+3][j] = toupper(symbols[k]);
          for (int i = 0; i < u->height; i++){
              fprintf (outfile, "%s\n", u->rows[i]);
          }
          return;
        }           
      }
    }
    // diagonal (ascending) win check
    for (int i=3; i<u->height; i++){
      for (int j=0; j<u->width-3; j++){
        if (u->rows[i][j] == symbols[k] && u->rows[i-1][j+1] == symbols[k] && u->rows[i-2][j+2] == symbols[k] && u->rows[i-3][j+3] == symbols[k]){
          // capitalise symbols
          u->rows[i][j] = toupper(symbols[k]);
          u->rows[i-1][j+1] = toupper(symbols[k]);
          u->rows[i-2][j+2] = toupper(symbols[k]);
          u->rows[i-3][j+3] = toupper(symbols[k]);
          for (int i = 0; i < u->height; i++){
              fprintf (outfile, "%s\n", u->rows[i]);
          }
          return;
        }
      }
    }
        // diagonal (descending) win check
    for (int i=3; i<u->height; i++){
      for (int j=3; j< u->width; j++){
        if (u->rows[i][j] == symbols[k] && u->rows[i-1][j-1] == symbols[k] && u->rows[i-2][j-2] ==symbols[k] && u->rows[i-3][j-3] == symbols[k]){
          // capitalise symbols
          u->rows[i][j] = toupper(symbols[k]);
          u->rows[i-1][j-1] = toupper(symbols[k]);
          u->rows[i-2][j-2] = toupper(symbols[k]);
          u->rows[i-3][j-3] = toupper(symbols[k]);
          for (int i = 0; i < u->height; i++){
              fprintf (outfile, "%s\n", u->rows[i]);
          }
          return;              
        }
      }
    }
  }
  // no winners
  for (int i = 0; i < u->height; i++){
    fprintf (outfile, "%s\n", u->rows[i]);
  }
  return;

}

char next_player(board u){
  int token_count = 0;

  // count tokens on board
  for (int i = 0; i < u->height; i++){
    for (int j = 0; j < u->width; j++){
      // there is an available slot
      if(u->rows[i][j] != '.'){
        token_count +=1; 
      }
    }
  }
  // if odd turn it is x's turn
  if(token_count == 0 || token_count % 2 == 0){
    return 'x';
  }else{
    // else it is o's turn 
    return 'o';
  }

}

char current_winner(board u){
  int emptySpace = 1;
  char symbols[] =  {'X', 'O'};
  
  // check for winner
  for (int k = 0; k < 2; k++){
    // horizontal win check
    for (int j = 0; j<u->width-3 ; j++ ){
      for (int i = 0; i<u->height; i++){
        if (u->rows[i][j] == symbols[k] && u->rows[i][j+1] == symbols[k] && u->rows[i][j+2] == symbols[k] && u->rows[i][j+3] == symbols[k]){
          return symbols[k];
        }           
      }
    }
    // vertical win check
    for (int i = 0; i<u->height-3; i++ ){
      for (int j = 0; j<u->width; j++){
        if (u->rows[i][j] == symbols[k] && u->rows[i+1][j] == symbols[k] && u->rows[i+2][j] == symbols[k] && u->rows[i+3][j] == symbols[k]){
          return symbols[k];
        }           
      }
    }
    // diagonal (ascending) win check 
    for (int i=3; i<u->height; i++){
      for (int j=0; j<u->width-3; j++){
        if (u->rows[i][j] == symbols[k] && u->rows[i-1][j+1] == symbols[k] && u->rows[i-2][j+2] == symbols[k] && u->rows[i-3][j+3] == symbols[k]){
          return symbols[k];
        }
      }
    }
    // diagonal (descending) win check
    for (int i=3; i<u->height; i++){
      for (int j=3; j< u->width; j++){
        if (u->rows[i][j] == symbols[k] && u->rows[i-1][j-1] == symbols[k] && u->rows[i-2][j-2] ==symbols[k] && u->rows[i-3][j-3] == symbols[k]){
          return symbols[k];
        }
      }
    }
  }

    // check board is not full
  for (int i = 0; i < u->height; i++){
    for (int j = 0; j < u->width; j++){
      if (u->rows[i][j] == '.'){
        // there is an available slot
        emptySpace = 0;
      }
    }
  }
  // if no empty slots it is a draw
  if (emptySpace == 1){
    return 'd';
  }
  // else no winners and there is a space to place token in
  return '.';
}

struct move read_in_move(board u){
  int col;
  int row;

  // get user's column
  printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
  while(scanf("%d", &col) != 1){
    int chr;
    printf("Invalid input...\n");
    printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
    do {
      chr = getchar();
    } while ((chr != EOF) && (chr != '\n'));
  }

  // get user's row
  printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
  while(scanf("%d", &row) != 1){
    int chr;
    printf("Invalid input...\n");
    printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
    do {
        chr = getchar();
    } while ((chr != EOF) && (chr != '\n'));
  }
  // create move struct
  struct move my_move;
  my_move.column = col;
  my_move.row = row;
  return my_move;
}

int is_valid_move(struct move m, board u){

  // check column is valid
  if(m.column > u->width+1 || m.column < 1 || abs(m.row) > u->height){
    printf("Not a valid move\n");
    return 0;
  }else{
    // find next available slot in selected column
    // iterate through rows 
    for (int i = 0; i < u->height; i++){
      if (u->rows[i][m.column-1] == '.'){
        // there is an available slot
        return 1;
      }
    }
    // if no space return false
    return 0;
  }
}

char is_winning_move(struct move m, board u){
  // create a temporary board structure
  struct board_structure *tempBoard;
  tempBoard = (struct board_structure *) malloc(sizeof(struct board_structure));

  // copy actual board properties to temporary board
  tempBoard->height = u->height;
  tempBoard->width= u->width;
  tempBoard->rows = malloc(u->height * sizeof(char *));
  tempBoard->rows = u->rows;

  // check move is valid
  if(is_valid_move(m, tempBoard)){
    // play move
    play_move(m,tempBoard);

    // check if move yields a winner
    char winner = current_winner(tempBoard);
    printf("winner: %c\n", winner);

    // if winner is . it could currently be a draw OR there is no winner yet
    if (winner == '.'){
      // find next available slot in selected column
      for (int i = 0; i < tempBoard->height; i++){
        for (int j = 0; j < tempBoard->width; j++){ 
          if (tempBoard->rows[i][j] == '.'){
            // there is an available slot
            return '.';
          }
        }
      }
      // if no space found we return that the move results in a draw
      return 'd';
    }else{
      // else there is a winner and we return the winner's token
      return winner;
    }

  }else{
    // not
    printf("Invalid move\n");
    // invalid move so no one wins/draws
    return '.';
  }
}

void play_move(struct move m, board u){
  // place token in col
  for (int i = u->height; i >= 0; i--){
    if (u->rows[i][m.column-1] == '.'){
      // there is an available slot, so we place next player's token there
      u->rows[i][m.column-1] = next_player(u);
      break;
    }
  }  
  // handle row twists
  if (m.row != 0){
    // if rightward twist
    if (m.row > 0){
      // temporarily store last column token
      char tempData  = u->rows[u->height-abs(m.row)][u->width-1];
      // shift each column to the right by one position
      for (int i= u->width-1; i >0; i--){
        u->rows[u->height-abs(m.row)][i] = u->rows[u->height-abs(m.row)][i-1]; 
      }
      // place the previous rightmost token in the first column
      u->rows[u->height-abs(m.row)][0] = tempData;
    }else{
    // if leftward twist
      // temporarily store first column token
      char tempData  = u->rows[u->height-abs(m.row)][0];
      // shift each column to the left by one position
      for (int i= 0; i < u->width-1; i++){
        u->rows[u->height-abs(m.row)][i] = u->rows[u->height-abs(m.row)][i+1]; 
      }
      // place the previous first column token in the rightmost column
      u->rows[u->height-abs(m.row)][u->width-1] = tempData;
    }

    // handle token gravity
    for(int i = 0; i < u->height; i++){
      for (int j = 0; j <u->width; j++){
        // if player token found
        if (u->rows[i][j]!= '.'){
          // check all tokens below are also not .
          for (int k = i; k< u->height; k++){
            if(u->rows[k][j] == '.'){
              // bubble . upwards k places by switching tokens
              for(int l = 0; l < k; l++){
                char tempA = u->rows[k-l][j];
                char tempB = u->rows[(k-l)-1][j];
                u->rows[k-l][j] = tempB; 
                u->rows[(k-l)-1][j] = tempA; 
              }
            }
          }

        }
      }
    }
  }
}

//You may put additional functions here if you wish.
