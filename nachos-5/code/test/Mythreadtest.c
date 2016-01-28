#include "syscall.h"
void print(int c)
{
	int i,n;
	n = 500000;
	for (i = 0; i < n; i++) {
	}
PutChar('J');
UserThreadExit();
}
int main()
{
int i = 0;
for ( i = 0 ; i < 5 ; i++)
	UserThreadCreate(print,(void*)i);
PutChar('E');
return 0;
}
