#include "syscall.h"
#include "console.h"

static Console *console;

void print(char c, int n)
{
int i;
for(i=0; i < n; i++) {
	console-> PutChar(c+i);
}
console-> PutChar('\n');
}

int main() {
print ('a',4);
Halt();
}
