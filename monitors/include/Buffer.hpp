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



class Buffer{
public:
    Buffer(){}
    char pick();
    void add(char element);
    int getSize();
    std::string getBuf();
    int getCapacity() const;
    char getBack();
private:
    static const int capacity = BUF_NUM_ELEMENTS;
    std::queue<char> buf;
};

#endif //T3_BUFFER_HPP
