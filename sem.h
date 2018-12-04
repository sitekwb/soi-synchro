#ifndef SEMAPHORE_H
#define SEMAPHORE_H


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

#include "queue.h"

#define CONSUMER_SLEEP  1
#define PRODUCER_SLEEP  2
#define MAX_JUMP        3

sem_t mutex, empty, full, userMutex, consumeStart;

Buffer buffer;

int notFinish = TRUE, notYetConsumed = TRUE;

char currentLetter;

void *consume(person *p) {//eat one letter
    //person *p = (person *)consumer;
    char c[MAX_JUMP];

    sem_wait(&consumeStart);
    sem_post(&consumeStart);

    while(notFinish) {

        sleep(CONSUMER_SLEEP);

        for(int i=0; i<p->jump; ++i) {
            sem_wait(&full);
        }
        sem_wait(&mutex);

        //remove item
        for(int i=0; i < p->jump; ++i) {
            c[i] = pickBuf(&buffer);
        }

        sem_post(&mutex);
        sem_post(&empty);

        sem_wait(&userMutex);
        //eat item
        for(int i=0; i < p->jump; ++i) {
            printf("%s: I ate letter %c!\n", p->name, c[i]);
        }
        sem_post(&userMutex);
    }
}

void *produce(person *p){
    //person *p = (person *)producer;
    char c[MAX_JUMP], buf[3];
    while(notFinish) {
        sleep(PRODUCER_SLEEP);

        //initialize produced item
        for(int i=0; i< p->jump; ++i){
            c[i] = currentLetter;
            if(currentLetter++ == 'z'){
                currentLetter = 'a';
            }
        }


        sem_wait(&empty);
        sem_wait(&mutex);

        //enter item
        for(int i=0; i < p->jump; ++i) {
            addBuf(&buffer, c[i]);
        }

        sem_post(&mutex);

        //inform about produced item
        sem_wait(&userMutex);
        for(int i=0; i < p->jump; ++i) {
            printf("%s: Produced letter: %c!\n", p->name, c[i]);
        }
        sem_post(&userMutex);

        for(int i=0; i < p->jump; ++i) {
            sem_post(&full);
            if(notYetConsumed) {
                int fullValue;
                sem_getvalue(&full, &fullValue);
                if (fullValue >= 0) {
                    sem_post(&consumeStart);
                }
                notYetConsumed = FALSE;
            }
        }
    }
}




#endif //SEMAPHORE_H