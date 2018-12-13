//
// Created by Wojciech Sitek on 12/11/2018.
//

#ifndef T3_BUFFER_HPP
#define T3_BUFFER_HPP

#include "Monitor.hpp"

#include <iostream>
#include <stdexcept>
#include <queue>

#define BUF_NUM_ELEMENTS        9



class Buffer : public Monitor{
public:

    char pick() { //throws runtime_error
        if(buf.empty()){
            throw std::runtime_error("Empty queue");
        }
        char c = buf.front();
        buf.pop();
        return c;
    }
    void add(char element){ //throws runttime_error
        if(buf.size() == capacity){
            throw std::runtime_error("Full queue");
        }
        buf.push(element);
    }
    int getSize(){
        return buf.size();
    }
    std::string getBuf(){
        std::string str;
        while( str.size() != buf.size() ){
            char c = buf.front();
            buf.pop();
            buf.push(c);
            str+=c;
        }
        return str;
    }
    int getCapacity() const{
        return capacity;
    }
    char getBack(){
        return buf.back();
    }
private:
    static const int capacity = BUF_NUM_ELEMENTS;
    std::queue<char>buf;
};

#endif //T3_BUFFER_HPP
