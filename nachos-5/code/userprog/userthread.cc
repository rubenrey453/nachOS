#include "userthread.h"
#include "system.h"
#include "forkprocess.h"

ForkArg *forkArgument = new ForkArg();
void StartUserThread(int thread) {
	DEBUG('t',"starting user thread\n");
	machine->WriteRegister (PCReg, forkArgument->function);
    	machine->WriteRegister (NextPCReg, forkArgument->function+4);
    	machine->WriteRegister (4, forkArgument->argument);
    	int threadOffset = 3 * PageSize;
    	machine->WriteRegister (StackReg, currentThread->space->getnumpage() * PageSize - 16 - PageSize - threadOffset);
    	DEBUG('t',"before run\n");
	machine->Run();
	
}

int do_UserThreadCreate(int f, int arg ) {
	Thread *newThread = new Thread("My Thread");
	if (newThread == NULL) { return -1; }
	DEBUG('t',"start : fetch the thread zone\n");
	int mId = currentThread->space->stackBitMap->Find();
	DEBUG('t',"result : derived the thread zone %d\n",mId);
	int tNum = currentThread->space->GetMyThreadId(mId);
        DEBUG('t',"result : derive the thread id %d\n",tNum);
	currentThread->space->ModifyCountinc();
	DEBUG('t',"opt: increased thread count by 1 %d\n",tNum);
        forkArgument->argument=arg;
	forkArgument->function=f;
        forkArgument->zone=mId;
        newThread->setZone(mId);
        DEBUG('t',"going to join\n");
        currentThread->space->JoinThreads[currentThread->space->Mid]->P();
	DEBUG('t',"going to fork\n");
	newThread->Fork(StartUserThread,int(forkArgument));
        return tNum; 
}

void do_UserThreadExit() {
     currentThread->space->JoinThreads[currentThread->space->Mid]->V();
     currentThread->space->ModifyCountdec();
     int threadCount=-1;
     currentThread->space->semRunningThreads->P();
     threadCount = currentThread->space->runningThreads;
     currentThread->space->semRunningThreads->V();
     DEBUG('t',"Current thread count is %d\n",threadCount);
    if (threadCount==0){
    	DEBUG('t',"last operation to halt\n");
        interrupt->Halt();
    }
    else{
      DEBUG('t',"Finishing current thread\n");
     currentThread->Finish();
   }
}

int do_UserThreadJoin(int thread_id) {
    DEBUG ('t', "invoke thread join for thread id %d\n",thread_id);
 
 int zone = -1;
    currentThread->space->semThreadZoneMap->P();
    for(int j = 0; j<256; j++) {
        if (currentThread->space->threadZoneMap[j] == thread_id) {
            if (currentThread->space->stackBitMap->Test(j))
                zone = j;
            break;
        }
    }
    currentThread->space->semThreadZoneMap->V();
    if (zone < 0)
    return zone;
     currentThread->space->JoinThreads[zone]->P();
     currentThread->space->JoinThreads[zone]->V();
    return 0;
}

