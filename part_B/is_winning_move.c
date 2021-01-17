#include<stdio.h>
#include"connect4.h"
int main(){
  FILE *infile;
  // *outfile;

  board my_board=setup_board();
  infile=fopen("./test_board_files/one_move_win.txt","r");
  read_in_file(infile,my_board);
  fclose(infile);

  write_out_file(stdout,my_board);
  struct move next_move = read_in_move(my_board);
  char win = is_winning_move(next_move, my_board);
  printf("Is winning move?: %c\n", win);
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

  cleanup_board(my_board);
  return 0;
}
