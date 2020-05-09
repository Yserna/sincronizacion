#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "concurrent_linked_list.h"
#include <string.h>
#include <time.h>

void* initialize_book_list(list_t *l);
void* book_lending(void * office);

list_t* books;
pthread_mutex_t lock;
int TOTAL_LOANS_SUCCESS = 0, TOTAL_LOANS_FAILURE = 0, TOTAL_BOOKS = 10000, NUMTHREADS = 4;

int main(int argc, char *argv[]) { 
    office_l * loansOffice[4];
    pthread_t threads[NUMTHREADS];
    struct timeval ti, tf;
    double time;

    List_Init(&books);

    gettimeofday(&ti, NULL);

    initialize_book_list(&books);

    for(int i = 0; i < NUMTHREADS; i++){
        office_l * office = malloc(sizeof(office_l));
        office->id = i;
        office->seed = (int)rand();        
        office->successful_loan = 0;
        office->failed_loan = 0;
        loansOffice[i] = office;
        printf("my id %d, my seed %d\n", i, office->seed);
        pthread_create(&threads[i], NULL, &book_lending, office);
    }

    for (int i = 0; i < NUMTHREADS; i++){
        pthread_join(threads[i], NULL);
        printf("Office %d has finished its workload, successful loans %d, failed loans %d\n",i,loansOffice[i]->successful_loan,loansOffice[i]->failed_loan);
        TOTAL_LOANS_SUCCESS = TOTAL_LOANS_SUCCESS + loansOffice[i]->successful_loan;
        TOTAL_LOANS_FAILURE = TOTAL_LOANS_FAILURE + loansOffice[i]->failed_loan;
    }

    gettimeofday(&tf, NULL);
    time = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;

    printf("Simulation done! execution time: %.2f ms\n", time);
    printf("Total successful loans %d, total failed loans %d\n", TOTAL_LOANS_SUCCESS, TOTAL_LOANS_FAILURE);
    printf("Number of remaining available books %d\n", (TOTAL_BOOKS-TOTAL_LOANS_SUCCESS));
    return 0;
}

void* initialize_book_list(list_t *l){
    printf("Initializing list of available books\n");
    for (int i = 0; i < 10000; i++){
        char buffer[10];
        Book * book = (Book*) malloc(sizeof(Book));
        sprintf(buffer, "book_%d", i);
        book->id = i;
        book->name = buffer;
        book->num_pages = 100;
        book->pub_year = 2020;
        book->available = 1;
        List_Insert(l, i, book);
    }
}

void* book_lending(void * loansOffice){
    office_l *office = loansOffice;
    srand(office->seed);
    for(int i = 0; i < 1000; i++){        
        int id_book = rand()%TOTAL_BOOKS;        
        node_t * node = get_node(&books, id_book);
        pthread_mutex_lock(&lock);
        if(node->book->available == 0){
            office->failed_loan++;  
        }else{        
            node->book->available = 0;
            office->successful_loan++;        
        } 
        pthread_mutex_unlock(&lock);       
    }
}
