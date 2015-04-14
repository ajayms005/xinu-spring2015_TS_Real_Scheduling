#include <xinu.h>
#include <string.h>

void iointensive(int x)
{
 int i,j;
 int savedclock;
 int res;
 int LOOP1 = 5;
 char src[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
 char dest[50];
 int LOOP2 = 100;
 for(i=0; i<LOOP1; i++){
   for(j=0; j< LOOP2; j++){
        savedclock = myglobalclock;
	sleepms(x);
        res = myglobalclock - savedclock;
       }
       
    printf("The difference of myglobalclock is %d\n", res);
   kprintf("The process pid in IOIntensive is %d and the outer loop count is %d\n", currpid, i);
   kprintf("The process priority in IOIntensive is %d\n", proctab[currpid].prprio);
   kprintf("The remaining time slice in IOIntensive is %d\n",preempt);
   }
 kprintf("The CPU time consumed by the process in IOIntensive is %d\n", proctab[currpid].cputime);
 }

