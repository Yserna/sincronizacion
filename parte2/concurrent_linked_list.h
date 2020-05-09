#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdio.h>
#include <pthread.h>

typedef struct __book {
    int id;
    char * name;
    int num_pages;
    int pub_year;
    int available;
} Book;

typedef struct __office {
    int id;
    int seed;
    int successful_loan;
    int failed_loan;
} office_l;

// basic node structure
typedef struct __node_t {
   int key;
   struct __book *book;
   struct __node_t *next;
} node_t;

// basic list structure (one used per list)
typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

void List_Init(list_t *L);
void List_Insert(list_t *L, int key, Book * book);
node_t * get_node(list_t *L, int key);

#endif