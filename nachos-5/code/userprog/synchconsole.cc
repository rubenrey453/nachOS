#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"


static Semaphore *readAvail;
static Semaphore *writeDone;

//Step 3
static Semaphore *write_mutex;
static Semaphore *read_mutex;

static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);
	
	write_mutex = new Semaphore("Mutex write", 1);
	read_mutex  = new Semaphore("Mutex read", 1);

	console = new Console (readFile, writeFile, ReadAvail, WriteDone, 0);
}
SynchConsole::~SynchConsole()
{
	delete console;
	delete writeDone;
	delete readAvail;
}
void SynchConsole::SynchPutChar(const char ch)
{
//write_mutex->P();
	console->PutChar(ch);
	
	writeDone->P(); //wait to enter a character
//write_mutex->V();
}
char SynchConsole::SynchGetChar()
//char SynchConsole::SynchGetChar(int *ch)
{
	read_mutex->P();
	readAvail->P ();        // wait for character to arrive
	char c = console->GetChar();
	read_mutex->V();
	return c;

}
void SynchConsole::SynchPutString(const char s[])
{
	write_mutex->P();
	int i=0;
	while(s[i]!='\0')
	{
		this->SynchPutChar(s[i]);
		i++;
	}
	write_mutex->V();
	//this->SynchPutChar('\0');
}
void SynchConsole::SynchGetString(char *s, int n)
{
	read_mutex->P();
	int i;
	i=0;
	while(s[i]!='\0' && i<=n-1 && s[i] != EOF)
	{
		readAvail->P();
		s[i] = console->GetChar();
		i++;
	}
	read_mutex->V();
}
#endif // CHANGE
