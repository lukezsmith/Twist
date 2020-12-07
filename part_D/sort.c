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
  // char arr= malloc(10 * sizeof(char));
  // struct character characters[100];
  struct line lines[255];
  int freeSpace = 0;
  
  char myString [1000];
  int upper = 0;
  int lower = 0;

  int bufferLength = 255;
  char buffer[bufferLength];

  // char c;
  int n =0;
  fp = fopen (filename , "r");
  // printf("First non-space characters encountered:\n");
  // while(fgets( myString, 1000, fp) != NULL){
  //   int jj = -1;
  //   while(++jj < strlen(myString)) {
  //     if ((c = myString[jj]) != ' ') break;
  //   }
  //   // add character STRUCT OBJECT to array
  //   characters[freeSpace].lineIndex = freeSpace;
  //   characters[freeSpace].c = c;

  //   freeSpace++;
  // }

  // create struct object with each line in input file
  while(fgets(buffer, bufferLength, fp)) {
      // printf("%s\n", buffer);
    strcpy(lines[freeSpace].contents, buffer);
    freeSpace++;
  }

  fclose (fp);

  // // test iteration over characters struct
  // for (int i = 0; i< 3; i++){
  //   printf("%s \n", lines[i].contents);
  // }

  

  // return char array

  // return characters;

  // return str;

}