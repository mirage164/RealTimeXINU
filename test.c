#include <conf.h>
#include <kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <q.h>
#include <sleep.h>
#include <proc.h>
#include <sem.h>
#include "myH.h"

void print_a();
void print_b();
xmain()
{
	char *p,*q,*y,*ptr1,*ptr2,*ptr3,*ptr4,**test;
	struct mblock *mymemlist = memlist.mnext;
	int i = 0,pid;
	int temp;
	
	//=========================== Part 5 ================================
	p = getmem(16);
	q = getmem(32);
	y = getmem(16);
	
	if(!p){
		kprintf("ERROR!!!!\n");
		return 0;
	}
	kprintf("Address:%d Size: Expected: 20 Actual: %u\n",p,*(p-4));
	kprintf("Address:%d Size: Expected: 36 Actual: %u\n",q,*(q-4));
	kprintf("Address:%d Size: Expected: 20 Actual: %u\n",y,*(y-4));
	
	kprintf("Expected: 1 Actual: %d\n",freemem(p,8));
	kprintf("Expected: -1 Actual: %d\n",freemem(p,1));
	kprintf("Expected: 12 Actual: %d\n",*(p-4+8));
	kprintf("Expected: 1 Actual: %d\n",freemem(p+8,8));
	kprintf("Expected: -1 Actual: %d\n",freemem(p+8,1));
	kprintf("Expected: -1 Actual: %d\n",freemem(p+12,1));
	kprintf("Expected: 36 Actual: %d\n",*(p+16));
	kprintf("Expected: -1 Actual: %d\n",freemem(p+16,1));
	
	kprintf("freep testing:\n");
	kprintf("Expected: 1 Actual: %d\n",freep(q));
	kprintf("Expected: -1 Actual: %d\n",freep(q));
	kprintf("Expected: 1 Actual: %d\n",freemem(y,8));
	kprintf("Expected: 12 Actual: %d\n",*(y-4+8));
	kprintf("Expected: 1 Actual: %d\n",freep(y+8));
	kprintf("Expected: -1 Actual: %d\n",freep(y+8));
	//===================================================================
	
	
	
	//=========================== Part 4 ================================
	kprintf("tmemq head:%d tmemq_tail:%d\n",tmemq,tmemq_tail);
	getmemForTime(20,10,&ptr1);
	kprintf("ptr1 address: %u memory size: %u memory type: %u\n",ptr1,*(ptr1-4),*(ptr1-2));
	getmemForTime(20,10,&ptr2);
	kprintf("ptr2 address: %u memory size: %u memory type: %u\n",ptr2,*(ptr2-4),*(ptr2-2));
	getmemForTime(20,20,&ptr3);
	kprintf("ptr3 address: %u memory size: %u memory type: %u\n",ptr3,*(ptr3-4),*(ptr3-2));
	ptr4 = getmem(16);
	kprintf("ptr4 address: %u memory size: %u memory type: %u\n",ptr4,*(ptr4-4),*(ptr4-2));
	while(ptr3 != NULL){
		kprintf("%d ",i++);
		if(i==5){
			freemem(ptr3,10);
			kprintf("\n12 bytes of ptr3 freed. ptr3 address: %d\n",ptr3);
		}
		sleep(1);
	}
	freep(ptr4);
	kprintf("\nmemory is no longer allocated\n");
	getchar();
	
	//===================================================================
	
	
	
	//======================== Part 1 xforkSonFirst===================================
	pid = xforkSonFirst();
	if(pid)
	{
		for(i=1;i<5;i++)
		{
			kprintf("A");
		}
	}
	else
	{
		for(i=1;i<5;i++)
		{
			kprintf("B");
		}
	}
	kprintf("\n");
	pid = xforkSonFirst();
	if(pid)
	{
		for(i=1;i<5;i++)
			kprintf("C");
		
	}
	else
	{
		for(i=1;i<5;i++)
			kprintf("D");
		
	}
	
	//===============================================================================
	
	
	//======================= part 1 normal xfork ===================================
	pid = xfork();
	if(pid)
	{
		for(i=1;i<5;i++)
		{
			kprintf("A");
		}
	}
	else
	{
		for(i=1;i<5;i++)
		{
			kprintf("B");
		}
	}
	kprintf("\n");
	pid = xfork();
	if(pid)
	{
		for(i=1;i<5;i++)
			kprintf("C");
		
	}
	else
	{
		for(i=1;i<5;i++)
			kprintf("D");
		
	}
	sleep(5);
	
	//===============================================================================
	
	
	
	
	
	/*
	//=================== part 2 test =================
	kprintf("main pid:%d\n",currpid);
	pid = xfork();
	if(pid == 0)
		kprintf("currpid:%d A\n",currpid);
	pid = xfork();
	if(pid == 0)
		kprintf("currpid:%d B\n",currpid);
	
	xwait();
	kprintf("currpid:%d C\n",currpid);
	//======================================================
	
	
	
	
	
	//======================= part 3 =======================
	temp = currpid;
	pid = xfork();
	if(temp == currpid )
		pid = xfork();
	if(pid == 0)
		kprintf("I am a son with pid:%d\n",currpid);
	xwaitAll();
	kprintf("procces: %d finished\n",currpid);
	//======================================================
	*/
	
	if(currpid == 4)
	{
		kprintf("FINISH!\n");
		getchar();
	}
}

















