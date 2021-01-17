#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

// function definitions
void process_file(FILE* fp, char sort_type, char output_type, int reverse, char* output_filename);
void write_to_file(char* filename, char* lines, int n);

// function that prints usage and brief overview to command line
void display_usage_info(){
  printf("This is the usage for sort \n"
       "Valid options are:\n"
       "    -r: reverse the sorting order\n"
       "    -o: specify output file for the sorted file to be saved to\n"
       "    -n: use numerical value to sort on\n"
       "    -h: display usage information the program\n"
       "\n"
       "For this part of the coursework I have been able to implement all -r, -o, -n and -h options for both stdin input as well as file input.\n"
       "Testing on MIRA, this sorting program produces identical outputs to the unix sort for all arguments aside from numerical sort when the input is a non-numeric string. \n"
       "For this part I have made the assumption that the -h flag should behave identically to the --help flag on UNIX sort in that it overwrites all other flags and simply outputs this information. \n");
}

// function that compares two strings (lines)
int compare_function (const void * a, const void * b) {
  return strcoll(a, b);
}

// function that compares two strings (lines) in reverse order
int reverse_compare_function (const void * a, const void * b) {
  return strcoll(b, a);
}

// function that compares two strings (lines) numerically
int numeric_compare_function(const void * a, const void * b) {
  char *pa;
  char *pb;

  // pa = (char*) a;
  // pb = (char*) b;

  // char ca = pa[0];
  // char cb = pb[0];
  // printf("first char a: %c\n", ca);


  int a_numeric = (int) strtol(a, &pa , 10);
  // printf("character: %s, integer val: %d\n", a, a_numeric);
  // printf("numeric: %d\n", a_numeric);
  int b_numeric = (int) strtol(b, &pb, 10);
  // printf("character: %s, integer val: %d\n", b, b_numeric);
  // char ca = (char *) *a[0];
  // char cb = (char *) *b[0];
  // const char* *ca = a;
  // const char* *cb = b;

  // int a_numeric = atoi(&ca);
  // printf("character: %c, integer val: %d\n", ca, a_numeric);
  // int b_numeric = atoi(&cb);
  // printf("character: %c, integer val: %d\n", cb,b_numeric);

  return (a_numeric - b_numeric);
}

// function that compares two strings (lines) numerically in reverse order
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
  // string for output filename
  char (*output_filename) = "";
  // string for input filename
  char (*filename) = "";
  // initialise sort type to use default compare function
  char sort_type = 'd';
  // initialise output to be stdout
  char output_type = 's';
  // initialise non-reverse compare 
  int reverse = 0;
  // initialise filename to be unread
  int filename_flag = 0;
  // file pointer for input file
  FILE *fp;

  // set system locale
  setlocale(LC_ALL, "");


  // iterate through arguments
  while (*++argv){
    // parse flag arguments
    if((*argv)[0] == '-'){
      switch ((*argv)[1]){
        // fallback option when flag not found
        default: 
          printf("Unknown option -%c\n\n", (*argv)[1]);
          display_usage_info();
          exit(1);
        
        // usage flag
        case 'h': 
          // display usage info
          display_usage_info();
          // terminate program
          exit(1);

        // output flag
        case 'o': 
          output_type = 'f';
          // get filename 
          char* filename = (*++argv);

          // set filename 
          output_filename = filename;
          break;          
        
        // numerical flag
        case 'n':
          // set numerical flag
          sort_type = 'n'; 
          break;          

        // reverse flag
        case 'r': 
          // set reverse flag
          reverse = 1;
          break;

        // double hyphen arguments
        case '-':
          switch ((*argv)[2]){
            // fallback option when flag not found
            default: 
              printf("sort: unrecognized option '--%c'\n", (*argv)[2]);
              printf("Try './sort -h for more information.\n");
              exit(1);
            
            // usage flag
            case 'h': 
              // display usage info
              display_usage_info();
              exit(1);

            // output flag
            case 'o': 
              output_type = 'f';
              // get filename 
              char* filename = (*++argv);

              // set filename 
              output_filename = filename;
              // outputFilename = "TETS";
              break;          
            
            // numerical flag
            case 'n':
              sort_type = 'n'; 
              // process & sort using numerical compare function????
              break;          

            // reverse flag
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
        // if output filename has already been set we check this argument to see if it is that
        if((*argv) != output_filename){
          filename =(*argv);
          filename_flag = 1;
        }
      }
    }
  }
  // if no arguments we use stdin
  if(filename_flag == 0){
    process_file(stdin, sort_type, output_type, reverse, output_filename);
    return 0;
  }else{
    // check file 
    if ((fp = fopen(filename, "r")) == NULL) {
      fprintf (stderr, "Error: Can't open file %s\n", filename);
      exit(1);
    }else{
      // process file
      process_file(fp, sort_type, output_type, reverse, output_filename);
      return 0;
      }
  }
}

// function that processes input, sorts and outputs results
void process_file(FILE* fp, char sort_type, char output_type, int reverse, char* output_filename){
  int n = 0;
  int max_lines = 10;
  int max_chars = 512;

  // create pointer to char array of size 512
  char (*input)[max_chars] = NULL;

  // check that the allocation was possible
  if (!(input = malloc (max_lines * sizeof *input))) { 
    fprintf (stderr, "Error: Insufficient memory to store text input.\n");
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
      // printf("Can't open file %s\n", output_filename);
      fprintf (stderr, "Error: Can't open file %s\n", output_filename);
      exit(1);
    }
    for (int i = 0; i < n; i++) fprintf (f, "%s\n", input[i]);
    fclose(f);
  }else{
    // print sorted input to stdout
    for (int i = 0; i < n; i++) printf ("%s\n", input[i]);
  }
  // free memory
  free (input);
}
