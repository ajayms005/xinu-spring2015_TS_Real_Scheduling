/* ready.c - ready */

#include <xinu.h>

qid16	readylist[61];			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	if(prptr->is_real_proc == 1){
	insert(pid, readylist[60], prptr->real_prio);
	}

	else{
	enqueue(pid, readylist[prptr->prprio]);
	}
	resched();

	return OK;
}
