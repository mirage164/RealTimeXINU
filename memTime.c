/* MemTime.c - getmemForTime */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <sleep.h>
#include "myH.h"
#include <q.h>

/*-----------------------------------------------------------------------------------------------
 *  getmemForTime  --  allocate heap storage, returning lowest integer address for temporary time
 *-----------------------------------------------------------------------------------------------
 */
 
 SYSCALL getmemForTime(nbytes, secs, ptr)
 int nbytes;
 int secs;
 void **ptr;
 {
	int i;
	if ( secs<1 )
		return(SYSERR);
	
	if(*ptr = getmem(nbytes))
	{
		/* create tmem_entry */
		*(((word *)(*ptr))-1) = 1;	//=========== init mem type (0-normal, 1-tmem)
		i = newTmemIndex();
		tmem_tab[i].tmem_state = TMEMUSED;
		tmem_tab[i].time = secs;
		tmem_tab[i].tmem_ptr = ptr;	
		while (secs >= TICSD) {
			getmemForTimet(TICSN,i);
			secs -= TICSD;
		}
		if (secs > 0)
			getmemForTimet( (int)( ((long)secs*(long)TICSN) / (long)TICSD ),i);
	}
	return(OK);
 }
 
 /*------------------------------------------------------------------------
 *  newTmemIndex  --  obtain a new (free) tmem index
 *------------------------------------------------------------------------
 */
LOCAL	newTmemIndex()
{
	int	i;			/* memory index to return		*/

	for (i = 2 ; i<NTMEM ; i++) {	/* check all NTMEM slots	*/
		if (tmem_tab[i].tmem_state == TMEMFREE)
			return i;
	}
	return(SYSERR);
}