# SEMAPHORE SOI PROJECT

Project implements consumer-producer problem in C language using threads from <pthread.h> and semaphors from <semaphore.h>.
##1. Parameters:
	- producers/consumers are operating on characters buffer with capacity of 9
	- there are two producers and two consumers (consuming/producing one or more letters at once)
	- after each consumption there should be at least 3 letters in buffer.
##2. Solutions:
	- structure Buffer implemented as a cycled queue with 'methods' to get front, pick element or add element 
	- different semaphors used:
		- binary semaphore *mutex*
		- binary semaphore *userMutex*
		- counting semaphore *consumeInitMutex* - when producer produces third letter, they enter in their critical section and raises binary flag *notYetConsumed* to false, allowing next producers to raise *full* semaphore 
		- counting semaphore *empty* (indicating how many places are left empty in buffer)
		- counting semaphore *full* (indicating how many places are full and ready to be consumed)
	- four additional threads imitating four people - 2 consumers and 2 producers and one main thread which finishes program running after time indicated by user in program arguments.
 
##1. Instruction:
```
$ make
```
##2. Execute program:
```
$ ./prog [*time-of-work*] [*producer-sleep-time*] [*consumer-sleep-time*] [>*output/file/path*]
```
If *time-of-work* is not specified, program will work for 30 seconds. But if sleep-times will not be specified, producer and consumer will work instantly.



