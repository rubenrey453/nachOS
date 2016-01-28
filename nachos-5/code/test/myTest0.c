#include "syscall.h"

void print(char c) {
    int j = 0, i=0;
    for (j=0; j<3; j++) {
        for (i=0; i<3000; i++) {}
        PutChar(c);
    }
    UserThreadExit(); 
}

int main() {
    int m,n;
    int t1;
    t1 = UserThreadCreate(print, (void *)'z');
    UserThreadJoin(t1);
    for (m=0; m<3; m++) {
        for (n=0; n<3000; n++) {}
        PutChar('K');
    }
    return 0;
}
