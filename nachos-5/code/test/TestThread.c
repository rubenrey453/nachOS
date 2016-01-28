#include "syscall.h"
void print(int c)
{
	int i,n;
	n = 5;
	for (i = 0; i < n; i++) {
          outInt(c);
	}

UserThreadExit();
}
int main()
{
int i = 0;
int threadId=0;
for ( i = 0 ; i < 5 ; i++){
	threadId=UserThreadCreate(print,(void*)i);
        UserThreadJoin(threadId);
        
}
PutChar('E');
return 0;
}
