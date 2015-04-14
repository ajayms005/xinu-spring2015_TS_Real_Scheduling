#include<xinu.h>

extern int edata,etext,bss;


void printsegaddress(void)
{
 char *p,*q,*r;
 p = &etext;
 q = &edata;
 r = &bss;
 int i;
 kprintf("The end of the text segment is %x\n", &etext);
 kprintf("The end of the data segment is %x\n", &edata);
 kprintf("The end of the bss  segment is %x\n", &bss);
 for(i=0; i<13; i++)
 {
  kprintf("The contents above the text segment and at location %d is %x\n", i, p[i]);
  }
 for(i=0; i<13; i++)
 {
  kprintf("The contents above the data  segment and at location %d is %x\n", i, q[i]);
  }
 for(i=0; i<13; i++)
 {
  kprintf("The contents above the bss segment and at location %d is %x\n", i, r[i]);
  }
  for(i=0; i<13; i++)
 {
  kprintf("The contents below the text segment and at location %d is %x\n", i, *p);
  p--;
 }
  for(i=0; i<13; i++)
 {
  kprintf("The contents below  the data segment and at location %d is %x\n", i, *q);
  q--;
  }
 for(i=0; i<13; i++)
 {
  kprintf("The contents below  the bss  segment and at location %d is %x\n", i,*r);
  r--;
  }


}
 
