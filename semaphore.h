#ifndef SEMAPHORE_H
#define SEMAPHORE_H


#include <stdio.h>
#include <string.h>
#include "queue.h"

#define MAX_JUMP        3

//defines id of semaphors
#define ID_MUTEX        0
#define ID_EMPTY        1
#define ID_FULL         2
#define ID_USERMUTEX    3


typedef struct semaphore{
    int v;
    int jump; //overwrites person jump if not 0
    int id;
    int raise;
    Queue_Person q;
}semaphore;

Queue_char buffer;

semaphore mutex, empty, full, userMutex;

void down(semaphore *s, person *p){
    s->v -= s->jump;

    if(!s->jump){//if semaphore didn't overwritten person jump
        s->v -= p->jump;
    }

    if(s->v < 0){
        add_queue_Person( &(s->q), p);
        p->cantPass[s->id] = TRUE;
        while(p->cantPass[s->id]){}
    }
}
void up(semaphore *s, person *p)
{
    s->v += s->jump;
    s->raise += s->jump;
    if(!s->jump){//if semaphore didn't overwritten person jump
        s->v += p->jump;
        s->raise += p->jump;
    }

    if(s == &full){

    }
    person *wokenPerson;
    if( ( wokenPerson = front_queue_Person(&s->q) ) && (s->jump!=0 || wokenPerson->jump <= s->raise) ){
        s->raise -= (s->jump==0) ? wokenPerson->jump : s->jump;
        pick_queue_Person(&s->q);
        wokenPerson->cantPass[s->id] = FALSE;
    }
}

void *consume(person *p) {//eat one letter
    //person *p = (person *)consumer;
    char c[MAX_JUMP];
    while(TRUE) {
        down(&full, p);
        down(&mutex, p);

        //remove item
        for(int i=0; i < p->jump; ++i) {
            c[i] = pick_queue_char(&buffer);
        }

        up(&mutex, p);
        up(&empty, p);

        down(&userMutex, p);
        //eat item
        for(int i=0; i < p->jump; ++i) {
            printf("%s: I ate letter %c!\n", p->name, c[i]);
        }
        up(&userMutex, p);
    }
}

void *produce(person *p){
    //person *p = (person *)producer;
    char c[MAX_JUMP], buf[3];
    while(TRUE) {
        down(&userMutex, p);
        //ask user for producing item
        for(int i=0; i < p->jump; ++i) {
            printf("%s: Please, enter letter no. %d to produce: ", p->name, i+1);
            scanf("%2c", buf);
            if(strcmp(buf, "ZZ") == 0){
                exit(EXIT_SUCCESS);
            }
            char tmp = buf[0];
            c[i] = tmp;
        }
        up(&userMutex, p);


        down(&empty, p);
        down(&mutex, p);

        //enter item
        for(int i=0; i < p->jump; ++i) {
            add_queue_char(&buffer, c[i]);
        }

        up(&mutex, p);
        up(&full, p);
    }
}




#endif //SEMAPHORE_H