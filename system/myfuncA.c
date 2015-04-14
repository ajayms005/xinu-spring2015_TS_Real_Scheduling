#include<xinu.h>

char myfuncA(char d)
{
 register int sp asm("sp");
 int *ptr;
 ptr = sp;
 int i;
 kprintf("The address of the stack pointer before returning from  MyFuncA is %x\n", sp);

 for(i=0;i<12;i++)
 {
 
 kprintf("The contents of the stack at position %d above the the stack pointer is %x\n", i, *ptr);
 ptr++;
  }
 return d;
 }
