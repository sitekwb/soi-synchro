//
// Created by Wojciech Sitek on 14/12/2018.
//

#include "Producer.hpp"



using namespace std;



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
        //cout<<functionName<<letterName<<" Entering to buffer."<<endl; TODO
        cout<<functionName<<' '<<letterName;
        monitor->enter();
        //cout<<functionName<<letterName<<" Entered to buffer."<<endl; TODO
        //if too much elements => wait till is more EMPTY
        for(int i=0; i < this->jump; ++i) {
            if (buffer->getSize() == buffer->getCapacity() - i) {
                // I'll be waiting <= inform user
                std::cout<<functionName<<letterName<<" waiting for "<<jump-i<<" places to produce"<<std::endl;
                //wait
                cout<<functionName<<' '<<letterName;
                monitor->wait(*empty);
                cout<<"[U]  "<<functionName<<' '<<letterName<<endl;
            }
        }
        //add&inform user
        for(int i=1; i <= this->jump; ++i){
            buffer->add(currentLetter++);
            std::cout<<functionName<<' '<<letterName<<' '<<i<<'/'<<jump<<' '  \
                <<buffer->getBack()<<' '<<buffer->getSize()<<' '<<buffer->getBuf()<<std::endl;
        }

        cout<<functionName<<' '<<letterName;
        monitor->signal(*full);
        //signal(full) = Hello! I emptied a few places, before there wasn't any!
    }
}