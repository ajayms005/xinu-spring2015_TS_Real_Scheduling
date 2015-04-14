#include<xinu.h>

char myfuncA(char d);

int myProgA(int a, int b)
{
 register int sp asm("sp");
 int *ptr;
 ptr = sp;
 int i;
 int c;
 c = a+b;
 kprintf("The address of the stack pointer before calling MyFuncA is %x\n", sp);
 for(i=0;i<12;i++)
 {
  kprintf("The contents of the stack at position %d above the the stack pointer is %x\n", i, *ptr);
  ptr++;
 }		  
 
 myfuncA('1');
 return c;
 
 }
