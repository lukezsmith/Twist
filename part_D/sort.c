#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "sort.h"

enum { MAXL = 40, MAXC = 50 };

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
       "    --r: reverse the sorting order\n"
       "    --o: specify output file for the sorted file to be saved to\n"
       "    --n: use numerical value to sort on\n"
       "    --h: display usage information the program\n");
}

int cmpfunc (const void * a, const void * b) {
  const char* aa = (const char*)a;
  const char* bb = (const char*)b;

    int ca, cb;
  do {
     ca = (unsigned char) *aa++;
     cb = (unsigned char) *bb++;
     ca = tolower(toupper(ca));
     cb = tolower(toupper(cb));
   } while (ca == cb && ca != '\0');
   return ca - cb;
  // return strcasecmp(aa, bb);
  

}

int reversecmpfunc (const void * a, const void * b) {
  // const char* aa = (const char*)a;
  // const char* bb = (const char*)b;
  // return strcasecmp(bb, aa);
  const char* aa = (const char*)a;
  const char* bb = (const char*)b;

    int ca, cb;
  do {
     ca = (unsigned char) *aa++;
     cb = (unsigned char) *bb++;
     ca = tolower(toupper(ca));
     cb = tolower(toupper(cb));
   } while (ca == cb && ca != '\0');
   return cb - ca;
}

int numbercmpfunc(const void * a, const void * b) {
  char* ptra;
  char* ptrb;
  const char* aa = (const char*)a;
  const char* bb = (const char*)b;

  long reta = strtol(aa, &ptra, 10);
  long retb = strtol(bb, &ptrb, 10);

  // return smallest of these
  return ( (int)reta - (int)retb );
}

int reversenumbercmpfunc(const void * a, const void * b) {
  char* ptra;
  char* ptrb;
  const char* aa = (const char*)a;
  const char* bb = (const char*)b;

  long reta = strtol(aa, &ptra, 10);
  long retb = strtol(bb, &ptrb, 10);

  // return smallest of these
  return ( (int)retb - (int)reta );
} 


void writeToFile(char *filename, char *lines, int n){
  printf("writing......!");
  int i = 0;
  FILE *f;
  // check file 
  if ((f = fopen(filename, "wb")) == NULL) {
    printf("Can't open file %s\n", filename);
  }
  for (i = 0; i < n; i++) fprintf (f, "%c\n", lines[i]);
  fclose(f);
}
int main(int argc, char *argv[]){
  char (*lines)[MAXC] = NULL; 
  char (*outputFilename) = "";
  char sortType = 'd';
  char outputType = 'c';
  int reverse = 0;
  FILE *fp;

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
    }
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
    ProcessFileAlt(fp, argv[-1], sortType, outputType, reverse, outputFilename);
    return 0;
    }
}

void ProcessFileAlt(FILE* fp, char* filename, char sortType, char outputType, int reverse, char* outputFilename){
  char (*lines)[MAXC] = NULL; /* pointer to array of type char [MAXC] */
  
  int i, n = 0, maxl = MAXL;


  if (!(lines = malloc (MAXL * sizeof *lines))) { /* allocate MAXL arrays */
      fprintf (stderr, "error: virtual memory exhausted 'lines'.\n");
  }

  while (n < MAXL && fgets (lines[n], MAXC, fp)) { /* read each line */
      char *p = lines[n];                  /* assign pointer */
      for (; *p && *p != '\n'; p++) {}     /* find 1st '\n'  */
      if (*p != '\n') {                   /* check line read */
            int c;  /* discard remainder of line with getchar  */
            while ((c = fgetc (fp)) != '\n' && c != EOF) {}
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
  if (fp != stdin) fclose (fp);   /* close file if not stdin */

  /* print lines */
  // printf("Original array: \n");
  // for (i = 0; i < n; i++) printf ("%s\n", lines[i]);

  free (lines);   /* free allocated memory */


  // choose sort type
  switch(sortType){
    // default comparison method
    default: 
      // check if reversed
      if (reverse == 0){
        qsort(lines, n, sizeof(*lines), cmpfunc);
        break;
      }else{
        qsort(lines, n, sizeof(*lines), reversecmpfunc);
        break; 
      }

    // numerical
    case 'n':
      if (reverse == 0){
        qsort(lines, n, sizeof(*lines), numbercmpfunc);
        break;
      }else{
        qsort(lines, n, sizeof(*lines), reversenumbercmpfunc);
        break;  
      }
  }

  // if file output
  if(outputType == 'f'){
    // file output logic
    // writeToFile(outputFilename, lines, n);
    printf("writing......!");
    // int i = 0;
    FILE *f;
    // check file 
    if ((f = fopen(outputFilename, "wb")) == NULL) {
      printf("Can't open file %s\n", outputFilename);
    }
    for (i = 0; i < n; i++) fprintf (f, "%s\n", lines[i]);
    fclose(f);
  }else{
    /* print lines */
    printf("Sorted array: \n");
    for (i = 0; i < n; i++) printf ("%s\n", lines[i]);
  }
}