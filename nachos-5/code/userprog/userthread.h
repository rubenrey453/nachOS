#include "system.h"
#include "syscall.h"
struct ForkArg
{
	int function;
	int argument;
	int zone;
};

extern int do_UserThreadCreate(int f, int arg );
extern void StartUserThread(int f);
extern void do_UserThreadExit();
extern int  do_UserThreadJoin(int thread_id);

