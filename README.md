# RealTimeXINU
Changing memory management and son process priority after xfork. 

Memory management changes:

In XINU the original memory allocation function is getmem(int memory_in_bytes) that returns the pointer to the allocated memory if succeeded.
Freeing memory function is freemem(cahr* pointer_to_memory, int size_of_memory_in_bytes).

Added function to allocate memory for period of time: getmemForTime(int size_in_bytes, int time_in_seconds, void** pointer)
this function is allocationg memory for time_in_seconds period and then the momory freed atomaticly.

Added function to atomaticly free all the momory that the pointer points to without specifying the memory size: freep(char* pointer)

---------------------------------------------------------------------------------------------------------------------------------------------------------

Process priority after xfork:

Added function xforkSonFirst(), similar to xfork() function but in xforkSonFirst() the father process gives up the CPU time for the son process.

Added function xwait() that waits to first son process to finish.

Added funtion xwaitAll() that waits to all son processes to finish.
