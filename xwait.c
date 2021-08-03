#include <sem.h>
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include "myH.h"


	/* wait for one of the sons to finish */
SYSCALL xwait()
{
	if(proctab[currpid].psem != 0)
	{
		wait(proctab[currpid].psem);
		return 1; // ack wait until one of sons is finished
	}
	return 0; // not waited (no sons)
}



	/*wait for all sons to finish*/
SYSCALL xwaitAll()
{
		while(semaph[currpid].semcnt < -1)
		{
			xwait();
		}
		return 1; // ack waited for all sons
	
	return 0; // not waited (no sons)
	
}