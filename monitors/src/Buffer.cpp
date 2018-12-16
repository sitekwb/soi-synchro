//
// Created by Wojciech Sitek on 12/11/2018.
//
#include "Buffer.hpp"

using namespace std;

char Buffer::pick() { //throws runtime_error
    char c;
    //cout<<"[Y1]"<<endl;
    if(buf.empty()){
        throw runtime_error("Empty queue");
    }
    //cout<<"[Y2]"<<endl;
    c = buf.front();
    //cout<<"[Y3]"<<endl;
    buf.pop();
    //cout<<"[Y4]"<<endl;
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
        //cout<<"[Z1]"<<endl;
        char c;
        c = buf.front();
        //cout<<"[Z2]"<<c<<endl;
        buf.pop();
        buf.push(c);
        str+=c;
        //cout<<"[Z3]"<<str<<endl;
    }
    return str;
}
int Buffer::getCapacity() const{
    return capacity;
}
char Buffer::getBack(){
    return buf.back();
}
