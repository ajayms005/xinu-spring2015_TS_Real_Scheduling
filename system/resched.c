/* resched.c - resched, resched_cntl */

#include <xinu.h>
#include <ts_init.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if(ptold->is_real_proc==1)
	{
	 if(ptold->prstate == PR_CURR){
	    if(ptold->real_prio > queuetab[firstid(60)].real_qkey)
	    {
	     return;
	     }

	     ptold->prstate = PR_READY;
	     insert_real(currpid, readylist[60], (double)(ptold->real_prio));
	     }
	     }

        //if the process is currently executing i.e it is executing currently, then it is considered as CPU bound process
	else{
	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		/*if (ptold->prprio > firstkey(readylist)) {
			return;
		}*/
		
                  /* Old process will no longer remain current */
	       if(currpid!=NULLPROC){
                ptold->prprio = tstab[ptold->prprio].ts_tqexp;
		}
		ptold->prstate = PR_READY;
		enqueue(currpid, readylist[ptold->prprio]); 


	}
        //if the process is in sleep state, it is considered to be as an I/O bound process
    	else if(ptold->prstate == PR_SLEEP){
	       ptold->prprio = tstab[ptold->prprio].ts_slpret;
	       }
        }

      /* Force context switch to highest priority ready process */
      //Now find the Process with the highest Priority from the ready list and then assign it as the currpid
        int i;
	for(i=60;i>=0;i--){
	      
	      if(!isempty(readylist[i]))
	      {
	       //enqueue(currpid, readylist[ptold->prprio]);
	       currpid = dequeue(readylist[i]);
	       if(currpid ==NULLPROC)
	       {
	        if(!isempty(readylist[i]))
	          {
		  enqueue(currpid, readylist[i]);
		  currpid = dequeue(readylist[i]);
		  }
		  }
		 break;
		  }
	       }
	       
	       
	
                 
	
	ptnew = &proctab[currpid];
	if(ptnew->is_real_proc==1)
	{
	  preempt = 70;
	}
	else
	{
	
	preempt = tstab[ptnew->prprio].ts_quantum;		/* Reset time slice for process	*/
	}
	ptnew->prstate = PR_CURR;
			
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	//run the call back function
	
	ptnew = &proctab[currpid];
	
	if(ptnew->asigcb == 0){
	if(proctab[currpid].func!=NULL && proctab[currpid].prhasmsg==TRUE)
	{
	  *(proctab[currpid].abuf)= proctab[currpid].prmsg;
	    
	    proctab[currpid].prhasmsg = FALSE;
	  
	  (*proctab[currpid].func)();
	  //  proctab[currpid].prhasmsg = FALSE;
         }
	 }


	 if(ptnew->asigcb ==1) {
            if(ptnew->optarg == 0)
	    {
	     if(ptnew->arecvfunc!=NULL && ptnew->prhasmsg==TRUE)
	     {
	        (*ptnew->arecvfunc)();   
	         // ptnew->prhasmsg = FALSE;
	     }
	     }
	    
	    
	  //  if(ptnew->optarg>0)
	    // {
	    //  if(ptnew->alarmfunc!=NULL && ptnew->prhasmsg==TRUE)
	     // {
	     if(ptnew->alarm_time>0)
	     {
	       if(myglobalclock >= ptnew->alarm_time)
	       {
	        
                
		 
		ptnew->alarm_time = -1;
                
	        (*ptnew->alarmfunc)();
                }
	}

    
	       // ptnew->prhasmsg = FALSE;
	      
	    // }
	   // }
         // }
}



	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
