#include<stdio.h>
#include"connect4.h"
int main(){
  FILE *infile;
  // FILE *outfile;

  board my_board=setup_board();

  // printf("Board structure: \n");
  // printf("%d\n", (board) my_board->height);
  // printf("%s\n", B.rows[0]);
  // for (int i = 0; i < 10; i++) printf ("%s\n", my_board.rows[i]);
  infile=fopen("diag_win.txt","r");
  read_in_file(infile,my_board);
  fclose(infile);

  write_out_file(stdout,my_board);
   
  // while(current_winner(my_board)=='.') {
  //   struct move next_move = read_in_move(my_board);
  //   if (is_valid_move(next_move,my_board)) {
  //   play_move(next_move,my_board);
  //   write_out_file(stdout,my_board);
  //   }
  // }

  // outfile=fopen("final_board.txt","w");
  // write_out_file(outfile,my_board);
  // fclose(outfile);

  // cleanup_board(my_board);
  return 0;
}
