#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"
#include <pthread.h>
#include <time.h>

/* start_routine header */
void* counter(void *);

/* Global variables */
int MAXCNT, NUMTHREADS;
counter_t count;

int main(int argc, char *argv[]) { 

    /* get the command's line parameters */
    MAXCNT = atoi(argv[1]);
    NUMTHREADS = atoi(argv[2]);

    /* Declaration of struct timeval variables */
    struct timeval ti, tf;
    time_t curtime;
    double time;
    char buffer[30];

    /* Initializing conter */
    init(&count);

    /* Threads handlers */
    pthread_t threadsArray[NUMTHREADS - 1];

    /* Time starts counting */
    gettimeofday(&ti, NULL);

    /* Creating a Threads */
    for (int i = 0; i < NUMTHREADS; i++){
        /* Thread creation */
        pthread_create(&threadsArray[i], NULL, &counter, NULL);
    }

    /* Threads joins */
    for (int i = 0; i < NUMTHREADS; i++){
        /* Threads joins */
        pthread_join(threadsArray[i], NULL);
    }

    /* Time stops counting here */
    gettimeofday(&tf, NULL);

    /* get the end time */
    curtime = tf.tv_sec;
    strftime(buffer, 30,"%T.",localtime(&curtime));
    printf("End time: %s%ld\n", buffer, tf.tv_sec);

    /* get the elapset time (end_time - start_time) */
    time = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;

    /* print the results (number threads employed, counter value, elasep time) */
    printf("Number threads employed: %d\nCounter value: %d\nElasep time: %g milisegundos\n", NUMTHREADS, get(&count), time);

    return 0;
}

/* start_routine definition */
void* counter(void * noArg){
    for (int i = 0; i < MAXCNT; i++){
        increment(&count);
    }
    return NULL;
}
