#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "sort.h"

enum { MAXL = 40, MAXC = 50 };

// enum { 
//   A = 130, 
//   B = 131,
//   C = 
// }


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


// struct line {
//   char contents[255];
// };

int cmpfunc (const void * a, const void * b) {
  // const char * pa = (const char *) a;
  // const char * pb = (const char *) b;
  // return ( (int)pa[0] - (int)pb[0] );
  const char* aa = (const char*)a;
  const char* bb = (const char*)b;
  return strcasecmp(aa, bb);
}

int reversecmpfunc (const void * a, const void * b) {
  const char* aa = (const char*)a;
  const char* bb = (const char*)b;
  return strcasecmp(bb, aa);

}



int main(int argc, char *argv[]){
  char (*lines)[MAXC] = NULL; 
  char sortType = 'd';
  char outputType = 'c';
  FILE *fp;

  // iterate through arguments

  while (*++argv){
    if((*argv)[0] == '-'){
      switch ((*argv)[1]){
        
        default: 
          printf("Unknown option-%c\n\n", (*argv)[1]);
          return 1;
        
        case 'h': 
          printf("\noption h is found\n\n");
          // if file specified, process & sort using default
          // display usage info
          // displayUsageInfo();

          break;

        case 'o': 
          outputType = 'f';
          printf("\noption o is found\n\n");
          // process & sort

          // write to specified file (if possible, else create new file and output to there????)
          break;          
        
        case 'n':
          sortType = 'n'; 
          printf("\noption n is found\n\n");
          // process & sort using numerical compare function????
          break;          

        case 'r': 
          sortType = 'r';
          printf("\noption r is found\n\n");
          // process & sort using reversed compare function
          break;
      }
    }
  }

  // default (no arguments) implementation

  // check file 
  if ((fp = fopen(argv[-1], "r")) == NULL) {
    printf("Can't open file %s\n", *argv);
    // Program exits if file pointer returns NULL.
    return 1;
  }else{
    // process file
    ProcessFileAlt(fp, argv[-1], sortType, outputType);
    return 0;
    }
}
void ProcessFileAlt(FILE* fp, char* filename, char sortType, char outputType){
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
  printf("Original array: \n");
  for (i = 0; i < n; i++) printf (" line[%2d] : '%s'\n", i + 1, lines[i]);

  free (lines);   /* free allocated memory */


  // choose sort type
  switch(sortType){
    // default comparison method
    default: 
      qsort(lines, n, sizeof(*lines), cmpfunc);
      break;

    // numerical
    case 'n':
      break;

    // reverse
    case 'r':
      qsort(lines, n, sizeof(char) * MAXC, reversecmpfunc);
      break;
  }

  // if file output
  if(outputType == 'f'){
    // file output logic
  }else{
    /* print lines */
    printf("Sorted array: \n");
    for (i = 0; i < n; i++) printf (" line[%2d] : '%s'\n", i + 1, lines[i]);
  }




}
void ProcessFile(FILE* fp, char* filename){

  int freeSpace = 0;

  int count = 0;
  char c;
  // char d;  
  

  // int bufferLength = 256;
  char buffer[256];

  int n =0;
  fp = fopen (filename , "r");

  // // count file lines
  // while(!feof(fp))
  // {
  //   d = fgetc(fp);
  //   if(d == '\n')
  //   {
  //     count++;
  //   }
  // }
  // while (d != EOF);
  // if(d != '\n' && count != 0)
  //   count++;

  // printf("The file has %d lines\n", count); 
  printf("test");

  // move file pointer back to beginning of the file
  rewind(fp);
  // fclose (fp);

  // fp = fopen (filename , "r");


  // define line character arrays
  char *lines[1000];

  int i = 0;

  while(fgets(buffer, sizeof(buffer), fp)) {
    i++;
    printf("i: %d", i);
    printf("%s\n", buffer);
    strcpy(lines[freeSpace], buffer);
    freeSpace++;
  }
  

  fclose (fp);

  printf("test");

  // test iteration over characters arr
  // for (int j = 0; j< sizeof(lines); i++){
  //   printf("%s \n", lines[j]);
  // }

  // // copy character array
  // for (int i = 0; i< count; i++){
  //   // printf("%c \n", characters[i]);
  //   copied[i] = characters[i];
  // }

  // printf("original -> copied \n");
  
  // // copy array
  // for(int loop = 0; loop < count; loop++) {
  //   printf("   %2d        %2d\n", characters[loop], copied[loop]);
  // }

  // sort copied arr by first character of contents
  // qsort(copied, count, sizeof(int), cmpfunc);

  // qsort(lines, count, 256, cmpfunc);
  
  // // print new order
  // printf("\nAfter sorting the list is: \n");
  // for( n = 0 ; n < count; n++ ) {   
  //   printf("%d ", copied[n]);
  // }

  // build new string order 


  // return char array

  // return characters;

  // return str;

}