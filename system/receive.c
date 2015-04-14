/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;                   /* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/

        pid32 this_sender;

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/
	if(!(isempty(prptr->senderqueue))){
	     int sender =0;
	     while(sender==0){
	        pid32 sendpid;
		if(!(isempty(prptr->senderqueue))){
		   sendpid = dequeue(prptr->senderqueue);
		   if(proctab[sendpid].sndflag!=0)
		   {
		    sender = 1;
		    this_sender = sendpid;
                   }
	     }
	     else{
	       restore(mask);
	       return msg;
	      }
	}
	}
	


//	prptr->prmsg = proctab[sendpid].sndmsg;
//	prptr->prhasmsg = TRUE;
//	proctab[sendpid].sndflag = 0;
	
	unsleep(this_sender);
	ready(this_sender);

	restore(mask);
	return msg;
}
