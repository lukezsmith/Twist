#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<io.h>    it's not standart


#define MAXCHAR 256

//  I implement the function because the warning is that
//  Incompatible pointer types passing 'int
//  (const char *, const char *)' to parameter of type
//  'int (*)(const void *, const void *)'

//  Already qsort() prototype is

// void qsort(void* ptr, size_t count, size_t size,
// int (*comp)(const void*, const void*));

// I think that the warning can be ignored strcmp also can be used

int myCompare(const void* a, const void* b)
{
    const char* aa = (const char*)a;
    const char* bb = (const char*)b;
    return strcasecmp(aa, bb);
}

int main(int argc, char **argv){
    char tempList[MAXCHAR][MAXCHAR];
    char reader[MAXCHAR];
    FILE* fp;
    int i;
    char *n;
    int index = 0;
    if(argc != 2){
        printf("too few arguments\n");
        exit(-1);
    }

    fp=fopen(argv[1], "r");
    if(fp == NULL){
        printf("failed to open file\n");
        exit(-1);
    }
    while(fgets(reader, MAXCHAR, fp) != NULL){ // !feof is not recommended search why

        n = strchr(reader, '\n');
        if(n != NULL){
            *n = '\0';
        }
        strcpy(tempList[index], reader);
        index++;
    }

    /*
    printf("%lu\n",sizeof(reader));     //256
    printf("%lu\n",sizeof(*reader));    //1
    printf("%lu\n",sizeof(*tempList));  //256
    printf("%lu\n",sizeof(**tempList)); //1
    */

    for(i=0; i<index; i++){
        printf("%s\n", tempList[i]);

    }
    qsort(tempList, index, sizeof(*tempList), myCompare);
    printf("\n\nAfter sorting\n\n");
    for(i=0; i<index; i++){
        printf("%s\n", tempList[i]);
    }
}