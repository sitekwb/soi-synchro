
//
// Created by Wojciech Sitek on 11/12/2018.
//

#ifndef MONITORS_PERSON_H
#define MONITORS_PERSON_H

Buffer *buffer;
Monitor *mutex, *userMutex, *empty, *consumeInitMutex, *full;

virtual class Person{
public:
    Person(int jump_, std::string name_) : jump(jump_), name(name_), currentLetter('a'){}
    int getJump(){
        return jump;
    }
    string getName(){
        return name;
    }
    virtual void action() = 0;
private:
    int jump;
    string name;
};

class Consumer : public Person{
    static char currentLetter;
public:
    void action(){
        //consume
        char c[MAX_JUMP];


        while(notFinish) {

            sleep(sleep);

            for(int i=0; i<p->jump; ++i) {
                full->
                sem_wait(&full);
            }
            sem_wait(&mutex);

            //remove item
            for(int i=0; i < p->jump; ++i) {
                c[i] = pickBuf(&buffer);
            }

            sem_wait(&userMutex);
            //eat item
            for(int i=0; i < p->jump; ++i) {
                printf("%s: I ate letter %c!\n", p->name, c[i]);
            }
            sem_post(&userMutex);

            sem_post(&mutex);
            for(int i=0; i < p->jump; ++i) {
                sem_post(&empty);
            }
        }
    }
    static int sleep;
};

class Producer : public Person{
public:
    void action(){
        //produce
        char c[MAX_JUMP], buf[3];
        while(true) {
            sleep(sleep);

            //initialize produced item
            for(int i=0; i< p->jump; ++i){
                c[i] = currentLetter;
                if(currentLetter++ == 'z'){
                    currentLetter = 'a';
                }
            }


            for(int i=0; i < p->jump; ++i) {
                sem_wait(&empty);
            }
            sem_wait(&mutex);

            //enter item
            for(int i=0; i < p->jump; ++i) {
                addBuf(&buffer, c[i]);
            }

            //inform about produced item
            sem_wait(&userMutex);
            for(int i=0; i < p->jump; ++i) {
                printf("%s: Produced letter: %c!\n", p->name, c[i]);
            }
            sem_post(&userMutex);

            sem_post(&mutex);


            for(int i=0; i < p->jump; ++i) {
                if(notYetConsumed) {
                    //stopping others who want to initialise full
                    sem_wait(&consumeInitMutex);
                }
                if(notYetConsumed) {
                    int semValue;
                    sem_getvalue(&consumeInitMutex, &semValue);
                    if (semValue <= 0) {
                        notYetConsumed = FALSE;
                        sem_post(&consumeInitMutex);
                    }
                }
                else{
                    sem_post(&full);
                }
            }
        }
    }
    static int sleep;
};
#endif //MONITORS_PERSON_H
