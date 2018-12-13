#include "Monitor.hpp"

Semaphore::Semaphore( int value )
{
#ifdef _WIN32
sem = CreateSemaphore( NULL, value, 1, NULL );
#else
 if( sem_init( & sem, 0, value ) != 0 )
   throw "sem_init: failed";
#endif
}
Semaphore::~Semaphore()
{
#ifdef _WIN32
CloseHandle( sem );
#else
  sem_destroy( & sem );
#endif
}

void Semaphore::p()
{
#ifdef _WIN32
  WaitForSingleObject( sem, INFINITE );
#else
 if( sem_wait( & sem ) != 0 )
   throw "sem_wait: failed";
#endif
}

void Semaphore::v()
{
#ifdef _WIN32
  ReleaseSemaphore( sem, 1, NULL );
#else
 if( sem_post( & sem ) != 0 )
   throw "sem_post: failed";
#endif
}



void Condition::wait()
{
	w.p();
}

bool Condition::signal()
{
	if( waitingCount )
	{
		-- waitingCount;
		w.v();
		return true;
	}//if
	else
		return false;
}



void Monitor::enter()
{
	s.p();
}

void Monitor::leave()
{
	s.v();
}

void Monitor::wait( Condition & cond )
{
	++ cond.waitingCount;
	leave();
	cond.wait();
}

void Monitor::signal( Condition & cond )
{
	if( cond.signal() )
		enter();
}


