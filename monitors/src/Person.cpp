
//
// Created by Wojciech Sitek on 11/12/2018.
//

#include "Person.hpp"

using namespace std;


char Letter::operator++(){
    c = (c=='z')?'a':(c+1);
    return c;
}
char Letter::operator++(int){
    char tmp = c;
    operator++();
    return tmp;
}
char Letter::operator*(){
    return c;
}
void Letter::operator=(char nLetter){
    c = nLetter;
}

int Person::getJump(){
    return jump;
}
char Person::getFunction(){
    return functionName;
}
char Person::getLetterName(){
    return letterName;
}

void Consumer::action(){
    //consume
    while(true){
        sleep(sleepTime);
        //enter to monitor Buffer
        buf.enter();
        //if too low number of elements => wait on full
        for(int i=0; i < this->jump+MIN_LETTERS_TO_CONSUME; ++i) {
            if (buf.getSize() == i) {
                std::cout<<functionName<<letterName<< \
                " waiting for "<<jump+MIN_LETTERS_TO_CONSUME-i<<" places"<<std::endl;
                buf.wait(*full);
            }
        }
        //pick&inform user
        for(int i=1; i <= this->jump; ++i){
            char c = buf.pick();
            std::cout<<functionName<<' '<<letterName<<' '<<i<<'/'<<jump<<' ' \
                <<c<<' '<<buf.getSize()<<' '<<buf.getBuf()<<std::endl;
        }
        //signal(empty) = Hello! I emptied a few places!
        if( buf.getSize() + jump == buf.getCapacity() ){
            buf.leave();
            buf.signal(*empty);
        }
        else{
            buf.leave();
        }
    }

}


void Producer::action(){
    //produce
    while(true){
        sleep(sleepTime);
        //enter to monitor Buffer
        buf.enter();
        //if too much elements => wait till is more EMPTY
        for(int i=0; i < this->jump; ++i) {
            if (buf.getSize() == buf.getCapacity() - i) {
                // I'll be waiting <= inform user
                std::cout<<functionName<<letterName<<" waiting for "<<jump-i<<" places"<<std::endl;
                //wait
                buf.wait(*empty);
            }
        }
        //add&inform user
        for(int i=1; i <= this->jump; ++i){
            buf.add(currentLetter++);
            std::cout<<functionName<<' '<<letterName<<' '<<i<<'/'<<jump<<' '  \
                <<buf.getBack()<<' '<<buf.getSize()<<' '<<buf.getBuf()<<std::endl;
        }
        //signal(empty) = Hello! I emptied a few places, before there wasn't any!
        if( buf.getSize() + jump == buf.getCapacity() ){
            buf.leave();
            buf.signal(*empty);
        }
        else{
            buf.leave();
        }
    }
}