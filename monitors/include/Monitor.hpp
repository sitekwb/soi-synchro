#ifndef __monitor_h
#define __monitor_h

#include <stdio.h> 
#include <stdlib.h> 

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h> 
#include <sys/stat.h> 
#include <string.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <pthread.h> 
#include <unistd.h>
#include <semaphore.h>

#endif

class Semaphore
{
public:

  Semaphore( int value );
  ~Semaphore();

  void p();

  void v();
  

private:

#ifdef _WIN32
	HANDLE sem;
#else
	sem_t sem;
#endif
};

class Condition
{
  friend class Monitor;

public:
	Condition() : w( 0 ){
        waitingCount = 0;
	}

	void wait();

	bool signal();

private:
	Semaphore w;
	int waitingCount;
};


class Monitor
{
public:
	Monitor() : s( 1 ) {}

	void enter();

	void leave();

	void wait( Condition & cond );

	void signal( Condition & cond );


private:
	Semaphore s;
};

#endif

