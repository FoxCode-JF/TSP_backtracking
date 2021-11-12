#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define LIST_DATA_TYPE int

typedef struct Node
{
	struct Node* next;
	struct Node* prev;
	LIST_DATA_TYPE data;
	char* name;
} Node_t;

Node_t* addNodeAtHead(Node_t **head, LIST_DATA_TYPE data, char* name);
void addNodeAtIndex(Node_t **head, LIST_DATA_TYPE data, uint16_t index, char* name);
Node_t* addNodeAtTail(Node_t **tail, LIST_DATA_TYPE data, char* name);
uint16_t elementsCount(Node_t* head);
Node_t* copyList(Node_t* src_head, Node_t** dst_head);
void deleteList(Node_t **head, Node_t **tail);
void deleteNodeAtHead(Node_t **head);
void deleteNodeAtIndex(Node_t **head, uint16_t index);
void deleteNodeAtTail(Node_t **head, Node_t **tail);
void printList(Node_t *head);

#endif // DOUBLY_LINKED_LIST_H