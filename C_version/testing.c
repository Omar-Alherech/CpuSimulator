//
// Created by pora on 4/3/20.
//

#include "Queue.h"
int main(){
	struct Queue * Pending = malloc(sizeof(struct Queue) + (sizeof(struct Node *)) + (sizeof(int) * 2) +
			                                (sizeof(char * )* MAX_SIZE_INPUT));
	Enqueue(Pending, "T1", 1, 2);
	Enqueue(Pending, "T2", 2, 3);
	Enqueue(Pending, "T3", 3, 4);
	Dequeue(Pending);
	printlist(Pending->head);
}