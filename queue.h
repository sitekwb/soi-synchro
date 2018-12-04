//
// Created by Wojciech Sitek on 30/11/2018.
//

#ifndef T3_QUEUE_H
#define T3_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define PERSON_NUMBER           4
#define BUF_NUM_ELEMENTS        9

#define TRUE                    1
#define FALSE                   0

typedef struct person{
    int jump;
    char name[10];
}person;

typedef person* Person;

typedef struct Buffer{
    int capacity;
    int size;
    int front;
    int rear;
    char elements[BUF_NUM_ELEMENTS];
}Buffer;
void initBuf(Buffer *Q){
    Q->size = 0;
    Q->capacity = BUF_NUM_ELEMENTS;
    Q->front = 0;
    Q->rear = -1;
}
char pickBuf(Buffer *Q) {
    if(Q->size==0){
        return NULL;
    }
    --Q->size;
    char p = Q->elements[Q->front++];
    if(Q->front==Q->capacity){
        Q->front=0;
    }
    return p;
}
void addBuf(Buffer *Q,char element){
    if(Q->size == Q->capacity){
        printf("Critical error!");
        return;
    }
    ++Q->size;
    ++Q->rear;
    if(Q->rear == Q->capacity){
        Q->rear = 0;
    }
    Q->elements[Q->rear] = element;
}
#endif //T3_QUEUE_H
