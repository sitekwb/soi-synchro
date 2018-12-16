#include "Monitor.hpp"


#include <iostream>//for a while TODO
using namespace boost::interprocess;

Semaphore::Semaphore( unsigned int value ) : sem(value){}
Semaphore::~Semaphore() {}

void Semaphore::p()
{
	sem.wait();
}

void Semaphore::v()
{
	sem.post();
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
	std::cout<<"[W]"<<std::endl;
	s.p();
	std::cout<<"[E]"<<std::endl;
}

void Monitor::leave()
{
    std::cout<<"[L]"<<std::endl;
	s.v();
}

void Monitor::wait( Condition & cond )
{
	++ cond.waitingCount;
	leave();
	cond.wait();
}

bool Monitor::signal( Condition & cond )
{
    return cond.signal();
}


