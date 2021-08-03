#include <conf.h>
#include <kernel.h>
#include <mem.h>
/* free all the memory only by starting pointer */ 
SYSCALL freep(p)
char *p;
{
	char * temp=p;
	temp -= 4; // location of saved memory size
	return freemem(p,*(temp)-4); // call freemem with actual size
}
