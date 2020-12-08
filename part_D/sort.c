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
// sort -n: Use the numerical value to sort.
// sort -h: option that outputs usage information and briefly explains how much of this part of the coursework you have managed to implement.

// uses qsort() to actually sort

// must use switch case to choose arguments. 


// struct line {
//   char contents[255];
// };

int cmpfunc (const void * a, const void * b) {
  const char * pa = (const char *) a;
  const char * pb = (const char *) b;
  // printf("%c\n", pa[0]);
  // printf("%c\n", pb[0]);

  return ( (int)pa[0] - (int)pb[0] );
}



int main(int argc, char *argv[]){
  
  // char c[1000];
  // int bufferLength = 255;
  // char buffer[bufferLength];
  FILE *fp;

  // if (argc == 1){
  //   // file not specified
  //   printf("Error! opening file");
  //   return 1;
  // }
  

  // iterate through arguments

  while (*++argv){
    if((*argv)[0] == '-'){
      switch ((*argv)[1]){
        
        default: 
          printf("Unknown option-%c\n\n", (*argv)[1]);
          return 1;
        
        case 'h': 
          printf("\noption h is found\n\n");
          // displayUsageInfo();
          break;

        case 'o': 
          printf("\noption o is found\n\n");
          break;          
        
        case 'n': 
          printf("\noption n is found\n\n");
          break;          

        case 'r': 
          printf("\noption r is found\n\n");
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
    // store first character of each line in an array
    ProcessFileAlt(fp, argv[-1]);
    
    // WE ALSO NEED A WAY TO REMEMBER WHICH CHARACTER BELONGS TO WHICH LINE AS WE CURRENTLY DO NOT HAVE THIS INFORMATION
    // MAYBE WE NEED A STRUCT? FOR EACH CHARACTER WE HAVE AN ORIGINAL LINE INDEX FOR WHICH LINE IT BEGINS TO?????
    // sort array using the rules (qsort())

    // print entire file contents in correct sorting order based on the sorted array we have created. 

    return 0;
    }
}
void ProcessFileAlt(FILE* fp, char* filename){
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

  /* sort array by first character */
  qsort(lines, n, sizeof(char) * MAXC, cmpfunc);

  /* print lines */
  printf("Sorted array: \n");
  for (i = 0; i < n; i++) printf (" line[%2d] : '%s'\n", i + 1, lines[i]);




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