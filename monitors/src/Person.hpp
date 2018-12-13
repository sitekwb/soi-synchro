
//
// Created by Wojciech Sitek on 11/12/2018.
//

#ifndef MONITORS_PERSON_H
#define MONITORS_PERSON_H

#include <string>

#include "Buffer.hpp"

#define BUFFERS_NUM             1
#define MONITORS_NUM            1
#define CONDITIONS_NUM          2
#define MAX_JUMP                3

using namespace std;

Buffer *buffer;
Buffer &buf = *buffer;
Monitor *userMutex;
Condition *empty, *full;

class Person{
public:
    Person(const int &jump_, char functionName_, char letterName_)
    : jump(jump_), functionName(functionName_), letterName(letterName_)
    {
        currentLetter = 'a';
    }
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
    static char currentLetter;
    int jump;
    char functionName, letterName;
};

class Consumer : public Person{

public:
    Consumer(const int &&jump_, char &&letterName_)
            : Person(jump_, '-', letterName_){}

    void action(){
        //consume
        bool finish;
        while(finish){
            //enter to monitor Buffer
            buf.enter();
            //if too low number of elements => wait on full
            for(int i=0; i < this->jump+3; ++i) {
                if (buf.getSize() == i) {
                    buf.wait(*full);
                }
            }
            //pick&inform user
            for(int i=0; i< this->jump; ++i){
                char c = buf.pick();

            }
        }

    }
    static int sleepTime;
};

class Producer : public Person{
public:
    Producer(const int &&jump_, char &&letterName_)
        : Person(jump_, '+', letterName_){}

    void action(){
        //produce
        char c[MAX_JUMP], buf[3];
        bool finish;
        while(finish) {
            sleep(sleepTime);

            //initialize produced item
            for(int i=0; i< p->jump; ++i){
                c[i] = currentLetter;
                if(currentLetter++ == 'z'){
                    currentLetter = 'a';
                }
            }


            for(int i=0; i < p->jump; ++i) {
                sem_wait(&empty);
            }
            sem_wait(&mutex);

            //enter item
            for(int i=0; i < p->jump; ++i) {
                addBuf(&buffer, c[i]);
            }

            //inform about produced item
            sem_wait(&userMutex);
            for(int i=0; i < p->jump; ++i) {
                printf("%s: Produced letter: %c!\n", p->name, c[i]);
            }
            sem_post(&userMutex);

            sem_post(&mutex);


            for(int i=0; i < p->jump; ++i) {
                if(notYetConsumed) {
                    //stopping others who want to initialise full
                    sem_wait(&consumeInitMutex);
                }
                if(notYetConsumed) {
                    int semValue;
                    sem_getvalue(&consumeInitMutex, &semValue);
                    if (semValue <= 0) {
                        notYetConsumed = FALSE;
                        sem_post(&consumeInitMutex);
                    }
                }
                else{
                    sem_post(&full);
                }
            }
        }
    }
    static int sleepTime;
};
#endif //MONITORS_PERSON_H
