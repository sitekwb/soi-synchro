//
// Created by Wojciech Sitek on 14/12/2018.
//

#include "Consumer.hpp"


using namespace std;

void Consumer::action(){
    //consume
    while(true){
        sleep(sleepTime);
        //enter to monitor Buffer
        monitor->enter();
        //cout<<functionName<<' '<<letterName<<" MONITOR"<<endl;
        //if too low number of elements => wait on full
        for(int i=0; i < this->jump+MIN_LETTERS_TO_CONSUME; ++i) {
            if (buffer->getSize() == i) {
                std::cout<<functionName<<' '<<letterName<< \
                " waiting for "<<jump+MIN_LETTERS_TO_CONSUME-i<<" places to consume"<<std::endl;
                monitor->wait(*full);
                cout<<"[U]  "<<functionName<<' '<<letterName<<endl;
            }
        }
        //pick&inform user
        for(int i=1; i <= this->jump; ++i){
            cout<<"[X1]"<<endl;
            char c = buffer->pick();
            cout<<"[X2]"<<endl;
            std::cout<<functionName<<' '<<letterName<<' '<<i<<'/'<<jump<<' ';
            cout<<c<<' '<<buffer->getSize()<<' '<<buffer->getBuf()<<std::endl;
        }
        //signal(empty) = If no one was waiting, switch off light
        if(!monitor->signal(*empty)) {
            monitor->leave();
        }
    }

}