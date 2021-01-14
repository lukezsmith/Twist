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

void displayUsageInfo(){
  printf("This is the usage for sort \n"
       "Valid options are:\n"
       "    -r: reverse the sorting order\n"
       "    -o: specify output file for the sorted file to be saved to\n"
       "    -n: use numerical value to sort on\n"
       "    -h: display usage information the program\n");
}

int compareFunction (const void * a, const void * b) {
  // const char* aa = (const char*)a;
  // const char* bb = (const char*)b;

  //   int ca, cb;
  // do {
  //    ca = (unsigned char) *aa++;
  //    cb = (unsigned char) *bb++;
  //    ca = tolower(toupper(ca));
  //    cb = tolower(toupper(cb));
  //  } while (ca == cb && ca != '\0');
  //  return ca - cb;

  return strcoll(a, b);
}

int reverseCompareFunction (const void * a, const void * b) {
  // const char* aa = (const char*)a;
  // const char* bb = (const char*)b;

  //   int ca, cb;
  // do {
  //    ca = (unsigned char) *aa++;
  //    cb = (unsigned char) *bb++;
  //    ca = tolower(toupper(ca));
  //    cb = tolower(toupper(cb));
  //  } while (ca == cb && ca != '\0');
  //  return cb - ca;
  return strcoll(b, a);
}

int numericCompareFunction(const void * a, const void * b) {
  char* ptra;
  char* ptrb;
  const char* aa = (const char*)a;
  const char* bb = (const char*)b;

  long reta = strtol(aa, &ptra, 10);
  long retb = strtol(bb, &ptrb, 10);

  // return smallest of these
  return ( (int)reta - (int)retb );
}

int reverseNumericCompareFunction(const void * a, const void * b) {
  char* ptra;
  char* ptrb;
  const char* aa = (const char*)a;
  const char* bb = (const char*)b;

  long reta = strtol(aa, &ptra, 10);
  long retb = strtol(bb, &ptrb, 10);

  // return smallest of these
  return ( (int)retb - (int)reta );
} 

int main(int argc, char *argv[]){
  // bypass compilation warning
  (void) argc;
  char (*outputFilename) = "";
  char sortType = 'd';
  char outputType = 'c';
  int reverse = 0;
  FILE *fp;

  // set system locale
  setlocale(LC_ALL, "");


  // iterate through arguments

  while (*++argv){
    if((*argv)[0] == '-'){
      switch ((*argv)[1]){
        
        default: 
          printf("Unknown option -%c\n\n", (*argv)[1]);
          displayUsageInfo();
          return 1;
        
        case 'h': 
          // if file specified, process & sort using default
          // display usage info
          displayUsageInfo();
          return 1;

        case 'o': 
          outputType = 'f';
          // get filename 
          char* filename = (*++argv);
          printf("output filename: %s\n", filename);

          // set filename 
          outputFilename = filename;
          // outputFilename = "TETS";
          break;          
        
        case 'n':
          sortType = 'n'; 
          // process & sort using numerical compare function????
          break;          

        case 'r': 
          reverse = 1;
          // process & sort using reversed compare function
          break;
      }
    }else{
      printf("argc: %d\n", argc);
    }
  }
  // if no arguments passed print usage????
  if(argc == 1){
    displayUsageInfo();
    return 1;
  }
  // printf("n.o arguments: %d", argc);
  // if(argc < 2)


  // default (no arguments) implementation

  // check file 
  if ((fp = fopen(argv[-1], "r")) == NULL) {
    printf("Can't open file %s\n", *argv);
    // Program exits if file pointer returns NULL.
    return 1;
  }else{
    // process file
    process_file(fp, sortType, outputType, reverse, outputFilename);
    return 0;
    }
}

void process_file(FILE* fp, char sortType, char outputType, int reverse, char* outputFilename){
  int n = 0;
  // int maxLines = 40;
  int maxLines = 10;
  int maxChars = 512;

  // create pointer to char array of size 512
  char (*input)[maxChars] = NULL;

  // check that the allocation was possible
  if (!(input = malloc (maxLines * sizeof *input))) { 
    fprintf (stderr, "Error: Insufficient memory to store board.\n");
    exit(1);
  }

  // iterate through each line in infile
  while (n < maxLines && fgets (input[n], maxChars, fp)) {
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
    if (++n == maxLines) {
      // allocate more memory to temp pointer
      void *tmp = realloc (input, 2 * maxLines * sizeof *input);
      // check that the allocation was possible
      if (!tmp) {
        fprintf (stderr, "Error: Insufficient memory to store board.\n");
        exit(1);
      }
      // assign larger memory block to input
      input = tmp;
      // update new line limit
      maxLines *= 2;
    }
  }
  // close file
  if (fp != stdin){
    fclose (fp);
  }
  // free memory
  free (input);

  // choose sort type
  switch(sortType){
    // default comparison method
    default: 
      // check if reversed
      if (reverse == 0){
        qsort(input, n, sizeof(*input), compareFunction);
        break;
      }else{
        qsort(input, n, sizeof(*input), reverseCompareFunction);
        break; 
      }

    // numerical
    case 'n':
      if (reverse == 0){
        qsort(input, n, sizeof(*input), numericCompareFunction);
        break;
      }else{
        qsort(input, n, sizeof(*input), reverseNumericCompareFunction);
        break;  
      }
  }

  // if file output
  if(outputType == 'f'){
    // file output logic
    printf("writing......!");
    // int i = 0;
    FILE *f;
    // check file 
    if ((f = fopen(outputFilename, "wb")) == NULL) {
      printf("Can't open file %s\n", outputFilename);
    }
    for (int i = 0; i < n; i++) fprintf (f, "%s\n", input[i]);
    fclose(f);
  }else{
    /* print lines */
    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) printf ("%s\n", input[i]);
  }
}
