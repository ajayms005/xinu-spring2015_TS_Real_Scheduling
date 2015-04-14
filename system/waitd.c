/* wait.c - wait */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wait  -  Cause current process to wait on a semaphore
 *------------------------------------------------------------------------
 */
syscall	waitd(
	  sid32		sem		/* Semaphore on which to wait  */
	)
{
	intmask mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	struct	sentry *semptr;         /* Ptr to sempahore table entry	*/
	int i,j;

	mask = disable();
	if (isbadsem(sem)) {
		restore(mask);
		return SYSERR;
	}

	semptr = &semtab[sem];
	if (semptr->sstate == S_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (--(semptr->scount) < 0) {	/* If caller must block	*/
	       
	       matrix[NPROC+sem][currpid] = 1;
	      // for(i=0;i<NPROC+NSEM;i++){
	      // for(j=0;j<NPROC+NSEM;j++){
	         // kprintf("%d ",matrix[i][j]);
		 // }
		 // kprintf("\n");
		 // }
	       if(cycle_detect())
		{
		 kprintf("Deadlock detected\n");
		 semptr->scount++;
		// kill(currpid);
		 return DEADLOCK;
		 }
		prptr = &proctab[currpid];
		prptr->prstate = PR_WAIT;	/* Set state to waiting	*/
		prptr->prsem = sem;             /* Record semaphore ID	*/
		//matrix[NPROC+sem][currpid] = 1;
		enqueue(currpid,semptr->squeue);/* Enqueue on semaphore	*/
		resched();			/*   and reschedule	*/
	}
        
	matrix[currpid][NPROC+sem] = 1;
	matrix[NPROC+sem][currpid] = 0;
	restore(mask);
	return OK;
}
