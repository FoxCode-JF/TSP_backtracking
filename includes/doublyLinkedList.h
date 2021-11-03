#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define LIST_DATA_TYPE int

struct Node
{
	struct Node* next;
	struct Node* prev;
	int data;
};
typedef struct Node Node_t;

Node_t* addNodeAtHead(Node_t **head, LIST_DATA_TYPE data);
void addNodeAtIndex(Node_t **head, LIST_DATA_TYPE data, uint16_t index);
Node_t* addNodeAtTail(Node_t **tail, LIST_DATA_TYPE data);
void deleteList(Node_t **head, Node_t **tail);
void deleteNodeAtHead(Node_t **head);
void deleteNodeAtIndex(Node_t **head, uint16_t index);
void deleteNodeAtTail(Node_t **head, Node_t **tail);
void deleteNode(Node_t **node);
void printList(Node_t *head);
// void printInt(void *intPtr);

#endif // DOUBLY_LINKED_LIST_H