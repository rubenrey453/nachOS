#include "syscall.h"

void print(char c) {
    int j = 0, i=0;
    for (j=0; j<1; j++) {
        for (i=0; i<1; i++) {}
        
    }
  UserThreadExit(); 
}

int main() {
    int t2;
    t2 = UserThreadCreate(print, (void *)'x');
    UserThreadJoin(t2);
    return 0;
}

