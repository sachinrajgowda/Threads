//Threads in C

/* Includes */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */

int flag1,flag2; //2 shared variables, with initial values to be 0(false)

void execute1(); //thread1 process
void execute2(); //thread2 process

int main()
{
    pthread_t thread1, thread2;  // thread variables
    // create threads 1 and 2   
    pthread_create (&thread1, NULL, (void *) &execute1, NULL);
    pthread_create (&thread2, NULL, (void *) &execute2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
              
    exit(0);
}

void execute1() 
{
    int i=0;
    while(i<10)
    {
        printf("\nTHREAD1 \tinitial value of flag1: %d, flag2:%d",flag1,flag2);        //it will print before updating the shared variable
        flag1 = 1;                                                                     //setting flag1 value to true
        while(flag2);                                                                  //empty body
        printf("\nThread1 \tentering critical section: (flag1 value: %d, flag2 value: %d)", flag1,flag2);
        i++;
        flag1 = 0;                                                                     //setting falg1 value to false
        printf("\nThread1 \tentering non critical section: (flag1 value: %d, flag2 value: %d)\n\n", flag1,flag2);
    }
    pthread_exit(0);
}


void execute2()
{
    int i=0;
    while(i<10)
    {
        printf("\nTHREAD2 \tinitial value of flag1: %d, flag2:%d",flag1,flag2);        //it will print before updating the shared variable
        flag2 = 1;                                                                     //setting flag2 value to true
        while(flag1);                                                                  //empty body
        printf("\nThread2 \tentering critical section: (flag1 value: %d, flag2 value: %d)", flag1,flag2);
        i++;
        flag2 = 0;                                                                     //setting flag2 value to false
        printf("\nThread2 \tentering non critical section: (flag1 value: %d, flag2 value: %d)\n\n", flag1,flag2);
    }
    pthread_exit(0);
}

