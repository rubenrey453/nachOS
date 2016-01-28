#include "syscall.h"

int main() {
    int i;
    PutString("start of test \n");
    for (i = 1; i < 16; i++) {
        ForkExec("putstring");
    }
    PutString("end of test\n");
    return 0;
}

