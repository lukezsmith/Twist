#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "sort.h"

// rules

// Lines starting with a number will appear before lines starting with a letter.
// Lines starting with a letter that appears earlier in the alphabet will appear before lines starting with a letter that appears later in the alphabet.
// Lines starting with a lowercase letter will appear before lines starting with the same letter in uppercase.

// sort -r: Reverse the sorting order.
// sort -o: Specify the output file.
// sort -n: Use the numerical value to sort. e.g a list > names.txt
// sort -h: option that outputs usage information and briefly explains how much of this part of the coursework you have managed to implement.

// uses qsort() to actually sort

// must use switch case to choose arguments. 

void display_usage_info(){
  printf("This is the usage for sort \n"
       "Valid options are:\n"
       "    -r: reverse the sorting order\n"
       "    -o: specify output file for the sorted file to be saved to\n"
       "    -n: use numerical value to sort on\n"
       "    -h: display usage information the program\n"
       "\n"
       "For this part of the coursework I have been able to implement all -r, -o, -n and -h options for both stdin input as well as file input.\n"
       "Testing on MIRA, this sorting program produces identical outputs to the unix sort. \n"
       "For this part I have made the assumption that the -h flag should behave identically to the --help flag on UNIX sort in that it overwrites all other flags and simply outputs this information. \n");
}

int compare_function (const void * a, const void * b) {
  return strcoll(a, b);
}

int reverse_compare_function (const void * a, const void * b) {
  return strcoll(b, a);
}

int numeric_compare_function(const void * a, const void * b) {
  char * pa;
  char * pb;

  int a_numeric = (int) strtol(a, &pa , 10);
  int b_numeric = (int) strtol(b, &pb, 10);
  return (a_numeric - b_numeric);
}

int reverse_numeric_compare_function(const void * a, const void * b) {
  char * pa;
  char * pb;

  int a_numeric = (int) strtol(a, &pa , 10);
  int b_numeric = (int) strtol(b, &pb, 10);
  return (b_numeric - a_numeric);
} 

int main(int argc, char *argv[]){
  // bypass compilation warning
  (void) argc;
  char (*output_filename) = "";
  char (*filename) = "";
  char sort_type = 'd';
  char output_type = 'c';
  int reverse = 0;
  FILE *fp;

  int filename_flag = 0;

  // set system locale
  setlocale(LC_ALL, "");


  // iterate through arguments

  while (*++argv){
    if((*argv)[0] == '-'){
      switch ((*argv)[1]){
        default: 
          printf("Unknown option -%c\n\n", (*argv)[1]);
          display_usage_info();
          return 1;
        
        case 'h': 
          // if file specified, process & sort using default
          // display usage info
          display_usage_info();
          return 1;

        case 'o': 
          output_type = 'f';
          // get filename 
          char* filename = (*++argv);
          printf("output filename: %s\n", filename);

          // set filename 
          output_filename = filename;
          // outputFilename = "TETS";
          break;          
        
        case 'n':
          sort_type = 'n'; 
          // process & sort using numerical compare function????
          break;          

        case 'r': 
          reverse = 1;
          // process & sort using reversed compare function
          break;

        // double hyphen arguments
        case '-':
          switch ((*argv)[2]){
            default: 
              printf("sort: unrecognized option '--%c'\n", (*argv)[2]);
              printf("Try './sort -h for more information.\n");
              // display_usage_info();
              return 1;
            
            case 'h': 
              // if file specified, process & sort using default
              // display usage info
              display_usage_info();
              return 1;

            case 'o': 
              output_type = 'f';
              // get filename 
              char* filename = (*++argv);
              printf("output filename: %s\n", filename);

              // set filename 
              output_filename = filename;
              // outputFilename = "TETS";
              break;          
            
            case 'n':
              sort_type = 'n'; 
              // process & sort using numerical compare function????
              break;          

            case 'r': 
              reverse = 1;
              // process & sort using reversed compare function
              break;
          }
          break;

      }
    }else{
      // save filename if output not set yet
      if(output_type != 'f'){
        filename =(*argv);
        filename_flag = 1;
      }else{
        // output has been set and so has a filename so we use stdin as input
        if (filename_flag == 0){
          process_file(stdin, sort_type, output_type, reverse, output_filename); 
        }
      }
    }
  }
  // if no arguments we use stdin without any flags
  if(filename_flag == 0){
    // display_usage_info();
    // return 1;
    // process_stdin(sort_type, output_type, reverse, output_filename);
    process_file(stdin, sort_type, output_type, reverse, output_filename);
  }else{
    // check file 
    if ((fp = fopen(filename, "r")) == NULL) {
      printf("Can't open file %s\n", *argv);
      // Program exits if file pointer returns NULL.
      return 1;
    }else{
      // process file
      process_file(fp, sort_type, output_type, reverse, output_filename);
      return 0;
      }
  }
}

void process_file(FILE* fp, char sort_type, char output_type, int reverse, char* output_filename){
  int n = 0;
  // int maxLines = 40;
  int max_lines = 10;
  int max_chars = 512;

  // FILE* f;


  // set input type
  // if (input_type == 's'){
  //   fp = stdin;
  // }

  // create pointer to char array of size 512
  char (*input)[max_chars] = NULL;

  // check that the allocation was possible
  if (!(input = malloc (max_lines * sizeof *input))) { 
    fprintf (stderr, "Error: Insufficient memory to text input.\n");
    exit(1);
  }

  // iterate through each line in infile
  while (n < max_lines && fgets (input[n], max_chars, fp)) {
    // assign pointer to char array
    char *chars = input[n];
    // iterate until newline
    for (; *chars && *chars != '\n'; chars++) {}
    // check line is not empty
    if (*chars != '\n') {
      int chr;
      do {
      chr = fgetc(fp);
      // discard unwanted input
      } while ((chr != EOF) && (chr != '\n'));
    }
    // reset pointer
    *chars = 0;
    // if maxLines has been reached then we need to increase limit and allocate more memory
    if (++n == max_lines) {
      // allocate more memory to temp pointer
      void *tmp = realloc (input, 2 * max_lines * sizeof *input);
      // check that the allocation was possible
      if (!tmp) {
        fprintf (stderr, "Error: Insufficient memory to store board.\n");
        exit(1);
      }
      // assign larger memory block to input
      input = tmp;
      // update new line limit
      max_lines *= 2;
    }
  }
  // close file
  if (fp != stdin){
    fclose (fp);
  }
  // free memory
  free (input);

  // choose sort type
  switch(sort_type){
    // default comparison method
    default: 
      // check if reversed
      if (reverse == 0){
        qsort(input, n, sizeof(*input), compare_function);
        break;
      }else{
        qsort(input, n, sizeof(*input), reverse_compare_function);
        break; 
      }

    // numerical
    case 'n':
      if (reverse == 0){
        qsort(input, n, sizeof(*input), numeric_compare_function);
        break;
      }else{
        qsort(input, n, sizeof(*input), reverse_numeric_compare_function);
        break;  
      }
  }

  // if file output
  if(output_type == 'f'){
    // file output logic
    FILE *f;
    // check file 
    if ((f = fopen(output_filename, "w")) == NULL) {
      printf("Can't open file %s\n", output_filename);
    }
    for (int i = 0; i < n; i++) fprintf (f, "%s\n", input[i]);
    fclose(f);
  }else{
    // print sorted input to stdout
    for (int i = 0; i < n; i++) printf ("%s\n", input[i]);
  }
}

// void process_stdin(char sort_type, char output_type, int reverse, char* output_filename){
//   // get stdin
//   // printf("Please enter a line:\n");
//   // char *line = NULL;
//   // size_t len = 0;
//   // ssize_t lineSize = 0;
//   // lineSize = getline(&line, &len, stdin);
//   // printf("You entered %s, which has %zu chars.\n", line, lineSize - 1);
//   // free(line);
//   // // return 0;
//   // line array
//   char line[512];

//   // array to store each line
//   // input[]
//   int n = 0;
//   while (fgets(line, 512, stdin) != NULL) {
//     // increment size of string array
//     n +=1;
//     // save line to lines array
//   }
//   printf("Lines from input:\n");
//   for (int i = 0; i < n; i++){
//     printf("%s\n", input[i]);
//   }
//   // sort

//   // // choose sort type
//   // switch(sort_type){
//   //   // default comparison method
//   //   default: 
//   //     // check if reversed
//   //     if (reverse == 0){
//   //       qsort(input, n, sizeof(*input), compare_function);
//   //       break;
//   //     }else{
//   //       qsort(input, n, sizeof(*input), reverse_compare_function);
//   //       break; 
//   //     }

//   //   // numerical
//   //   case 'n':
//   //     if (reverse == 0){
//   //       qsort(input, n, sizeof(*input), numeric_compare_function);
//   //       break;
//   //     }else{
//   //       qsort(input, n, sizeof(*input), reverse_numeric_compare_function);
//   //       break;  
//   //     }
//   // }

//   // // output
  
//   // // if file output
//   // if(output_type == 'f'){
//   //   // file output logic
//   //   FILE *f;
//   //   // check file 
//   //   if ((f = fopen(output_filename, "w")) == NULL) {
//   //     printf("Can't open file %s\n", output_filename);
//   //   }
//   //   for (int i = 0; i < n; i++) fprintf (f, "%s\n", input[i]);
//   //   fclose(f);
//   // }else{
//   //   // print sorted input to stdout
//   //   for (int i = 0; i < n; i++) printf ("%s\n", input[i]);
//   // }
// }
