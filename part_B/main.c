#include<stdio.h>
#include"connect4.h"
int main(){
  FILE *infile;
  FILE *outfile;

  board my_board=setup_board();

  infile=fopen("initial_board.txt","r");
  // infile=fopen("test_input1.txt","r");
  // infile=fopen("draw_board.txt","r");
  read_in_file(infile,my_board);
  fclose(infile);
  write_out_file(stdout,my_board);

  // struct move next_move = read_in_move(my_board);
  // char isWin = is_winning_move(next_move, my_board);
  // printf("winning move: %c\n", isWin);

  while(current_winner(my_board)=='.') {
    struct move next_move = read_in_move(my_board);
    if (is_valid_move(next_move,my_board)) {
      play_move(next_move,my_board);
      write_out_file(stdout,my_board); 
    }
  }

  outfile=fopen("final_board.txt","w");
  write_out_file(outfile,my_board);
  fclose(outfile);

  cleanup_board(my_board);
  return 0;
}
