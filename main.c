//
// Created by Wojciech Sitek on 30/11/2018.
//
#include "semaphore.h"
#include <pthread.h>
#include <string.h>

person *caPerson, *cbPerson, *paPerson, *pbPerson;

int main(){
    setbuf(stdout, 0);
    initQueue_char(&buffer);
    pthread_t caThread, cbThread, paThread, pbThread;


    //INITIALIZE VAR VALUES
    caPerson = (person *)malloc(sizeof(person));
    caPerson->jump = 1;
    strcpy(caPerson->name, "ConsumerA");

    cbPerson = (person *)malloc(sizeof(person));
    cbPerson->jump = 2;
    strcpy(cbPerson->name, "ConsumerB");

    paPerson = (person *)malloc(sizeof(person));
    paPerson->jump = 1;
    strcpy(paPerson->name, "ProducerA");

    pbPerson = (person *)malloc(sizeof(person));
    pbPerson->jump = 3;
    strcpy(pbPerson->name, "ProducerB");


    //INIT OF SEMAPHORS
    mutex.jump = 1;
    mutex.v = 1;
    initQueue_Person(&mutex.q);
    mutex.id = ID_MUTEX;

    userMutex.jump = 1;
    userMutex.v = 1;
    initQueue_Person(&userMutex.q);
    userMutex.id = ID_USERMUTEX;

    empty.jump = 0;
    empty.v = BUF_NUM_ELEMENTS; //how many places are empty
    initQueue_Person(&empty.q);
    empty.id = ID_EMPTY;

    full.jump = 0;
    full.v  = 0;                //how many places are full
    initQueue_Person(&full.q);
    full.id = ID_FULL;

    finish.jump = 1;
    finish.v = TRUE;
    finish.id = ID_FINISH;

    //RUN THREADS
    int retCA = pthread_create( &caThread, NULL, consume, (void *)(caPerson));
    if(retCA){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",retCA);
        exit(EXIT_FAILURE);
    }

    int retCB = pthread_create( &cbThread, NULL, consume, (void *)(cbPerson));
    if(retCB){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",retCB);
        exit(EXIT_FAILURE);
    }

    int retPA = pthread_create( &paThread, NULL, produce, (void *)(paPerson));
    if(retPA){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",retPA);
        exit(EXIT_FAILURE);
    }

    int retPB = pthread_create( &pbThread, NULL, produce, (void *)(pbPerson));
    if(retPB){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",retPB);
        exit(EXIT_FAILURE);
    }

    pthread_join( caThread, NULL);
    pthread_join( cbThread, NULL);
    pthread_join( paThread, NULL);
    pthread_join( pbThread, NULL);

    exit(EXIT_SUCCESS);
}