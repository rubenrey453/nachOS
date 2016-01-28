#include "syscall.h"

void f(void *arg)
{
        int i;	
	PutChar(*((char *)arg));
        for(i=0; i<20; i++){};
	PutString("Inside User Thread \n");
	UserThreadExit();
}

int
main()
{
	char number = '2';
        int i,j;
	j=UserThreadCreate(f, (void *) &number);
        UserThreadJoin(j);
	for(i=0; i<2000; i++){};
		PutString("Inside Main Thread \n");
	UserThreadExit();			
	return 0;
}
