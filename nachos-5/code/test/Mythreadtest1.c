#include "syscall.h"
void print(int c)
{
	int i,n;
	n = 500;
	for (i = 0; i < n; i++) {
	}
PutChar('J');
UserThreadExit();
}
void disp(int c)
{
	int i,n;
	n = 6000;
	for (i = 0; i < n; i++) {
	}
PutChar('M');
UserThreadExit();
}

int main()
{
int i = 0;
int j,m,l,k=200;
 j=UserThreadCreate(print,(void*)i);
 UserThreadJoin(j);
for (l = 0; i < k; i++) {}
 m=UserThreadCreate(disp,(void*)i); 
 UserThreadJoin(m);        
PutChar('E');
return 0;
}
