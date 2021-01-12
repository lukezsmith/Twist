//You can include any of headers defined in the C11 standard here. They are:
//assert.h, complex.h, ctype.h, errno.h, fenv.h, float.h, inttypes.h, iso646.h, limits.h, locale.h, math.h, setjmp.h, signal.h, stdalign.h, stdarg.h, stdatomic.h, stdbool.h, stddef.h, stdint.h, stdio.h, stdlib.h, stdnoreturn.h, string.h, tgmath.h, threads.h, time.h, uchar.h, wchar.h or wctype.h
//You may not include any other headers.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include"connect4.h"

struct board_structure {
  // row x column array?
  // int board[1][1];
  // char **rows;
  char (*rows)[512];
  // char *rows[512];
  // n.o rows
  int height;
  // n.o columns
  int width;

  // unsigned char **board_ptr;
};

board setup_board(){
  // dynamically allocate a board structure
  int initialSize = 4;
  struct board_structure *B;
  B = (struct board_structure *) malloc(sizeof(struct board_structure));

  B->rows = malloc(initialSize * sizeof(char *));
  B->height = 4;
  B->width = 4;

  // populate board
  // for (int i = 0; i < initialSize; i++){
  //   B->rows[i] = "....";
  // } 
  
  // B = malloc(sizeof(board));
  // printf("Board structure: \n");
  // // printf("%s\n", B.rows[0]);
  // for (int i = 0; i < initialSize; i++) printf ("%s\n", B->rows[i]);


  // return board address
  return B;

}

void cleanup_board(board u){
  free(u->rows);
  free(u);
}

void read_in_file(FILE *infile, board u){
  int n = 0;
  int lineLength = 0;
  int maxl = 4;
  int maxc = 512;
   
  char (*lines)[maxc] = NULL; /* pointer to array of type char [MAXC] */

  if (!(lines = malloc (maxl * sizeof *lines))) { /* allocate MAXL arrays */
    fprintf (stderr, "error: virtual memory exhausted 'lines'.\n");
  }
  while (n < maxl && fgets (lines[n], maxc, infile)) { /* read each line */
      // get and check line length
      if (n == 0){
        lineLength = strlen(lines[n]) -1 ;
        // printf("line length: %d\n", lineLength);
        u->width = lineLength;

        if (lineLength <4 || lineLength > 512){
          // invalid file error handling
          printf("Invalid board size\n");
          return;
        }          
      }

      // check all lines are same length
      if ((int) strlen(lines[n])-1 != lineLength){
          printf("Curr line length: %d\n", (int) strlen(lines[n]-1));
          printf("Invalid board size\n");
          return;
      }
      char *p = lines[n];                  /* assign pointer */
      for (; *p && *p != '\n'; p++) {}     /* find 1st '\n'  */
      if (*p != '\n') {                   /* check line read */
            int c;  /* discard remainder of line with getchar  */
            while ((c = fgetc (infile)) != '\n' && c != EOF) {}
        }
      // *p = 0, n++;
      *p = 0;                              /* nul-termiante  */
      if (++n == maxl) { /* if limit reached, realloc lines  */
          void *tmp = realloc (lines, 2 * maxl * sizeof *lines);
          if (!tmp) {     /* validate realloc succeeded */
              fprintf (stderr, "error: realloc - virtual memory exhausted.\n");
              break;      /* on failure, exit with existing data */
          }
          lines = tmp;    /* assign reallocated block to lines */
          maxl *= 2;      /* update maxl to reflect new size */
      }                         /* nul-termiante  */
  }
  // if (infile != stdin) fclose (infile);   /* close file if not stdin */

  // set board height
  u->height = n;

  // set board rows
  // u->rows = lines;
  
  u->rows = malloc(maxl * sizeof *lines);
  memcpy(u->rows, lines, maxl * sizeof *lines);
  // printf("Read in print: \n");
  // for (int i = 0; i < u->height; i++){
  //   fprintf (stdout, "%d %s\n", u->height-i,  u->rows[i]);
  // }

  // board check
  // printf("board dim: %dx%d\n", u->width, u->height);
  // iterate by row x col rather than just row
  // for (int i = 0; i < n; i++) printf ("%c\n", u->rows[i][7]);
  
  free (lines);   /* free allocated memory */
  // printf("u-> height = %d\n", u->height);
  // printf("sizeof u->rows = %d\n", sizeof(u->rows));
}

void write_out_file(FILE *outfile, board u){
  // printf("First row (write_out_file): %s\n", u->rows[0]);
  // fflush(stdin); 
  // fflush(stdout); 
  // write board rows to the outfile
  // for (int i = 0; i < sizeof(u->rows); i++){
    // check string for four consecutive tokens
    // char *line = checkRow(u->rows[i]);
    // fprintf (outfile, "%s\n", line);
    // fprintf (outfile, "%s\n", u->rows[i]);

  // horizontalCheck 
  // for each symbol
  char symbols[] =  {'x', 'o'};
  // printf("board dims: %dx%d\n", u->width, u->height);
  // printf("board size: %d\n", sizeof(u->rows));
  // for (int i = 0; i < sizeof(u->rows); i++){
  //   printf ("%s\n", u->rows[i]);
  // }


  for (int k = 0; k < 2; k++){
    for (int j = 0; j<u->width-3 ; j++ ){
        for (int i = 0; i<u->height; i++){
            if (u->rows[i][j] == symbols[k] && u->rows[i][j+1] == symbols[k] && u->rows[i][j+2] == symbols[k] && u->rows[i][j+3] == symbols[k]){
                // capitalise o's
                u->rows[i][j] = toupper(symbols[k]);
                u->rows[i][j+1] = toupper(symbols[k]);
                u->rows[i][j+2] = toupper(symbols[k]);
                u->rows[i][j+3] = toupper(symbols[k]);
                  for (int i = 0; i < u->height; i++){
                    fprintf (outfile, "%s\n", u->rows[i]);
                }
                // fclose(outfile);
                return;
            }           
        }
    }
    // verticalCheck
    for (int i = 0; i<u->height-3; i++ ){
        for (int j = 0; j<u->width; j++){
            if (u->rows[i][j] == symbols[k] && u->rows[i+1][j] == symbols[k] && u->rows[i+2][j] == symbols[k] && u->rows[i+3][j] == symbols[k]){
                // capitalise o's
                u->rows[i][j] = toupper(symbols[k]);
                u->rows[i+1][j] = toupper(symbols[k]);
                u->rows[i+2][j] = toupper(symbols[k]);
                u->rows[i+3][j] = toupper(symbols[k]);
                for (int i = 0; i < u->height; i++){
                    fprintf (outfile, "%s\n", u->rows[i]);
                }
                // fclose(outfile);
                return;
            }           
        }
    }
    // ascendingDiagonalCheck 
    for (int i=3; i<u->height; i++){
        for (int j=0; j<u->width-3; j++){
            if (u->rows[i][j] == symbols[k] && u->rows[i-1][j+1] == symbols[k] && u->rows[i-2][j+2] == symbols[k] && u->rows[i-3][j+3] == symbols[k]){
                // capitalise o's
                u->rows[i][j] = toupper(symbols[k]);
                u->rows[i-1][j+1] = toupper(symbols[k]);
                u->rows[i-2][j+2] = toupper(symbols[k]);
                u->rows[i-3][j+3] = toupper(symbols[k]);
                for (int i = 0; i < u->height; i++){
                    fprintf (outfile, "%s\n", u->rows[i]);
                }
                // fclose(outfile);
                return;
            }
        }
    }
        // descendingDiagonalCheck
    for (int i=3; i<u->height; i++){
        for (int j=3; j< u->width; j++){
            if (u->rows[i][j] == symbols[k] && u->rows[i-1][j-1] == symbols[k] && u->rows[i-2][j-2] ==symbols[k] && u->rows[i-3][j-3] == symbols[k]){
                // capitalise o's
                u->rows[i][j] = toupper(symbols[k]);
                u->rows[i-1][j-1] = toupper(symbols[k]);
                u->rows[i-2][j-2] = toupper(symbols[k]);
                u->rows[i-3][j-3] = toupper(symbols[k]);
                for (int i = 0; i < u->height; i++){
                    fprintf (outfile, "%s\n", u->rows[i]);
                }
                // fclose(outfile);
                return;              
            }
        }
    }
  }
  // no winners
  // printf("\n");
  // printf("First line: %s\n", u->rows[0]);
  // fflush(stdout);
  for (int i = 0; i < u->height; i++){
    fprintf (outfile, "%s\n", u->rows[i]);
  }
  return;

}

char next_player(board u){
  // int x_count = 0;
  // int o_count = 0;

  // // count how many tokens each player has and then return the token with the least amount on the board
  // for (int i = 0; i < u->height; i++){
  //   for (int j = 0; j < u->width; j++){
  //     if (u->rows[i][j] == 'x'){
  //       // there is an available slot
  //       x_count +=1; 
  //     }
  //     if (u->rows[i][j] == 'o'){
  //       // there is an available slot
  //       o_count +=1; 
  //     }
  //   }
  // }
  // printf("x_count: %d\n", x_count);
  // printf("o_count: %d\n", o_count);
  // if(x_count < o_count){
  //   printf("x's turn to play!\n");
  //   return 'x';
  // }
  // else{
  //   printf("o's turn to play!\n");
  //   return 'o';
  // }
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
  
  // check no winners
  for (int k = 0; k < 2; k++){
    // horizontal Check
    for (int j = 0; j<u->width-3 ; j++ ){
        for (int i = 0; i<u->height; i++){
            if (u->rows[i][j] == symbols[k] && u->rows[i][j+1] == symbols[k] && u->rows[i][j+2] == symbols[k] && u->rows[i][j+3] == symbols[k]){
                // fclose(outfile);
                return symbols[k];
            }           
        }
    }
    // verticalCheck
    for (int i = 0; i<u->height-3; i++ ){
        for (int j = 0; j<u->width; j++){
            if (u->rows[i][j] == symbols[k] && u->rows[i+1][j] == symbols[k] && u->rows[i+2][j] == symbols[k] && u->rows[i+3][j] == symbols[k]){
              return symbols[k];
            }           
        }
    }
    // ascendingDiagonalCheck 
    for (int i=3; i<u->height; i++){
        for (int j=0; j<u->width-3; j++){
            if (u->rows[i][j] == symbols[k] && u->rows[i-1][j+1] == symbols[k] && u->rows[i-2][j+2] == symbols[k] && u->rows[i-3][j+3] == symbols[k]){
              return symbols[k];
            }
        }
    }
    // descendingDiagonalCheck
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
  if (emptySpace == 1){
    return 'd';
  }

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
    // fflush(stdout); 
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
  // printf("move: col %c, row %c\n", , row);
  struct move my_move;
  my_move.column = col;
  my_move.row = row;
  return my_move;


}

int is_valid_move(struct move m, board u){

  // int selectedCol; 
  // // check valid column
  // if(m.column < )
  // if(m.row != 0){
  //   selectedCol = abs(m.column + m.row);
  // }else{
  //   selectedCol = abs(m.column);
  // }

  // check column is valid
  if(m.column > u->width+1 || m.column < 1 || abs(m.row) > u->height){
    // printf("Not a valid move, selected column does not exist!\n");
    printf("Not a valid move\n");
    return 0;
  }else{
    // printf("is_valid else\n");
    // find next available slot in selected column

    // iterate through rows 
    for (int i = 0; i < u->height; i++){
      // printf("for loop: %d\n", i);
      // printf("board val: %c\n", u->rows[1][1]);
      // printf("board val: %s\n", u->rows[i]);
      if (u->rows[i][m.column-1] == '.'){
        // printf("is_valid returning 1\n");
        // there is an available slot
        return 1;
      }
    }
    // printf("is_valid returning 0\n");
    // if no space return false
    return 0;
  }
}

char is_winning_move(struct move m, board u){
  // copy board
  // board tempBoard;
  struct board_structure *tempBoard;
  tempBoard = (struct board_structure *) malloc(sizeof(struct board_structure));
  tempBoard->height = u->height;
  tempBoard->width= u->width;
  tempBoard->rows = malloc(u->height * sizeof(char *));
  tempBoard->rows = u->rows;

  // sanity check print
  // printf("tempBoard sanity check: \n");
  // for (int i = 0; i < tempBoard->height; i++){
  //   fprintf (stdout, "%d %s\n", tempBoard->height-i,  tempBoard->rows[i]);
  // }
  // printf("copied safely\n");
  // memcpy(tempBoard->rows, u->rows, sizeof *u->rows); 
  // memcpy(tempBoard, u, sizeof *u); 

  // check move is valid
  if(is_valid_move(m, tempBoard)){
    // printf("valid move\n");
    // play move
    play_move(m,tempBoard);


      // sanity check print
    // printf("tempBoard post-move sanity check: \n");
    // for (int i = 0; i < tempBoard->height; i++){
    //   fprintf (stdout, "%d %s\n", tempBoard->height-i,  tempBoard->rows[i]);
    // }

    // check if move yields a winner
    char winner = current_winner(tempBoard);
    printf("winner: %c\n", winner);

    // if winner is . it could currently be a draw OR there is no winner yet
    if (winner == '.'){
      // if no available spaces in the board
      // find next available slot in selected column

      // iterate through rows 
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
    printf("invalid move\n");
    // invalid move so no one wins/draws
    return '.';
  }
}

void play_move(struct move m, board u){
  // printf("First row (play_move): %s\n", u->rows[0]);
  // place token in col
  // iterate through rows (bottom up)
  for (int i = u->height; i >= 0; i--){
    if (u->rows[i][m.column-1] == '.'){
      // there is an available slot
      u->rows[i][m.column-1] = next_player(u);
      break;
    }
  }  
  if (m.row != 0){
    // twist row
    // rightward
    if (m.row > 0){
      char tempData  = u->rows[u->height-abs(m.row)][u->width-1];
      for (int i= u->width-1; i >0; i--){
        u->rows[u->height-abs(m.row)][i] = u->rows[u->height-abs(m.row)][i-1]; 
      }
      u->rows[u->height-abs(m.row)][0] = tempData;
    }else{
    // leftward
      char tempData  = u->rows[u->height-abs(m.row)][0];
      for (int i= 0; i < u->width-1; i++){
        u->rows[u->height-abs(m.row)][i] = u->rows[u->height-abs(m.row)][i+1]; 
      }
      u->rows[u->height-abs(m.row)][u->width-1] = tempData;
    }

    // handle gravity
    // iterate from bottom to top
    // if 
    for(int i = 0; i < u->height; i++){
      for (int j = 0; j <u->width; j++){
        if (u->rows[i][j]!= '.'){
          // printf("non-dot token found!\n");
          // check all tokens below are also not .
          for (int k = i; k< u->height; k++){
            if(u->rows[k][j] == '.'){
              // printf("hanging dot found!\n");
              // BUBBLE NOT WORKING NEED TO DEBUG IT!!!!!
              // bubble . upwards k places
              for(int l = 0; l < k; l++){
                // printf("bubbling up %d times!\n", l);
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
