
//
// Created by Wojciech Sitek on 11/12/2018.
//

#include "Person.hpp"

using namespace std;

Buffer *buffer;
Condition *empty, *full;
Monitor *monitor;


int Person::getJump(){
    return jump;
}
char Person::getFunction(){
    return functionName;
}
char Person::getLetterName(){
    return letterName;
}

