//
// Created by pora on 4/3/2 1.
//

#ifndef PROJECT3_LINKEDLIST_INT_XOR_H
#define PROJECT3_LINKEDLIST_INT_XOR_H
#define MAX_SIZE_INPUT 1024
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

struct Node * xor(struct Node *a, struct Node *b);
void insert(struct Node **head, char * process_id, int service, int arrival);
void remove_head(struct Node *head);

//XOR Linked List - Supposed to be more memory efficient.
struct Node {
	char * process_id;
	int service_time;
	int arrival_time;
	struct Node * ptr_val;
};



void insert(struct Node **head, char * process_id, int service, int arrival){
	struct Node * temp = malloc(sizeof(struct Node) + (sizeof(int) * 2) + (sizeof(char * ) * MAX_SIZE_INPUT));
	temp->service_time = service;
	temp->arrival_time = arrival;
	temp->process_id = malloc (sizeof(char * ) * MAX_SIZE_INPUT);
	strcpy(temp->process_id, process_id);
	temp->ptr_val = xor(NULL, (*head));
	if ((*head) != NULL){
		struct Node * new_node = xor(NULL, (*head)->ptr_val);
		(*head)->ptr_val = xor(temp, new_node);
	}
	(*head) = temp;
}



void display_list(struct Node *head){
	struct Node *  prev;
	struct Node *  curr;
	struct Node *  next;
	curr = head;
	prev = NULL;

	while(curr != NULL){
		printf("%s\t", curr->process_id);
		printf("%d\t", curr->service_time);
		printf("%d\n", curr->arrival_time);
		next = xor(prev, curr->ptr_val);

		prev = curr;
		curr = next;
	}
	printf("\n");
}

struct Node* xor(struct Node *a, struct Node *b)
{
	return (struct Node*) ((uintptr_t) (a) ^ (uintptr_t) (b));
}
#endif //PROJECT3_LINKEDLIST_INT_XOR_H
