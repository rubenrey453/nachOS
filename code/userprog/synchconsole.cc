#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"


static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);
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
	console->PutChar(ch);
	writeDone->P();
/*
	if(character == 'c'){
		console->PutChar('<');
		writeDone->P();
		console->PutChar(character);
		writeDone->P();
		console->PutChar('>');
		writeDone->P();
	}
	else{
		console->PutChar (character);	// echo it!
		writeDone->P ();	// wait for write to finish
	}
	if (character == EOF)
		return;		// if EOF, quit
*/
}
char SynchConsole::SynchGetChar()
//char SynchConsole::SynchGetChar(int *ch)
{
	readAvail->P ();        // wait for character to arrive
	character = console->GetChar();
	return character;
}
void SynchConsole::SynchPutString(const char s[])
{
	int i;
	i=0;
	while(s[i]!='\0')
	{
		this->SynchPutChar(s[i]);
		i++;
	}
	this->SynchPutChar('\0');
}
void SynchConsole::SynchGetString(char *s, int n)
{
	int i;
	i=0;
	while(s[i]!='\0' && i<=n-1 && s[i] != EOF)
	{
		readAvail->P();
		s[i] = console->GetChar();
		i++;
	}
}
#endif // CHANGE