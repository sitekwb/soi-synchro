//
// Created by Wojciech Sitek on 14/12/2018.
//

#include "Producer.hpp"


extern Condition *full, *empty;
extern Buffer *buffer;



Producer::Producer(const int jump_, char letterName_, int sleepTime_)
: Person(jump_, '+', letterName_, sleepTime_)
{
    currentLetter = 'a';
}

void Producer::action(){
    //produce
    while(true){
        sleep(sleepTime);
        //enter to monitor Buffer
        buffer->enter();
        //if too much elements => wait till is more EMPTY
        for(int i=0; i < this->jump; ++i) {
            if (buffer->getSize() == buffer->getCapacity() - i) {
                // I'll be waiting <= inform user
                std::cout<<functionName<<letterName<<" waiting for "<<jump-i<<" places"<<std::endl;
                //wait
                buffer->wait(*empty);
            }
        }
        //add&inform user
        for(int i=1; i <= this->jump; ++i){
            buffer->add(currentLetter++);
            std::cout<<functionName<<' '<<letterName<<' '<<i<<'/'<<jump<<' '  \
                <<buffer->getBack()<<' '<<buffer->getSize()<<' '<<buffer->getBuf()<<std::endl;
        }
        //signal(empty) = Hello! I emptied a few places, before there wasn't any!
        if( buffer->getSize() + jump == buffer->getCapacity() ){
            buffer->leave();
            buffer->signal(*full);
        }
        else{
            buffer->leave();
        }
    }
}