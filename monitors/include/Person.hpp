
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


Buffer *buffer;
Buffer &buf = *buffer;
Condition *empty, *full;


struct Letter{
    char c;
    char operator++();
    char operator++(int);
    char operator*();
    void operator=(char nLetter);
};

class Person{
public:
    Person(const int &jump_, char functionName_, char letterName_)
    : jump(jump_), functionName(functionName_), letterName(letterName_){}

    int getJump();
    char getFunction();
    char getLetterName();
    virtual void action() = 0;

protected:
    int jump;
    char functionName, letterName;
};

class Consumer : public Person{

public:
    Consumer(const int &&jump_, char &&letterName_, int sleepTime_)
    : Person(jump_, '-', letterName_)
    {
        sleepTime = sleepTime_;
    }

    void action();
    static int sleepTime;
};

class Producer : public Person{
public:
    Producer(const int &&jump_, char &&letterName_, int sleepTime_)
    : Person(jump_, '+', letterName_)
    {
        currentLetter = 'a';
        sleepTime = sleepTime_;
    }

    void action();
    static int sleepTime;
private:
    static Letter currentLetter;
};
#endif //MONITORS_PERSON_H
