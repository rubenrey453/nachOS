#include "syscall.h"

void display(void *arg)
{
	int i;
	for(i=97; i<123; i++) {
		PutChar(i);
       for(i=0; i<100; i++) { } 
      }					
	UserThreadExit();
}

int
main()
{
	int i;
	UserThreadCreate(display, (void *) '\0');
	for(i=65; i<91; i++)
       {
		PutChar(i);
       for(i=0; i<50; i++) { } 
      }				
	UserThreadExit();			
	return 0;
}
