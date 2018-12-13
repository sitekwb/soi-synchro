
//
// Created by Wojciech Sitek on 11/12/2018.
//

#ifndef MONITORS_PERSON_H
#define MONITORS_PERSON_H

#include <string>

#include "Buffer.hpp"

#define BUFFERS_NUM             1
#define CONDITIONS_NUM          2
#define MIN_LETTERS_TO_CONSUME  3

using namespace std;

Buffer *buffer;
Buffer &buf = *buffer;
Condition *empty, *full;


struct Letter{
    char c;
    char operator++(){
        c = (c=='z')?'a':(c+1);
        return c;
    }
    char operator++(int){
        char tmp = c;
        operator++();
        return tmp;
    }
    char operator*(){
        return c;
    }
    void operator=(char nLetter){
        c = nLetter;
    }
};




class Person{
public:
    Person(const int &jump_, char functionName_, char letterName_)
    : jump(jump_), functionName(functionName_), letterName(letterName_) {}

    int getJump(){
        return jump;
    }
    char getFunction(){
        return functionName;
    }
    char getLetterName(){
        return letterName;
    }
    virtual void action() = 0;

protected:
    int jump;
    char functionName, letterName;
};

class Consumer : public Person{

public:
    Consumer(const int &&jump_, char &&letterName_)
            : Person(jump_, '-', letterName_){}

    void action(){
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
    static int sleepTime;
};

class Producer : public Person{
public:
    Producer(const int &&jump_, char &&letterName_) : Person(jump_, '+', letterName_){
        currentLetter = 'a';
    }

    void action(){
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
    static int sleepTime;
private:
    static Letter currentLetter;
};
#endif //MONITORS_PERSON_H
