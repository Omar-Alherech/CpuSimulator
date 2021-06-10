
#include "LinkedListStruct.h"
#ifndef PROJECT3_QUEUE_H
#define PROJECT3_QUEUE_H

struct Queue{
	int size;
	struct Node * head;
};

int IsEmpty(struct Queue * pqueue){
	return (pqueue->size == 0);
}
int Size(struct Queue * pqueue){
	return (pqueue->size);
}
void Enqueue(struct Queue *pqueue, char * process_id, int service, int arrival){
	pqueue->size++;
	insert(&(pqueue->head), process_id, service, arrival);
}

void Dequeue(struct Queue * pqueue){
	pqueue->size--;
	remove_head(&pqueue->head);
}

#endif 

