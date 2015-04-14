#include<xinu.h>

void printprocstks()
{
 struct procent *p;
 
 create(myProgA(1,2), 1024, 20, "Process1", 2);
 create(myfuncA('d'), 1024, 20, "Process2", 1);

 
 int i;
 pid32 pid;

 for(i = 0; i < NPROC; i++)
 {
  if(((p = &proctab[i])->prstate)!=PR_FREE)
  {
   kprintf("Proc[%s].Pid = %d\n", p->prname,i);
   kprintf("Stack: Base = %x\n\t", p->prstkbase);
   kprintf("Len = %x\n\t", p->prstklen);
   kprintf("Limit = %x\n\t",(p->prstkbase-p->prstklen));

   if(((p=&proctab[i])->prstate)!=PR_CURR)
   {
    kprintf("StkPtr = %x\n", p->prstkptr);
    }
    else
    {
     register int sp asm("sp");
     kprintf("StkPtr = %x\n", sp);
     }
     }
     }
     }
