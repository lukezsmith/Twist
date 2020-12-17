//You can include any of headers defined in the C11 standard here. They are:
//assert.h, complex.h, ctype.h, errno.h, fenv.h, float.h, inttypes.h, iso646.h, limits.h, locale.h, math.h, setjmp.h, signal.h, stdalign.h, stdarg.h, stdatomic.h, stdbool.h, stddef.h, stdint.h, stdio.h, stdlib.h, stdnoreturn.h, string.h, tgmath.h, threads.h, time.h, uchar.h, wchar.h or wctype.h
//You may not include any other headers.
#include"connect4.h"
#include <stdlib.h>
#include <stdio.h>

struct board_structure {
  // row x column array?
  // int board[1][1];
  char **rows;
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
  for (int i = 0; i < initialSize; i++) printf ("%s\n", B->rows[i]);


  // return board address
  return B;

}

// void cleanup_board(board u){
// //You may put code here
// }

void read_in_file(FILE *infile, board u){
  // iterate through input file inserting each line to respective board row


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
