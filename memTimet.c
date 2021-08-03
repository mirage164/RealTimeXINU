/* MemTimet.c - getmemForTimet */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <q.h>
#include "myH.h"

/*-----------------------------------------------------------------------------------------------
 *  getmemForTimet  --  delay the caller for a time specified in system ticks
 *-----------------------------------------------------------------------------------------------
 */
 SYSCALL getmemForTimet(ticks,index)
 int ticks;
 int index;
 {
	int	ps;
	int actual_NQENT = NQENT;
	index += actual_NQENT; // tmemq start index is NQENT
	if ( ticks<0 )
		return(SYSERR);
	if (ticks == 0)
		return(OK);
	
    disable(ps);
    insertdTmem(index,tmemq,ticks); // allocate memory for time
	tmem_nempty = TRUE;				// indicates that the memory queue is not empty
	tmem_top = & q[q[tmemq].qnext].qkey;
    restore(ps);
	return(OK);
 }
 
 
 /*--------------------------------------------------------------------------------------------
 *  insertdTmem  --  insert tmem index in delta list "head", given its key customized for NTMEM
 *---------------------------------------------------------------------------------------------
 */
LOCAL insertdTmem(index, head, key)
int	index;
int	head;
int	key;
{
	int	next;			/* runs through list		*/
	int	prev;			/* follows next through list	*/

	for(prev=head,next=q[head].qnext ;
	    q[prev].qnext != tmemq_tail && q[next].qkey < key ; prev=next,next=q[next].qnext)
		key -= q[next].qkey;
	q[index].qnext = next;
	q[index].qprev = prev;
	q[index].qkey  = key;
	q[prev].qnext = index;
	q[next].qprev = index;
	if (next != tmemq_tail)
		q[next].qkey -= key;
	return(OK);
}