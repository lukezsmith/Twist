#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "sort.h"

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


struct line {
  char contents[255];
};

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}



int main(int argc, char *argv[]){
  
  // char c[1000];
  int bufferLength = 255;
  char buffer[bufferLength];
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
    ProcessFile(fp, argv[-1]);
    
    // WE ALSO NEED A WAY TO REMEMBER WHICH CHARACTER BELONGS TO WHICH LINE AS WE CURRENTLY DO NOT HAVE THIS INFORMATION
    // MAYBE WE NEED A STRUCT? FOR EACH CHARACTER WE HAVE AN ORIGINAL LINE INDEX FOR WHICH LINE IT BEGINS TO?????
    // sort array using the rules (qsort())

    // print entire file contents in correct sorting order based on the sorted array we have created. 

    return 0;
    }
}

void ProcessFile(FILE* fp, char* filename){
  struct line lines[255];

  int freeSpace = 0;

  int count = 0;
  char c;
  char d;
  
  char myString [1000];
  int upper = 0;
  int lower = 0;

  int bufferLength = 255;
  char buffer[bufferLength];

  int n =0;
  fp = fopen (filename , "r");

  // count file lines
  while(!feof(fp))
  {
    d = fgetc(fp);
    if(d == '\n')
    {
      count++;
    }
  }
  while (d != EOF);
  if(d != '\n' && count != 0)
    count++;

  printf("The file has %d lines\n ", count); 

  // move file pointer back to beginning of the file
  rewind(fp);
  // define line character arrays
  int characters [count];
  int copied [count];

  // add each line's first character to comparison array
  printf("First non-space characters encountered:\n");
  while(fgets( myString, 1000, fp) != NULL){
    int jj = -1;
    while(++jj < strlen(myString)) {
      if ((c = myString[jj]) != ' ') break;
    }

    // add character to array
    characters[freeSpace]=  (int)c;
    freeSpace++;
  }
  fclose (fp);

  // // test iteration over characters arr
  // for (int i = 0; i< 8; i++){
  //   printf("%c \n", characters[i]);
  // }

  // copy character array
  for (int i = 0; i< count; i++){
    // printf("%c \n", characters[i]);
    copied[i] = characters[i];
  }

  printf("original -> copied \n");
  
  // copy array
  for(int loop = 0; loop < count; loop++) {
    printf("   %2d        %2d\n", characters[loop], copied[loop]);
  }

  // sort copied arr by first character of contents
  qsort(copied, count, sizeof(int), cmpfunc);
  
  // print new order
  printf("\nAfter sorting the list is: \n");
  for( n = 0 ; n < count; n++ ) {   
    printf("%d ", copied[n]);
  }

  // build new string order 


  // return char array

  // return characters;

  // return str;

}