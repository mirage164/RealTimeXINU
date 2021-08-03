extern SYSCALL freep(char* p);
extern SYSCALL getmemForTime(int nbytes,  int secs, void **ptr);
extern SYSCALL getmemForTimet(int ticks, int index);
extern SYSCALL xforkSonFirst();
extern SYSCALL xwait();
extern SYSCALL xwaitAll();
#define	NTMEM		52 /* maximum 50 time memorys + 2 extra for head and tail*/

/* time memory state constants */
#define	TMEMUSED		'\01'
#define	TMEMFREE		'\02'

/* time memory entry */
struct	tmem_entry	{
	int tmem_index;		/*index of the memory*/
	char tmem_state;	/*state of the memory*/
	int	time;			/*remaining life time*/
	char **tmem_ptr;		/*pointer to allocated memory*/
};

extern	struct	tmem_entry tmem_tab[]; /* tab of time memory */
extern	int	tmemq;		/* q index of time memory list	*/
extern  int tmemq_tail;  /* time memory queue tail*/
extern	int	*tmem_top;		/* address of first key on tmemq	*/
extern	int	tmem_nempty;	/* 1 if tmemq is not empty		*/ 
extern  int parent_pid[]; 	/* array to save the parent of each child procces */
