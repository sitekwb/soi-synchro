//
// Created by Wojciech Sitek on 14/12/2018.
//

#include "Consumer.hpp"

extern Condition *full, *empty;
extern Buffer *buffer;


void Consumer::action(){
    //consume
    while(true){
        sleep(sleepTime);
        //enter to monitor Buffer
        buffer->enter();
        //if too low number of elements => wait on full
        for(int i=0; i < this->jump+MIN_LETTERS_TO_CONSUME; ++i) {
            if (buffer->getSize() == i) {
                std::cout<<functionName<<letterName<< \
                " waiting for "<<jump+MIN_LETTERS_TO_CONSUME-i<<" places"<<std::endl;
                buffer->wait(*full);
            }
        }
        //pick&inform user
        for(int i=1; i <= this->jump; ++i){
            char c = buffer->pick();
            std::cout<<functionName<<' '<<letterName<<' '<<i<<'/'<<jump<<' ' \
                <<c<<' '<<buffer->getSize()<<' '<<buffer->getBuf()<<std::endl;
        }
        //signal(empty) = Hello! I emptied a few places!
        if( buffer->getSize() + jump == buffer->getCapacity() ){
            buffer->leave();
            buffer->signal(*empty);
        }
        else{
            buffer->leave();
        }
    }

}