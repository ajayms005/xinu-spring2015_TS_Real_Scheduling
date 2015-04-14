/*#include<xinu.h>

int somefuncA(char a)
{
// register int sp asm("sp");
 //kprintf("%x Bitch work This time\n", sp);
 sleepms(20);
 putc(CONSOLE, a);
 return 1;
 }

 void someprogA()
 {
  putc(CONSOLE, 'A');
 // int *p;
 // register int sp asm("sp");
 // p = sp;
 // kprintf("%x\n",sp);
 // kprintf("The contents of the stack pointer now is %x\n",*p);
  somefuncA('a');
  putc(CONSOLE,  'A');
  }*/
