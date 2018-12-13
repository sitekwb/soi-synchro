//
// Created by Wojciech Sitek on 11/12/2018.
//

//boost shared memory
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

//fork
#include <sys/types.h>

//kill
#include <signal.h>

//classes
#include "Person.hpp"


int main (int argc, char **argv)
{
    int pid[4];
    Person *person[4];
    person[0] = new Consumer(1, 'A');
    person[1] = new Consumer(2, 'B');
    person[2] = new Producer(1, 'A');
    person[3] = new Producer(3, 'B');

    using namespace boost::interprocess;

    shared_memory_object::remove("MySharedMemory");
    try{
        //allocate memory and buffer and monitors objects
        //shared_memory_object segment(create_only, "Memory", read_write);

        managed_shared_memory segment(create_only, "Memory",
            BUFFERS_NUM*sizeof(Buffer) + CONDITIONS_NUM*sizeof(Condition));

        buffer = segment.construct<Buffer>("Buf")();
        empty = segment.construct<Condition>("empty")();
        full = segment.construct<Condition>("full")();

        //initialize time to sleep before each action
        Consumer::sleepTime = (argc==4)?atoi(argv[2]):0;
        Producer::sleepTime = (argc==4)?atoi(argv[3]):0;

        //create child processes performing their actions
        for(int i=0; i<4; ++i){
            pid[i] = fork();
            if(pid[i] == 0){//I am child
                    person[i]->action();
            }
        }
        //sleep waiting for result of people work
        sleep((argc>1)?atoi(argv[1]):30);
    }
    catch(const std::runtime_error& re)
    {
        std::cout << "Runtime error: " << re.what() << std::endl;
    }
    catch(...){
        std::cout << "Unknown error! Exiting." << std::endl;
    }
    //kill processes and exit
    for(int i=0; i<4; ++i){
        kill(pid[i], SIGKILL);
    }
    shared_memory_object::remove("MySharedMemory");
    return 0;
}
