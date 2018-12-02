//
// Created by Wojciech Sitek on 30/11/2018.
//

#ifndef T3_QUEUE_H
#define T3_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define PERSON_NUMBER           4
#define BUF_NUM_ELEMENTS        9
#define SEMAPHORES_NUM          5

#define TRUE                    1
#define FALSE                   0

typedef struct person{
    int cantPass[SEMAPHORES_NUM];
    int jump;
    char name[10];
}person;

typedef person* Person ;

#define QUEUE_TEMPLATE(TYPE, CAPACITY)              \
typedef struct Queue_##TYPE{                        \
    int capacity;                                   \
    int size;                                       \
    int front;                                      \
    int rear;                                       \
    TYPE elements[CAPACITY];                        \
}Queue_##TYPE;                                      \
void initQueue_##TYPE(Queue_##TYPE *Q){             \
    Q->size = 0;                                    \
    Q->capacity = CAPACITY;                         \
    Q->front = 0;                                   \
    Q->rear = -1;                                   \
}                                                   \
TYPE front_queue_##TYPE(Queue_##TYPE *Q) {          \
    if(Q->size==0){                                 \
        return NULL;                                \
    }                                               \
    return Q->elements[Q->front];                   \
}                                                   \
TYPE pick_queue_##TYPE(Queue_##TYPE *Q) {           \
    if(Q->size==0){                                 \
        return NULL;                                \
    }                                               \
    --Q->size;                                      \
    TYPE p = Q->elements[Q->front++];               \
    if(Q->front==Q->capacity){                      \
        Q->front=0;                                 \
    }                                               \
    return p;                                       \
}                                                   \
void add_queue_##TYPE(Queue_##TYPE *Q,TYPE element){\
    if(Q->size == Q->capacity){                     \
        printf("Critical error!");                  \
        return;                                     \
    }                                               \
    ++Q->size;                                      \
    ++Q->rear;                                      \
    if(Q->rear == Q->capacity){                     \
        Q->rear = 0;                                \
    }                                               \
    Q->elements[Q->rear] = element;                 \
}                                                   \

QUEUE_TEMPLATE(Person, PERSON_NUMBER);
QUEUE_TEMPLATE(char, BUF_NUM_ELEMENTS);

#endif //T3_QUEUE_H
