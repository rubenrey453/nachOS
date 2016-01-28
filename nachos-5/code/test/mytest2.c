#include "syscall.h"

void print2(char d) {
    int k = 0;
     while(k==5){
     PutChar('c');
     k++;
    }
UserThreadExit();
 }  
 
int main() {
    int i = 0;
    int t1;
    for (i=0; i<3000; i++) {
       t1 = UserThreadCreate(print2, (void *)'c');
       UserThreadJoin(t1);
   }
    return 0;
}

