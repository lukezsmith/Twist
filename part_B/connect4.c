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

// void cleanup_board(board u){
// //You may put code here
// }

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
        printf("line length: %d\n", lineLength);
        u->width = lineLength;

        if (lineLength <4 || lineLength > 512){
          // invalid file error handling
          printf("Invalid board size\n");
          return;
        }          
      }

      // check all lines are same length
      if (strlen(lines[n])-1 != lineLength){
          printf("Curr line length: %d\n", strlen(lines[n]-1));
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
  if (infile != stdin) fclose (infile);   /* close file if not stdin */

  // set board height
  u->height = n;

  // set board rows
  u->rows = lines;

  // board check
  // printf("board dim: %dx%d\n", u->width, u->height);
  // iterate by row x col rather than just row
  // for (int i = 0; i < n; i++) printf ("%c\n", u->rows[i][7]);
  
  free (lines);   /* free allocated memory */
}

void write_out_file(FILE *outfile, board u){
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
                printf("HORIZONTAL WIN!!\n");
                // capitalise o's
                u->rows[i][j] = toupper(symbols[k]);
                u->rows[i][j+1] = toupper(symbols[k]);
                u->rows[i][j+2] = toupper(symbols[k]);
                u->rows[i][j+3] = toupper(symbols[k]);
                for (int i = 0; i < sizeof(u->rows); i++){
                    fprintf (outfile, "%s\n", u->rows[i]);
                }
                fclose(outfile);
                return;
            }           
        }
    }
    // verticalCheck
    for (int i = 0; i<u->height-3; i++ ){
        for (int j = 0; j<u->width; j++){
            if (u->rows[i][j] == symbols[k] && u->rows[i+1][j] == symbols[k] && u->rows[i+2][j] == symbols[k] && u->rows[i+3][j] == symbols[k]){
                printf("VERTICAL WIN!!\n");
                printf("i: %d, j: %d\n", i, j);
                printf("i: %d, j: %d\n", i+1, j);
                printf("i: %d, j: %d\n", i+2, j);
                printf("i: %d, j: %d\n", i+3, j);
                // capitalise o's
                u->rows[i][j] = toupper(symbols[k]);
                u->rows[i+1][j] = toupper(symbols[k]);
                u->rows[i+2][j] = toupper(symbols[k]);
                u->rows[i+3][j] = toupper(symbols[k]);
                for (int i = 0; i < sizeof(u->rows); i++){
                    fprintf (outfile, "%s\n", u->rows[i]);
                }
                fclose(outfile);
                return;
            }           
        }
    }
    // ascendingDiagonalCheck 
    for (int i=3; i<u->height; i++){
        for (int j=0; j<u->width-3; j++){
            if (u->rows[i][j] == symbols[k] && u->rows[i-1][j+1] == symbols[k] && u->rows[i-2][j+2] == symbols[k] && u->rows[i-3][j+3] == symbols[k]){
                printf("DIAGONAL (asc) WIN!!\n");
                // capitalise o's
                u->rows[i][j] = toupper(symbols[k]);
                u->rows[i-1][j+1] = toupper(symbols[k]);
                u->rows[i-2][j+2] = toupper(symbols[k]);
                u->rows[i-3][j+3] = toupper(symbols[k]);
                for (int i = 0; i < sizeof(u->rows); i++){
                    fprintf (outfile, "%s\n", u->rows[i]);
                }
                fclose(outfile);
                return;
            }
        }
    }
        // descendingDiagonalCheck
    for (int i=3; i<u->height; i++){
        for (int j=3; j< u->width; j++){
            if (u->rows[i][j] == symbols[k] && u->rows[i-1][j-1] == symbols[k] && u->rows[i-2][j-2] ==symbols[k] && u->rows[i-3][j-3] == symbols[k]){
                printf("DIAGONAL (desc) WIN!!\n");
                // capitalise o's
                u->rows[i][j] = toupper(symbols[k]);
                u->rows[i-1][j-1] = toupper(symbols[k]);
                u->rows[i-2][j-2] = toupper(symbols[k]);
                u->rows[i-3][j-3] = toupper(symbols[k]);
                for (int i = 0; i < sizeof(u->rows); i++){
                    fprintf (outfile, "%s\n", u->rows[i]);
                }
                fclose(outfile);
                return;              
            }
        }
    }
  }
  // no winners
  for (int i = 0; i < sizeof(u->rows); i++){
    fprintf (outfile, "%s\n", u->rows[i]);
  }
  return;

}

char next_player(board u){
  int x_count = 0;
  int o_count = 0;

  // count how many tokens each player has and then return the token with the least amount on the board
  for (int i = 0; i < u->height; i++){
    for (int j = 0; j < u->width; j++){
      if (u->rows[i][j] == 'x'){
        // there is an available slot
        x_count +=1; 
      }
      if (u->rows[i][j] == 'o'){
        // there is an available slot
        o_count +=1; 
      }
    }
  }
  if(x_count < o_count){
    return 'x';
  }
  else{
    return 'o';
  }
}

char current_winner(board u){
  int emptySpace = 1;
  char symbols[] =  {'x', 'o'};

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
  
  // check no winners
  for (int k = 0; k < 2; k++){
    for (int j = 0; j<u->width-3 ; j++ ){
        for (int i = 0; i<u->height; i++){
            if (u->rows[i][j] == symbols[k] && u->rows[i][j+1] == symbols[k] && u->rows[i][j+2] == symbols[k] && u->rows[i][j+3] == symbols[k]){
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

  return '.';
}

struct move read_in_move(board u){
  int col;
  int row;

  int validCol = 0;
  int validRow = 0;

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
  printf("input column, row: %d, %d\n", col, row);
  // create move struct and return it
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
  if(m.column > u->width || m.column < 0 || m.row > u->height || m.row < -1 || m.row > 1 ){
    // printf("Not a valid move, selected column does not exist!\n");
    printf("Not a valid move\n");
    return 0;
  }else{
    printf("is_valid else\n");
    // find next available slot in selected column

    // iterate through rows 
    for (int i = 0; i < u->height; i++){
      printf("for loop: %d\n", i);
      // printf("board val: %c\n", u->rows[1][1]);
      printf("board val: %s\n", u->rows[i]);
      if (u->rows[i][m.column] == '.'){
        printf("is_valid returning 1\n");
        // there is an available slot
        return 1;
      }
    }
    printf("is_valid returning 0\n");
    // if no space return false
    return 0;
  }
}

// char is_winning_move(struct move m, board u){
// //You may put code here
// }

void play_move(struct move m, board u){
  // place token in col
    // iterate through rows (bottom up)
    for (int i = u->height; i > 0; i--){
      if (u->rows[i][m.column] == '.'){
        // there is an available slot
        u->rows[i][m.column] = next_player(u);
        break;
      }
    }  
  // rotate row

}

//You may put additional functions here if you wish.
