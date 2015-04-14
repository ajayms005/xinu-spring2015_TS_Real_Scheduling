/* signal.c - signal */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  signal  -  Signal a semaphore, releasing a process if one is waiting
 *------------------------------------------------------------------------
 */
syscall	signal(
	  sid32		sem		/* ID of semaphore to signal	*/
	)
{
	intmask mask;                   /* Saved interrupt mask		*/
	pid32 pid_ready_dead;
	struct	sentry *semptr;		/* Ptr to sempahore table entry	*/

	mask = disable();
	if (isbadsem(sem)) {
		restore(mask);
		return SYSERR;
	}
	semptr= &semtab[sem];
	if (semptr->sstate == S_FREE) {
		restore(mask);
		return SYSERR;
	}

	matrix[currpid][NPROC+sem] = 0;  //for deadlock detection
	if ((semptr->scount++) < 0) {	/* Release a waiting process */
		pid_ready_dead = dequeue(semptr->squeue);
		//matrix[NPROC+sem][pid_ready_dead] = 0; //for deadlock detection
		ready(pid_ready_dead);

	}
	restore(mask);
	return OK;
}
