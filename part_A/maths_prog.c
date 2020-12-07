#include<stdio.h>
#include "subtract.h"
#include "add.h"

// #define MY_LIB "libmaths.so"


int main(int argc, char *argv[]){
  int a,b;
  scanf("%d %d",&a,&b);
  printf("%d+%d=%d\n",a,b,add(a,b)); 
  printf("%d-%d=%d\n",a,b,subtract(a,b)); 
  return 0;
}
