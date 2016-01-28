#include "syscall.h"

void cDisplay(int i) {
      
 UserThreadExit();
}

void main () {

	int i=162;
	int checkFlag;
	checkFlag = UserThreadCreate(cDisplay, (void *)i);
	if (checkFlag == -1){
		PutString("Error creating user thread\n");
	}
	else {
            PutString("User Thread : ");
			PutString(" OK\n");
    }
	
	
}
