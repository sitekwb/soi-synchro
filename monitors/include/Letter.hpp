//
// Created by Wojciech Sitek on 14/12/2018.
//

#ifndef MONITORS_LETTER_H
#define MONITORS_LETTER_H



struct Letter{
    char c;
    char operator++();
    char operator++(int);
    char operator*();
    void operator=(char nLetter);
};



#endif //MONITORS_LETTER_H
