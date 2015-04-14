#include <xinu.h>

/*------------------------------------------------------------------------
 *  *  registercbsig  -  register a callback function and call it after a certain wait time
 *   *------------------------------------------------------------------------
 *    */
syscall	registercbsig( uint16 asig, int (* func) (void), uint32 optarg )
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/

	mask = disable();
	if ( func == NULL) {
		restore(mask);
	        return SYSERR;
	}

	kprintf("Inside registersig\n");

	prptr = &proctab[currpid];
	prptr->asigcb = 1;

	if(asig == ARECV)
	{
	// kprintf("Inside the sig in ARECV\n");
	 prptr->optarg = 0;
	 prptr->arecvfunc = func;
	 }
	
	if(asig == AALRM)
	{
       //	kprintf("Inside the sig in AALRM\n");
        prptr->alarmfunc = func;
        prptr->optarg = optarg;
	prptr->alarm_time = myglobalclock + optarg;
	kprintf("in register: myglobalclock = %d\n", myglobalclock);
	kprintf("Optarg = %d\n", optarg);
	}

	restore(mask);		/* restore interrupts */
	return OK;

}	
