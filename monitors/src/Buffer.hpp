//
// Created by Wojciech Sitek on 12/11/2018.
//

#ifndef T3_BUFFER_HPP
#define T3_BUFFER_HPP

#include "Monitor.hpp"

#include <iostream>
#include <stdexcept>

#define BUF_NUM_ELEMENTS        9



class Buffer : public Monitor{

public:

    Buffer() : size(0), capacity(BUF_NUM_ELEMENTS), front(0), rear(-1) {}

    char pick() { //throws runtime_error
        if(size==0){
            throw std::runtime_error("");
        }
        --size;
        char p = elements[front++];
        if(front==capacity){
            front=0;
        }
        return p;
    }
    void add(char element){ //throws runttime_error
        if(size == capacity){
            throw std::runtime_error("Full buffer!");
        }
        ++size;
        ++rear;
        if(rear == capacity){
            rear = 0;
        }
        elements[rear] = element;
    }
    int getSize(){
        return size;
    }
    std::string getBuf(){
        std::string buf;
        int p = front;
        if(front < rear){
            
        }
    }
private:
    int capacity;
    int size;
    int front;
    int rear;
    char elements[BUF_NUM_ELEMENTS];
};

#endif //T3_BUFFER_HPP
