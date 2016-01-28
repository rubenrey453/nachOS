#include "syscall.h"
int main()
{	
	char v;
	while ((v= GetChar())!='q')
		PutChar(v);

	Halt();
	return 0;
}

