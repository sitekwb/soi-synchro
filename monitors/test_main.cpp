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
#include "Producer.hpp"
#include "Consumer.hpp"

extern Condition *full, *empty;
extern Buffer *buffer;


using namespace boost::interprocess;

int main (int argc, char **argv)
{

    auto person = new Consumer(1, 'A', (argc==4)?atoi(argv[3]):0);


    shared_memory_object::remove("Memory");
    try{
        //allocate memory and buffer and monitors objects
        //shared_memory_object segment(create_only, "Memory", read_write);

        managed_shared_memory segment(create_only, "Memory", 100*(BUFFERS_NUM*sizeof(Buffer) + CONDITIONS_NUM*sizeof(Condition)));

        std::queue<char> *queue = segment.construct<std::queue<char>>("Queue")();
        buffer = segment.construct<Buffer>("Buf")(queue);
        empty = segment.construct<Condition>("empty")();
        full = segment.construct<Condition>("full")();
        monitor = segment.construct<Monitor>("Monitor")();
        for(char i='a'; i<'a'+4; ++i)
            buffer->add(i);

        person->action();

        int pid = fork();
        if(pid == 0){
            while(1){
                sleep(1);
                monitor->enter();
                std::cout<<"Enter action: ";
                char x;
                std::cin>>x;
                if(x=='a'){
                    buffer->add('a');
                }
                else if(x=='p'){
                    buffer->pick();
                }
                else if(x=='q'){
                    exit(0);
                }
            }
        }
        //create child processes performing their actions
                person->action();
    }
    catch(const std::runtime_error& re)
    {
        std::cout << "Runtime error: " << re.what() << std::endl;
    }
    catch(const interprocess_exception& ie){
        std::cout << "Interprocess exception: " << ie.what() << std::endl;
    }
    //catch(...){
    //  std::cout << "Unknown error! Exiting." << std::endl;
    //}
    //kill processes and exit

    shared_memory_object::remove("MySharedMemory");
    return 0;
}
//
// Created by Wojciech Sitek on 16/12/2018.
//

