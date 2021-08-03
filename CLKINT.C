/* clkint.c - clkint */

#include <conf.h>
#include <kernel.h>
#include <sleep.h>
#include <io.h>
#include <q.h>
#include "myH.h"


/*------------------------------------------------------------------------
 *  clkint  --  clock service routine
 *  called at every clock tick and when starting the deferred clock
 *------------------------------------------------------------------------
 */
INTPROC clkint(mdevno)
int mdevno;				/* minor device number		*/
{
	int	i;
        int resched_flag;

        
	tod++;

        resched_flag = 0;
	if (slnempty)
		if ( (--*sltop) <= 0 )
                     {
                        resched_flag = 1;
			wakeup();
                     } /* if */
	if ( (--preempt) <= 0 )
             resched_flag = 1;

       if (resched_flag == 1)
 		resched();

	/*================= Lab 4 ==================*/
	if (tmem_nempty)
		if ( (--*tmem_top) <= 0 )
                     free_tmem();
                   
	/*==========================================*/
}

/* find all the time memory that needs to be freed */
LOCAL free_tmem()
{
	struct tmem_entry *ptr;
	int actual_nqent = NQENT; 
	while ( (q[(tmemq)].qnext != tmemq_tail) && (firstkey(tmemq) <= 0) )
	{
		ptr = &tmem_tab[q[tmemq].qnext - actual_nqent]; 
		freep(*(ptr->tmem_ptr));
	}
	
	if ( (tmem_nempty = (q[(tmemq)].qnext < NTMEM + actual_nqent)) != 0 ) 
		tmem_top = &firstkey(tmemq);
}