#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "concurrent_linked_list.h"


void List_Init(list_t *L) {
	L->head = NULL;
	pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, int value, Book * libro) {
    // synchronization not needed
	node_t *new = malloc(sizeof(node_t));    
	if (new == NULL) {
		perror("malloc");
		return;
	}
	new->key = value;
    new->book = libro;
    // just lock critical section
	pthread_mutex_lock(&L->lock);
	new->next = L->head;
	L->head = new;
	pthread_mutex_unlock(&L->lock);
}

node_t * get_node(list_t *L, int key){
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    node_t *result = NULL;
    while (curr) {
        if (curr->key == key) {
            result = curr;
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return result;
}