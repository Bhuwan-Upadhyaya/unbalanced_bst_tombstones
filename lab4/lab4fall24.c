/* 
Name :Bhuwan Upadhyaya
Netid: bxu9187 /1002079187

I used the following command in omega server
gcc -Wall -o lab4 lab4fall24.c bst.c
./lab4 < lab4fall24.a.dat (or cat lab4fall24.a.dat | ./lab4)


Also i tried using the powershell
gcc -Wall -o lab4 lab4fall24.c bst.c
Get-Content lab4fall24.a.dat | ./lab4

*/ 

// Driver to handle operations in 3318 Lab 4, Fall 2024
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

int main()
{
int op,key,rank;

STinit();  // Initialize binary search tree
verifyBSTproperties();

scanf("%d",&op);
while (op)
{
  switch (op)
  {
    case 1:
      scanf("%d",&key);
      printf("1 %d\n",key);
      STinsert(key);
      break;
    case 2:
      scanf("%d",&key);
      printf("2 %d\n",key);
      STdelete(key);
      break;
    case 3:
      scanf("%d",&key);
      printf("3 %d\n",key);
      rank=STinvSelect(key);
      if (rank==(-1))
        printf("Key %d is not in tree\n",key);
      else
        printf("Key %d has rank %d\n",key,rank);
      break;
    case 4:
      scanf("%d",&rank);
      printf("4 %d\n",rank);
      if (rank<1 || rank>getLive())
        printf("rank %d range error\n",rank);
      else
        printf("rank %d has key %d\n",rank,key(STselect(rank)));
      break;
    case 5:
      printf("5\n");
      printf("Live %d Dead %d Recycled %d Height %d\n",
        getLive(),getDead(),getRecycled(),getHeight());
      break;
    case 6:
      printf("6\n");
      removeDead();
      break;
    case 7:
      printf("7\n");
      STprintTree();
      break;
    case 8:
      printf("8\n");
      if (verifyBSTproperties())
        printf("clean\n");
      else
        printf("corrupt\n");
      break;
    default:
      printf("Bad operation %d\n",op);
  }
  //fflush(stdout);  // In case output is going to a fifo
  scanf("%d",&op);
}
printf("0\n");
return 0;
}