//
// Created by pora on 4/4/21.
//

#ifndef PROJECT3_LINKEDLISTSTRUCT_H
#define PROJECT3_LINKEDLISTSTRUCT_H
#define MAX_SIZE_INPUT 1024
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

struct Node {
	char * process_id;
	int service_time;
	int arrival_time;
	struct Node * next;
	struct Node * prev;
};


// Porapat ArchLinux Kernel 5.5.6-arch1-1 @ 03/22/2020
void insert(struct Node** head, char* process, int service, int arrival) {
		struct Node * temp = malloc(sizeof(struct Node) + (sizeof(int) * 2) + (sizeof(char * ) * MAX_SIZE_INPUT));
		struct Node ** curr = head;
		temp->service_time = service;
		temp->arrival_time = arrival;
		temp->process_id = malloc (sizeof(char * ) * MAX_SIZE_INPUT);
		strcpy(temp->process_id, process);
		while (*curr) {
			curr = &(*curr)->next;
		}
		temp->next = *curr;
		*curr = temp;
}

void remove_head(struct Node ** head){
	struct Node ** temp = *head;
	*head = (*head)->next;
	free(temp);
}

void printlist(struct Node * head){
	struct Node * curr = head;

	while(curr != NULL)
	{
		printf("%s\t", curr->process_id);
		printf("%d\t", curr->service_time);
		printf("%d\n", curr->arrival_time);
		head = curr;
		curr = curr->next;
		free(head);
	}
}




#endif //PROJECT3_LINKEDLISTSTRUCT_H


