//
// Created by pora on 4/3/20.
//

#ifndef PROJECT3_LINKEDLIST_H
#define PROJECT3_LINKEDLIST_H
#define MAX_SIZE_INPUT 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node * xor (struct Node * a, struct Node *b);
void insert(struct Node **head, char *data_input);

// XOR Linked List - Supposed to be more memory efficient.
struct Node {
  char *data;
  struct Node *ptr_val;
};
ptr_val

    void
    insert(struct Node **head, char *data_input) {
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
  temp->data = malloc(sizeof(char *) * MAX_SIZE_INPUT);
  strcpy(temp->data, data_input);
  temp->ptr_val = xor(NULL, (*head));
  if ((*head) != NULL) {
    struct Node *new_node = xor(NULL, (*head)->ptr_val);
    (*head)->ptr_val = xor(temp, new_node);
  }
  (*head) = temp;
}

void display_list(struct Node *head) {
  struct Node *prev;
  struct Node *curr;
  struct Node *next;
  curr = head;
  prev = NULL;

  while (curr != NULL) {
    printf("%s", curr->data);
    next = xor(prev, curr->ptr_val);
    free(prev);
    prev = curr;
    curr = next;
  }
  printf("\n");
}

struct Node * xor (struct Node * a, struct Node *b) {
  return (struct Node *)((unsigned)a ^ (unsigned)b);
}
#endif  // PROJECT3_LINKEDLIST_H
