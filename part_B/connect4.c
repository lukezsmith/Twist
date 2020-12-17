//You can include any of headers defined in the C11 standard here. They are:
//assert.h, complex.h, ctype.h, errno.h, fenv.h, float.h, inttypes.h, iso646.h, limits.h, locale.h, math.h, setjmp.h, signal.h, stdalign.h, stdarg.h, stdatomic.h, stdbool.h, stddef.h, stdint.h, stdio.h, stdlib.h, stdnoreturn.h, string.h, tgmath.h, threads.h, time.h, uchar.h, wchar.h or wctype.h
//You may not include any other headers.
#include"connect4.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
  printf("board dim: %dx%d\n", u->width, u->height);
  for (int i = 0; i < n; i++) printf ("%s\n", u->rows[i]);
  
  free (lines);   /* free allocated memory */
}

// void write_out_file(FILE *outfile, board u){
// //You may put code here
// }

// char next_player(board u){
// //You may put code here
// }

// char current_winner(board u){
// //You may put code here
// }

// struct move read_in_move(board u){
// //You may put code here
//   printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
// //You may put code here
//   printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
// //You may put code here
// }

// int is_valid_move(struct move m, board u){
// //You may put code here
// }

// char is_winning_move(struct move m, board u){
// //You may put code here
// }

// void play_move(struct move m, board u){
// //You may put code here
// }

//You may put additional functions here if you wish.
