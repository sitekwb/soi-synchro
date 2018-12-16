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
	sharable_lock<interprocess_mutex> lock(mutex);
	std::cout<<"[C]"<<std::endl;
	cond.wait(lock);
	std::cout<<"[O]"<<std::endl;
}

void Condition::signal()
{
	std::cout<<"[N]"<<std::endl;
	cond.notify_one();
	std::cout<<"[ND]"<<std::endl;

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
	leave();
	cond.wait();
	enter();
}

void Monitor::signal( Condition & cond )
{
    cond.signal();
}


