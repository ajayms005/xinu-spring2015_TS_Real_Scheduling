/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>


//char myfuncA(char d);

void printprocstks(void);

void someprogA();

void someprogB();

void rogueB();

void rogueB2();

long host2netl_asm(long);

long net2hostl_asm(long);

int myProgA(int a, int b);

int nestedfunc(int);

void printsegaddress(void);

int roguefuncB(char c);

void printloop(int);

void cpuintensive(void);

void iointensive(int);

void mydeadlocktest(sid32, sid32);

void myperiodicrtapp(int , int);

void sendMessage(pid32 recpid, umsg32 msg, int32 maxwait)
{
  
  kprintf("The global time before sendb is called is %d for the pid %d\n",myglobalclock, currpid);
  sendb(recpid, msg, maxwait);
  kprintf("The global time after sendb is called is %d for the pid %d\n",myglobalclock, currpid);

}


void receiveMessage(void)
{ 
 umsg32 msg;
 int i=0;
 for(i=0;i<2;i++){
 msg = receive();
 // sleepms(2);
 kprintf("The message recieved is %c\n", msg);
 }
}

umsg32 proc1buf;
umsg32 proc2buf;

int myrecvhandler1(void) {
      kprintf("msg received = %d\n",proc1buf);
      return(OK);
}


int myrecvhandler2(void) {
      kprintf("msg received = %d\n",proc2buf);
      return(OK);
}


int bonusrecvhandler1(void){
   umsg32 msg;
   msg = receive();
  // kprintf("Inside bonushandler1\n");
   kprintf("Bonus1: msg received= %d\n",msg);
   return OK;
}

int bonusrecvhandler2(void){
  // kprintf("After = %d\n", myglobalclock);
   umsg32 msg;
   msg = receive();
  // kprintf("Inside bonushandler2\n");
   kprintf("Bonus2: msg received= %d\n",msg);
   return OK;
 }

int bonusrecvhandler3(void){
   kprintf("After = %d\n", myglobalclock);
  //    umsg32 msg;
    //    msg = receive();
           // kprintf("Inside bonushandler2\n");
              kprintf("Bonus Passed\n");
                 return OK;
                 }
  



void recv1(void)
{
   if (registercb(&proc1buf,&myrecvhandler1) != OK) {
         kprintf("recv1 handler registration failed\n");
	    }
    while(1) {}
}

void recv2(void)
{
   if (registercb(&proc2buf,&myrecvhandler2) != OK) {
         kprintf("recv2 handler registration failed\n");
	    }
   while(1) {}
}

void bonusrecv1(void)
{
   if (registercbsig(ARECV,&bonusrecvhandler1,0) != OK) {
            kprintf("recv1 handler registration failed\n");
	                }
   while(1) {}
}

void bonusrecv2(void)
{
   if (registercbsig(ARECV,&bonusrecvhandler2,0) != OK) {
               kprintf("recv1 handler registration failed\n");
	      }
    while(1) {}
 }

void bonusrecv3(void)
{
   
   kprintf("Before  = %d\n", myglobalclock);		                
   if(registercbsig(AALRM,&bonusrecvhandler3,40) != OK) {
                  kprintf("recv1 handler registration failed\n");
		  }
  // kprintf("Before  = %d\n", myglobalclock);		                
   while(1) {}
}


			    

void send1(pid32 pid1, pid32 pid2, umsg32 msg1, umsg32 msg2)
{
   kprintf("Before bonus  1st send \n");
   send(pid1, msg1);
   kprintf("After bonus  1st Send \n");
  // sleepms(5);
   kprintf("Before bonus  2nd send\n");
   send(pid2, msg2);
   kprintf("After bonus  2nd send\n");
}

void send2(pid32 pid1, umsg32 msg1)
{
  kprintf("send2 time: %d\n",myglobalclock);
// kprintf("send2 before\n");
 send(pid1,msg1); 
// kprintf("send2 after\n");
 }

process	main(void)
{
       	kprintf("\nHello World!\n");
       	kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
       	kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
       	kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
       	kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
       	kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
	//kprintf("\n...creating a shell\n");
       //	recvclr(); 
     // resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
        
	//Part A
       // char p = 'P';
       //  pid32 pid1;
//	pid32 pid2;
//	pid32 pid3;
//	pid32 pid4;
        //Lab 2 4.1
//	
//	pid1 = create(printloop, 1024, 25, "child1",1, 11);
	
//	pid2 =create(printloop, 1024, 25, "child2",1, 22);

//	pid3 = create(printloop, 1024, 25, "child3",1, 33);

//	pid4 = create(printloop, 1024, 25, "child4",1, 44);
        
//	kprintf("%c",p);
//	resume(pid1);
//	kprintf("%c",p);
//	resume(pid2);
//	kprintf("%c",p);
//	resume(pid3);
//	kprintf("%c",p);
//	resume(pid4);
        
//	sleepms(5000);

  //Lab 2 Part B- CPU intensive
 // resume(create(cpuintensive, 1024, 20, "process1", 0));
 // resume(create(cpuintensive, 1024, 20, "process2", 0));
 // resume(create(cpuintensive, 1024, 20, "process3", 0));
 // resume(create(cpuintensive, 1024, 20, "process4", 0));
 // resume(create(cpuintensive, 1024, 20, "process5", 0));
 // resume(create(cpuintensive, 1024, 20, "process6", 0));
	
  //Lab 2 Part B -IO Intensive
  // resume(create(iointensive, 1024, 20, "process1", 0));
  // resume(create(iointensive, 1024, 20, "process2", 0));
  // resume(create(iointensive, 1024, 20, "process3", 0));
  // resume(create(iointensive, 1024, 20, "process4", 0));
  // resume(create(iointensive, 1024, 20, "process5", 0));
  // resume(create(iointensive, 1024, 20, "process6", 0));
  
  //Lab 2 Part B -Half Cpu And HAlf IO
    //Lab 2 Part B -IO Intensive
   // resume(create(cpuintensive, 1024, 20, "process1", 0));
   // resume(create(cpuintensive, 1024, 20, "process2", 0));
   // resume(create(cpuintensive, 1024, 20, "process3", 0));
   // resume(create(iointensive, 1024, 20, "process4", 0));
   // resume(create(iointenisive, 1024, 20, "process5", 0));
   // resume(create(iointensive, 1024, 20, "process6", 0));
    
 //Lab 2 Part B - myglobal clock
     // resume(create(cpuintensive, 1024, 20, "process1", 0));
     // resume(create(cpuintensive, 1024, 20, "process2", 0));
     // resume(create(cpuintensive, 1024, 20, "process3", 0));
     // resume(create(iointensive, 1024, 20, "process4", 1, 5));
     // resume(create(iointensive, 1024, 20, "process5",1, 20));
     // resume(create(iointensive, 1024, 20, "process6", 1, 10));
                             

  	
       //register int sp asm("sp");
       //	int *ptr;
       //	ptr = sp;
//	int i;
	
      //Question 5 Lab
       //resume(create(someprogB, 1024, 20, "someprogB", 0));
        // resume(create(rogueB, 1024, 20, "rogueB", 0));
      //  resume(create(rogueB2, 1024, 20, "rogueB2", 0));
       // resume(create(someprogA, 1024, 20, "someprogA", 0));

         
	/* Wait for shell to exit and recreate it */

       //	while (TRUE) {
	// Print the address and content of the top of the run-time stack	receive();
	//	sleepms(200);
	//	kprintf("\n\nMain process recreating shell\n\n");
	//	resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
       //	}
       
       //Question 3.3 Lab
      // kprintf("\n The stack pointer address is %x\n",sp);
      // kprintf("\n The contents of the top of the stack before myprogA is %x\n", *ptr);
      // for(i=1;i<=12;i++)
      // {
        // ptr++;
        // kprintf("The contents of the stack at position %d above the the stack pointer is %x", i, *ptr);
       // }
       //	resume(create(myProgA(1,2), 2048, 20, "process 1", 2));
     
     
     
     // Lab 3
    // sid32 s1, s2, s3,s4;
    // kprintf("Inside the semcreate part\n");
    // s1 = semcreate(1);
    // s2 = semcreate(1);
    // s3 = semcreate(1);
     //s4 = semcreate(1);
    // resume(create(mydeadlocktest, 2048, 20, "p1", 2, s1, s2));
    // resume(create(mydeadlocktest, 2048, 20, "p2", 2, s2, s3));
    // resume(create(mydeadlocktest, 2048, 20, "p3", 2, s3, s1));

    // resume(rt_create(40,10,myperiodicrtapp, 2048, 20, "r1", 2, 40, 10 ));
    // resume(rt_create(100,10,myperiodicrtapp, 2048, 20, "r2",2, 100, 10 ));
    // resume(rt_create(60,15,myperiodicrtapp, 2048, 20, "r3",2, 60, 15 ));

    // resume(create(cpuintensive, 2048, 20, "p1", 0));
    // resume(create(cpuintensive, 2048, 20, "p2", 0));
    // resume(create(cpuintensive, 2048, 20, "p3", 0));
     		
    //LAb 4
    

   // pid32 send1, send2, send3,send4, send5, rec1;
   // rec1 = create(receiveMessage, 1024, 20, "r1",0);
   // send1 = create(sendMessage, 1024, 10, "s1",3, rec1,'a',3);
   // send2 = create(sendMessage, 1024, 5, "s2",3, rec1,'b',10);
   
   // send3 = create(sendMessage, 1024, 25, "s3",3, rec1,'c',4);
   // send4 = create(sendMessage, 1024, 15, "s4",3, rec1,'d',10);
   // resume(rec1);
   // resume(send1);
   // resume(rec1);
   // resume(send2);
   
   // resume(send3);
   // resume(send4);
    

     pid32 pid1, pid2, pid3;
    // pid1 = create(bonusrecv1,1024,20,"r1",0);
     pid2 = create(bonusrecv3,1024,20,"r2",0);
    // pid3 = create(send1,1024,20,"s1",4,pid1,pid2,'a','b');
     
    // pid3 = create(send2,1024,20,"s2",2,pid2,'a');
    // resume(pid1);
    // resume(pid3);
    
    
    resume(pid2);
     
     
     
     //Question 3.4 Lab
    // printprocstks();

      
      // Question 3.1 Lab 
      // long x = 0xABCDABCD;
      // long y = host2netl_asm(x);
      // kprintf("After the host2netl conversion, the address is %x\n", y);
      // long z = net2hostl_asm(y);
      // kprintf("After the net2hostl conversion, the address is %x\n", z);
      
      // Question 3.2 Lab
      //printsegaddress();

      return OK;
}

/*
int somefuncB(char b)
{
 sleepms(20);
 putc(CONSOLE, 'b');
 return 1;
}

void someprogB()
{
 putc(CONSOLE,'B');
 somefuncB('b');
 putc(CONSOLE,'B');
 }

int somefuncA(char a)
{
 sleepms(20);
 putc(CONSOLE, a);
 return 1;
 }

void someprogA()
{
  putc(CONSOLE, 'A');
  somefuncA('a');
  putc(CONSOLE,  'A');
 } 



void rogueB()
{
 putc(CONSOLE, 'B');
 sleepms(20);
 nestedfunc(123);
 putc(CONSOLE , 'B');
 sleep(20);
 }

int nestedfunc(int n)
{
  static int i=1;
  i++;
  int a = 10;
  int b = 20;
  if(i==50)return 1;
  if(n==0) return 0;
  nestedfunc(n+1);
  }

void rogueB2()
  {
   int *p;
   putc(CONSOLE, 'B');
   sleepms(20);
   register int sp  asm("sp");
   p = sp;
   asm("mov %esp,0xfdefbbc \n\t");
         register int bx asm("ebx");
         kprintf("\n this is bx register %x\n",bx);
         kprintf("\n This is the sp address: in rogue %x \n",sp);
         roguefuncB('b');
         sleepms(20);
       }
           
 int roguefuncB(char b)
   {
     register int sp asm("sp");
     asm("mov 8(%ebp),%eax\n\t"
         "add 0x30, %ebx\n\t"
         "mov %esp, (%ebx)\n\t");
     kprintf("\nin rogue %x\n",sp);
  // char cpy[1028] =  {'a'};
  // char buf[10];
  // strcpy(buf,cpy);
     putc(CONSOLE, b);
     return 1;
}

*/































  //                               }
  //

