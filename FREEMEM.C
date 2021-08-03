/* freemem.c - freemem */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <q.h>
#include "myH.h"

/*--------------------------------------------------------------------
 *  freemem  --  free a memory block, returning it to memlist
 *--------------------------------------------------------------------
 */
SYSCALL	freemem(block, size)
char *block;
word size;
{
	int	ps;
	struct	mblock	*p, *q;
	char	*top;
	int temp;
	size = roundew(size);
	block = (char *) truncew( (word)block );
	if ( size==0 || block > maxaddr || (maxaddr-block) < size ||
		block < end )
		return(SYSERR);
		
	disable(ps);
	block -= 4; //=====Lab 4 set block to real memory start (char is 1 bytes)
	
	for( q = &memlist, p=memlist.mnext ;
		(char *)p != NULL && (char *)p < block ;
		q=p, p=p->mnext );
	if ( q != &memlist && (top=(char *)q+q->mlen) > block
		 || (char *)p != NULL && (block+size) > (char *)p ) {
		restore(ps);
		return(SYSERR);
	}
	
	//=========================== LAB 4 ===============================
	//check if all memory is freed
	if(*(block) == size + 4){ //if we want to free all the memory
		size += 4;
		if( *((word*)(block+2)) == 1) // if the memory is tmem type
			update_tmemq(block + 4);   // send the pointer to allocated memery start 
	}
	else //if we want to free part of the memory
	{
		*(block+size) = *(block) - size; // copy of extra space used to save memory size and type
		*(block+size+2) = *(block + 2);	
		if( *(block+size+2) == 1 ) // if its tmem we need to update pointer in tmem_tab
		{
			temp = update_tmem_ptr(block + 4);
			*(tmem_tab[temp].tmem_ptr) += size; // sizeof(char*) = 2 bytes
		}
	}
	//==================================================================
	
	if ( q != &memlist && top == block )
		q->mlen += size;
	else {
		((struct mblock *)block)->mlen = size;
		((struct mblock *)block)->mnext = p;
		q->mnext = (struct mblock *)block;
		(char *)q = block;
	}
	if ( ((char *)q + q->mlen) == (char *)p ) {
		q->mlen += p->mlen;
		q->mnext = p->mnext;
	}
	restore(ps);
	return(OK);
}

//============================== LAB 4 ====================================
/* udates the tmem queue if memory was freed by a command instead of clock interrupt */
LOCAL update_tmemq(char* ptr)
{
	
	int current;
	int next_tmem;
	int actual_NQENT;
	actual_NQENT = NQENT;
	current = q[tmemq].qnext; 
	while( *(tmem_tab[current - actual_NQENT].tmem_ptr) != ptr )
	{
		current = q[current].qnext; 
	}
	next_tmem = q[current].qnext;
	if(next_tmem != tmemq_tail && q[current].qkey > 0)	{
		q[next_tmem].qkey += q[current].qkey;
	}
	kprintf("\nfreed time memory: %d\n",*(tmem_tab[current - actual_NQENT].tmem_ptr)); // to show which memory was freed
	*(tmem_tab[current - actual_NQENT].tmem_ptr) = NULL;	// set the pointer of freed memory to NULL
	tmem_tab[current - actual_NQENT].tmem_state = TMEMFREE;	// set the memory state in array to FREE
	dequeue(current);
	tmem_nempty = (q[(tmemq)].qnext < NTMEM + actual_NQENT);// check and set if the time memory queue is empty
}

/* find wanted memory in tmem queue*/
LOCAL int update_tmem_ptr(char* ptr)
{
	int current;
	int actual_NQENT;
	actual_NQENT = NQENT;
	current = q[tmemq].qnext; 
	while( *(tmem_tab[current - actual_NQENT].tmem_ptr) != ptr )
	{
		current = q[current].qnext;
	}
	return current - actual_NQENT;
}

//=========================================================================



