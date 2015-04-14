/*#include<xinu.h>

int roguefuncB(char c);

void rogueB2()
{ 
// int *p;
 putc(CONSOLE, 'B');
 sleepms(20);
 register int sp  asm("sp");
// p = ip;
 asm("mov %esp,0xfdefbbc \n\t");
 register int bx asm("ebx");
 kprintf("\n this is bx register %x\n",bx);
 kprintf("\n This is the sp bitch address: in rogue %x \n",sp);
 roguefuncB('b');
// sleepms(20);
 }

 int roguefuncB(char b)
 {
 // register int sp asm("sp");
 //asm("mov 8(%ebp),%eax\n\t"
   //   "add 0x30, %ebx\n\t"
     //"mov %esp, (%ebx)\n\t"); 
 // kprintf("\nin rogue %x\n",sp);
 // char cpy[1028] =  {'a'};
 // char buf[10];
 // strcpy(buf,cpy);
 putc(CONSOLE, b);
  return 1;
  
  }*/
