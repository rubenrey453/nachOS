#include "system.h"

void StartForkedProcess(int arg) {
    currentThread->space->RestoreState();
    currentThread->space->InitRegisters ();
    currentThread->space->ModifyCountinc();
    int mId = currentThread->space->stackBitMap->Find();
    currentThread->setZone(mId);
    int tnum = currentThread->space->GetMyThreadId(mId);
    currentThread->setId(tnum);
     machine->Run();
}

int do_ForkExec (char *filename)
{
    DEBUG ('t',"enterting process\n");
    OpenFile *exefile = fileSystem->Open (filename);
    AddrSpace *space;
    if (exefile == NULL) {
        printf ("Unable to open file %s\n", filename);
        delete [] filename;
        return -1;
    }
    DEBUG ('t',"code:2\n");
    space = new AddrSpace (exefile);
    DEBUG ('t',"code:3\n");
    if (space == NULL) {
        printf("%s : Error while starting the program\n",filename);
        delete exefile;
        delete [] filename;
        return -1;
    }
    delete exefile;
    Thread * execThread = new Thread(filename);
    execThread->space = space;
    machine->IncRunningProcess();
    execThread->Fork (StartForkedProcess, 0);
    return 0;
}

