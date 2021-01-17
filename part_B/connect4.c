//You can include any of headers defined in the C11 standard here. They are:
//assert.h, complex.h, ctype.h, errno.h, fenv.h, float.h, inttypes.h, iso646.h, limits.h, locale.h, math.h, setjmp.h, signal.h, stdalign.h, stdarg.h, stdatomic.h, stdbool.h, stddef.h, stdint.h, stdio.h, stdlib.h, stdnoreturn.h, string.h, tgmath.h, threads.h, time.h, uchar.h, wchar.h or wctype.h
//You may not include any other headers.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include"connect4.h"

// structure that stores the board
struct board_structure {
  char (*rows)[512];
  int height;
  int width;
};

// function that initialises and allocates memory to board 
board setup_board(){
  // initial row and column size in order to play connect4
  int max_size = 512;

  // allocate memory for board struct
  struct board_structure *B;
  B = (struct board_structure *) malloc(sizeof(struct board_structure));

  // dynamically allocate memory for dynamic amount of rows
  if (!(B->rows = malloc (max_size * sizeof (char *)))) {
    // not enough memory to assign
    fprintf (stderr, "Error: Insufficient memory to store board.\n");
    free(B);
    exit(1);
  }

  // set board height and width initially to 4
  B->height = 4;
  B->width = 4;

  // return board address
  return B;

}

// function that cleans the board and frees allocated board memory
void cleanup_board(board u){
  // free dynamically allocated board row memory
  free(u->rows);
  // free dynamically allocated board struct memory
  free(u);
}

// function that reads the input file and builds the board
void read_in_file(FILE *infile, board u){
  // variable that counts number of lines in the input file
  int n = 0;
  // variable that counts the number of characters in each line of the input file
  int line_length = 0;
  // initial maximum number of rows (lines) to the board
  int max_height = 4;
  // maximum number of characters to handle in each row of the board
  int max_width = 515;
   
  // create pointer to char array of size 512
  char (*rows)[max_width] = NULL;

  // check input file is valid
  if (infile == NULL) {
    fprintf(stderr, "Error: Can't open input file.\n");
    cleanup_board(u);
    exit(1);
  }
 
  // iterate through each line in infile
  while (n< max_height && fgets (u->rows[n], max_width, infile)) {
    // if first line
    if (n == 0){
      // set linelength for number of characters in first line
      line_length = strlen(u->rows[n]) -1 ;
      u->width = line_length;

      // incorrect board dimensions
      if (line_length <4 || line_length > 512){
        fprintf (stderr, "Error: Invalid board size.\n");
        cleanup_board(u);
        fclose(infile);
        exit(1);
      }          
    }

    // check all lines are same length
    if ((int) strlen(u->rows[n])-1 != line_length){
        fprintf (stderr, "Error: Invalid board size.\n");
        cleanup_board(u);
        fclose(infile);
        exit(1);
    }
    // assign pointer to char array
    char *chars = u->rows[n];

    // check characters are all valid
    for (int i = 0; i < line_length; i++){
      if (chars[i] != '.' && chars[i] != 'x' && chars[i] != 'o' ){
        fprintf (stderr, "Error: Invalid token in board: '%c'.\n", chars[i]);
        cleanup_board(u);
        fclose(infile);
        exit(1);
      }
    }
    // iterate until newline
    for (; *chars && *chars != '\n'; chars++) {
    }
    // check line is not empty
    if (*chars != '\n') {
      int chr;
      do {
      chr = fgetc(infile);
      // discard unwanted input
      } while ((chr != EOF) && (chr != '\n'));
    }
    // reset pointer
    *chars = 0;
    // if max_height has been reached then we need to increase limit and allocate more memory
    if (++n == max_height) {
      // allocate more memory to temp pointer
      void *tmp = realloc (u->rows, 2 * max_height * sizeof *rows);
      // check that the allocation was possible
      if (!tmp) {
        fprintf (stderr, "Error: Insufficient memory to store board.\n");
        cleanup_board(u);
        free(tmp);
        fclose(infile);
        exit(1);
      }
      // assign larger memory block to LINES (RENAME????)
      u->rows = tmp;
      // update new height limit
      max_height *= 2;
    }
  }
  // set board height
  u->height = n;

  // we now check to see if the input file's tokens follow gravity correctly
  // iterate through board tokens
  for(int i = 0; i < u->height; i++){
    for (int j = 0; j <u->width; j++){
      // if player token found
      if (u->rows[i][j]!= '.'){
        // check all tokens below are also not .
        for (int k = i; k< u->height; k++){
          if(u->rows[k][j] == '.'){
            fprintf (stderr, "Error: Invalid board. Gravity not applied to input file.\n");
            cleanup_board(u);
            fclose(infile);
            exit(1); 
          }
        }
      }
    }
  }
}

// function that writes the current state of the board to specified file pointer
void write_out_file(FILE *outfile, board u){
  // array that holds each player's token
  char symbols[] =  {'x', 'o'};

  // flag to register a winning line for each player
  int x_win = 0;
  int o_win = 0;

  // check for winner
  for (int k = 0; k < 2; k++){
    //horizontal win check
    
    // iterate over the board
    for (int j = 0; j<u->width ; j++ ){
      for (int i = 0; i<u->height; i++){
        // check if each respective board position is the same: i.e four in a row
        if (u->rows[i][j] == symbols[k] && u->rows[i][(j+1)% u->width] == symbols[k] && u->rows[i][(j+2)% u->width] == symbols[k] && u->rows[i][(j+3)% u->width] == symbols[k]){
          // if the token is x and x hasn't already won we flag the win and capitalise the tokens to indicate a win
          if (k == 0 && x_win == 0){
            x_win = 1;
            // capitalise symbols
            u->rows[i][j] = toupper(symbols[k]);
            u->rows[i][(j+1)% u->width] = toupper(symbols[k]);
            u->rows[i][(j+2)% u->width] = toupper(symbols[k]);
            u->rows[i][(j+3)% u->width] = toupper(symbols[k]);
          }

          // if the token is o and o hasn't already won we flag the win and capitalise the tokens to indicate a win
          if (k == 1 && o_win == 0){
            o_win = 1;
            // capitalise symbols
            u->rows[i][j] = toupper(symbols[k]);
            u->rows[i][(j+1)% u->width] = toupper(symbols[k]);
            u->rows[i][(j+2)% u->width] = toupper(symbols[k]);
            u->rows[i][(j+3)% u->width] = toupper(symbols[k]);
          }
        }           
      }
    }
    // vertical win check
        
    // iterate over the board
    for (int i = 0; i<u->height-3; i++ ){
      for (int j = 0; j<u->width; j++){
        // check if each respective board position is the same: i.e four in a row
        if (u->rows[i][j] == symbols[k] && u->rows[i+1][j] == symbols[k] && u->rows[i+2][j] == symbols[k] && u->rows[i+3][j] == symbols[k]){
          // if the token is x and x hasn't already won we flag the win and capitalise the tokens to indicate a win
          if (k == 0 && x_win == 0){
            x_win = 1;
            // capitalise symbols
            u->rows[i][j] = toupper(symbols[k]);
            u->rows[i+1][j] = toupper(symbols[k]);
            u->rows[i+2][j] = toupper(symbols[k]);
            u->rows[i+3][j] = toupper(symbols[k]);
          }

          // if the token is o and o hasn't already won we flag the win and capitalise the tokens to indicate a win
          if (k == 1 && o_win == 0){
            o_win = 1;
            // capitalise symbols
            u->rows[i][j] = toupper(symbols[k]);
            u->rows[i+1][j] = toupper(symbols[k]);
            u->rows[i+2][j] = toupper(symbols[k]);
            u->rows[i+3][j] = toupper(symbols[k]);
          }
        }           
      }
    }
    // diagonal (ascending) win check
            
    // iterate over the board
    for (int i=3; i<u->height; i++){
      for (int j=0; j<u->width; j++){
        // check if each respective board position is the same: i.e four in a row
        if (u->rows[i][j] == symbols[k] && u->rows[i-1][(j+1) % u->width] == symbols[k] && u->rows[i-2][(j+2) % u->width] == symbols[k] && u->rows[i-3][(j+3) % u->width] == symbols[k]){
          // if the token is x and x hasn't already won we flag the win and capitalise the tokens to indicate a win
          if (k == 0 && x_win == 0){
            x_win = 1;
            // capitalise symbols
            u->rows[i][j] = toupper(symbols[k]);
            u->rows[i-1][(j+1) % u->width] = toupper(symbols[k]);
            u->rows[i-2][(j+2) % u->width] = toupper(symbols[k]);
            u->rows[i-3][(j+3) % u->width] = toupper(symbols[k]);
          }

          // if the token is o and o hasn't already won we flag the win and capitalise the tokens to indicate a win
          if (k == 1 && o_win == 0){
            o_win = 1;
            // capitalise symbols
            u->rows[i][j] = toupper(symbols[k]);
            u->rows[i-1][(j+1) % u->width] = toupper(symbols[k]);
            u->rows[i-2][(j+2) % u->width] = toupper(symbols[k]);
            u->rows[i-3][(j+3) % u->width] = toupper(symbols[k]);
          }
        }
      }
    }
    // diagonal (descending) win check
                
    // iterate over the board
    for (int i=3; i<u->height; i++){
      for (int j=0; j< u->width; j++){
        // check if each respective board position is the same: i.e four in a row
        if (u->rows[i][j] == symbols[k] && u->rows[i-1][(unsigned int) (j-1) % u->width] == symbols[k] &&  u->rows[i-2][(unsigned int) (j-2) % u->width] ==symbols[k] && u->rows[i-3][(unsigned int) (j-3) % u->width] == symbols[k]){
          // if the token is x and x hasn't already won we flag the win and capitalise the tokens to indicate a win
          if (k == 0 && x_win == 0){
            x_win = 1;
            // capitalise symbols
            u->rows[i][j] = toupper(symbols[k]);
            u->rows[i-1][(unsigned int) (j-1)% u->width] = toupper(symbols[k]);
            u->rows[i-2][(unsigned int) (j-2) % u->width] = toupper(symbols[k]);
            u->rows[i-3][(unsigned int) (j-3) % u->width] = toupper(symbols[k]);
          }

          // if the token is o and o hasn't already won we flag the win and capitalise the tokens to indicate a win
          if (k == 1 && o_win == 0){
            o_win = 1;
            // capitalise symbols
            u->rows[i][j] = toupper(symbols[k]);
            u->rows[i-1][(unsigned int)(j-1)% u->width] = toupper(symbols[k]);
            u->rows[i-2][(unsigned int)(j-2)% u->width] = toupper(symbols[k]);
            u->rows[i-3][(unsigned int)(j-3)% u->width] = toupper(symbols[k]);
          }
        }
      }
    }
  }

  // print output to file pointer
  for (int i = 0; i < u->height; i++){
    fprintf (outfile, "%s\n", u->rows[i]);
  }
  return;

}

// function that returns the token of the next player
char next_player(board u){
  // variable that counts the number of tokens in the board
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

// function that returns the current winner of the board
char current_winner(board u){
  // variable that indicates if there is a free space on the board or not
  int empty_space = 1;
  // array containing the winning player's tokens
  char symbols[] =  {'x', 'o'};
  // flag to register a winning line for each player
  int x_win = 0;
  int o_win = 0;
  
  // check for winner
  for (int k = 0; k < 2; k++){

    //horizontal win check

    // iterate over the board
    for (int j = 0; j<u->width; j++ ){
      for (int i = 0; i<u->height; i++){
        // check if each respective board position is the same: i.e four in a row
        if (tolower(u->rows[i][j]) == symbols[k] && tolower(u->rows[i][(j+1) % u->width]) == symbols[k] && tolower(u->rows[i][(j+2)% u->width]) == symbols[k] && tolower(u->rows[i][(j+3) % u->width]) == symbols[k]){
          // if x win 
          if (k == 0){
            x_win = 1;
          }else{
            // o win
            o_win = 1;
          }
        }           
      }
    }
    // vertical win check

    // iterate over the board
    for (int i = 0; i<u->height-3; i++ ){
      for (int j = 0; j<u->width; j++){
        // check if each respective board position is the same: i.e four in a row
        if (tolower(u->rows[i][j]) == symbols[k] && tolower(u->rows[i+1][j]) == symbols[k] && tolower(u->rows[i+2][j]) == symbols[k] && tolower(u->rows[i+3][j]) == symbols[k]){
          // if x win 
          if (k == 0){
            x_win = 1;
          }else{
            // o win
            o_win = 1;
          }
        }           
      }
    }
    // diagonal (ascending) win check 

    // iterate over the board
    for (int i=3; i<u->height; i++){
      for (int j=0; j<u->width; j++){
        // check if each respective board position is the same: i.e four in a row
        if (tolower(u->rows[i][j]) == symbols[k] && tolower(u->rows[i-1][(j+1)% u->width]) == symbols[k] && tolower(u->rows[i-2][(j+2)% u->width]) == symbols[k] && tolower(u->rows[i-3][(j+3)% u->width]) == symbols[k]){
          // if x win 
          if (k == 0){
            x_win = 1;
          }else{
            // o win
            o_win = 1;
          }
        }
      }
    }
    // diagonal (descending) win check

    // iterate over the board
    for (int i=3; i<u->height; i++){
      for (int j=0; j< u->width; j++){
        // check if each respective board position is the same: i.e four in a row
        if (tolower(u->rows[i][j]) == symbols[k] && tolower(u->rows[i-1][(unsigned int)(j-1)% u->width]) == symbols[k] && tolower(u->rows[i-2][(unsigned int)(j-2)% u->width]) ==symbols[k] && tolower(u->rows[i-3][(unsigned int)(j-3)% u->width]) == symbols[k]){
          // if x win 
          if (k == 0){
            x_win = 1;
          }else{
            // o win
            o_win = 1;
          }
        }
      }
    }
  }

  // check for winners and return the winner's character
  if(x_win == 1 && o_win == 0){
    return 'x';
  }
  if(x_win == 0 && o_win == 1){
    return 'o';
  }
  if(x_win == 1 && o_win == 1){
    return 'd';
  }

  // check board is not full
  for (int i = 0; i < u->height; i++){
    for (int j = 0; j < u->width; j++){
      if (u->rows[i][j] == '.'){
        // there is an available slot
        empty_space = 0;
      }
    }
  }
  // if no empty slots it is a draw
  if (empty_space == 1){
    return 'd';
  }
  // else no winners and there is a space to place token in
  return '.';
}

// function that reads in the next player's move
struct move read_in_move(board u){
  // function that stores the move's row and column numbers
  int col;
  int row;

  // get user's column
  printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
  // checks that the user input is numeric
  // while(scanf("%d", &col) != 1){
  //   // if not numeric we display the error message and re-prompt
  //   int chr;
  //   fprintf(stderr, "Error: Invalid input, please enter a number.\n");
  //   printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
  //   do {
  //     chr = getchar();
  //   } while ((chr != EOF) && (chr != '\n'));
  // }
  if(scanf("%d", &col) !=1){
    fprintf(stderr, "Error: Invalid input, column should be a number.\n");
    exit(1);
  }

  // get user's row
  printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
  // checks that the user input is numeric
  // while(scanf("%d", &row) != 1){
  //   // if not numeric we display the error message and re-prompt
  //   int chr;
  //   fprintf(stderr, "Error: Invalid input, please enter a number.\n");
  //   printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
  //   do {
  //       chr = getchar();
  //   } while ((chr != EOF) && (chr != '\n'));
  // }
  if(scanf("%d", &row) !=1){
    fprintf(stderr, "Error: Invalid input, row should be a number.\n");
    exit(1);
  }
  // create move struct
  struct move my_move;
  my_move.column = col;
  my_move.row = row;
  return my_move;
}

// function that checks if the user's move is valid or not
int is_valid_move(struct move m, board u){

  // check column is valid
  if(m.column > u->width+1 || m.column < 1 || abs(m.row) > u->height){
    fprintf(stderr, "Error: Not a valid move.\n");
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
    fprintf(stderr, "Error: Not a valid move.\n");
    return 0;
  }
}

// function that checks if the specified move will result in a win, draw or otherwise
char is_winning_move(struct move m, board u){
  // create a temporary board structure
  struct board_structure *temp_board;
  temp_board = (struct board_structure *) malloc(sizeof(struct board_structure));

  // copy actual board properties to temporary board
  temp_board->height = u->height;
  temp_board->width= u->width;
  temp_board->rows = malloc(sizeof(u->rows));
  for (int i = 0; i < u->height; i++){
    for(int j = 0; j <u->width;j++){
      temp_board->rows[i][j] = u->rows[i][j];
    }
  }

  // check move is valid
  if(is_valid_move(m, temp_board)){
    // play move
    play_move(m,temp_board);
    printf("temp_board: %dx%d \n", temp_board->height, temp_board->width);
    write_out_file(stdout, temp_board);

    // check if move yields a winner
    char winner = current_winner(temp_board);
    printf("winner: %c\n", winner);

    // if winner is . it could currently be a draw OR there is no winner yet
    if (winner == '.'){
      // find next available slot in selected column
      for (int i = 0; i < temp_board->height; i++){
        for (int j = 0; j < temp_board->width; j++){ 
          if (temp_board->rows[i][j] == '.'){
            // there is an available slot
            cleanup_board(temp_board);
            return '.';
          }
        }
      }
      // if no space found we return that the move results in a draw
      cleanup_board(temp_board);
      return 'd';
    }else{
      // else there is a winner and we return the winner's token
      cleanup_board(temp_board);
      return winner;
    }

  }else{
    // invalid move so no one wins/draws
    cleanup_board(temp_board);
    return '.';
  }
}

// function that plays the user's move 
void play_move(struct move m, board u){
  // place token in col
  for (int i = u->height-1; i >= 0; i--){
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
      char temp_data  = u->rows[u->height-abs(m.row)][u->width-1];
      // shift each column to the right by one position
      for (int i= u->width-1; i >0; i--){
        u->rows[u->height-abs(m.row)][i] = u->rows[u->height-abs(m.row)][i-1]; 
      }
      // place the previous rightmost token in the first column
      u->rows[u->height-abs(m.row)][0] = temp_data;
    }else{
      // if leftward twist
      // temporarily store first column token
      char temp_data  = u->rows[u->height-abs(m.row)][0];
      // shift each column to the left by one position
      for (int i= 0; i < u->width-1; i++){
        u->rows[u->height-abs(m.row)][i] = u->rows[u->height-abs(m.row)][i+1]; 
      }
      // place the previous first column token in the rightmost column
      u->rows[u->height-abs(m.row)][u->width-1] = temp_data;
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
                char temp_a = u->rows[k-l][j];
                char temp_b = u->rows[(k-l)-1][j];
                u->rows[k-l][j] = temp_b; 
                u->rows[(k-l)-1][j] = temp_a; 
              }
            }
          }

        }
      }
    }
  }
}

//You may put additional functions here if you wish.
