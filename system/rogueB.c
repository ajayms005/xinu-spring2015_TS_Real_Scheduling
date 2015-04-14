/*#include<xinu.h>

int nestedfunc(int);

void rogueB()
{
 putc(CONSOLE, 'B');
 sleepms(20);
 nestedfunc(123);
 sleepms(20);
 }

 int nestedfunc(int n)
 {
  static int i=1;
  i++;
  if(i==400)return 1;
  if(n==0) return 0;
  nestedfunc(n+1);
  }
*/
