//
// Created by Wojciech Sitek on 12/11/2018.
//
#include "Buffer.hpp"

using namespace std;

char Buffer::pick() { //throws runtime_error
    if(buf.empty()){
        throw runtime_error("Empty queue");
    }
    char c = buf.front();
    buf.pop();
    return c;
}
void Buffer::add(char element){ //throws runttime_error
    if(buf.size() == capacity){
        throw runtime_error("Full queue");
    }
    buf.push(element);
}
int Buffer::getSize(){
    return buf.size();
}
string Buffer::getBuf(){
    string str;
    while( str.size() != buf.size() ){
        char c = buf.front();
        buf.pop();
        buf.push(c);
        str+=c;
    }
    return str;
}
int Buffer::getCapacity() const{
    return capacity;
}
char Buffer::getBack(){
    return buf.back();
}
