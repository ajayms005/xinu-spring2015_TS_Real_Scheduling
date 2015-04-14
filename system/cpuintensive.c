#include <xinu.h>
#include <string.h>

void cpuintensive()
{
 int i,j;
 int alu;
 int LOOP1 = 15;
 char src[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
 char dest[50]; 
 int LOOP2 = 100000;
 for(i=0; i<LOOP1; i++){
   for(j=0; j< LOOP2; j++){
      memcpy(dest, src, strlen(src)+1);
      alu = 1+2;
      alu = alu + 3*4/5;
      }
      kprintf("The process pid in CPUIntensive is %d and the outer loop count is %d\n", currpid, i);
      kprintf("The process priority in CPUIntensive is  %d\n", proctab[currpid].prprio);
      kprintf("The remaining time slice in CPUIntensive is %d\n",preempt);
      }
      kprintf("The CPU time consumed by the process in CPUINtensive is %d\n", proctab[currpid].cputime);
      }

     
     
