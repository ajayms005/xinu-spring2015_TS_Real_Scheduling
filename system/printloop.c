#include<xinu.h>

void printloop(int val)
{
 int temp;
 int OUTERB = 5;
 int INNERB;  
 int max = 100000000;
 while(OUTERB>=0)
 {
  kprintf("%d",val);
  INNERB = max;
  while(INNERB>=0)
  {
    temp = 1;
    INNERB--;
    }
    OUTERB--;
  }
  }

  



