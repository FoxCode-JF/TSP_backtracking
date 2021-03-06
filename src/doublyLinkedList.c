#include "doublyLinkedList.h"

static void deleteNode(Node_t **node);

/**
 * @brief      Adds a node at head. If list is empty it will be created.
 *
 * @param      head          The head of the list
 * @param      data          The data to put in the list
 * @param	   name			 The name of the node.
 *
 * @return     { returns tail pointer if list is empty, else returns NULL}
 */
Node_t* addNodeAtHead(Node_t **head, LIST_DATA_TYPE data, char* name)
{
	/* Allocate memory for a new node */
	Node_t *newNode = (Node_t*)malloc(sizeof(Node_t));
	newNode->next = NULL;
	newNode->prev = NULL;

	/* Copy data to allocated */
	newNode->data = data;
	newNode->name = name;

	/* If list is empty make a new node at head and point tail to head, else add newnode to existing list */
	if(*head == NULL)
	{
		Node_t *tail;
		*head = newNode;
		tail = newNode;
		return tail;
	}
	else
	{
		newNode->next = *head;
		(*head)->prev = newNode;
		*head = newNode;
	}
	return NULL;
}

/**
 * @brief      Adds a node at index.
 *
 * @param      head          The head
 * @param      data          The data
 * @param[in]  index         The index
 * @param	   name			 The name of the node.
 */
void addNodeAtIndex(Node_t **head, LIST_DATA_TYPE data, uint16_t index, char* name)
{
	Node_t *current = *head;
	Node_t *newNode = (Node_t*)malloc(sizeof(Node_t));

	newNode->data = data;
	newNode->name = name;

	/* go to node of the list where new node will be placed */
	for (LIST_DATA_TYPE i = 0; i < index - 1; ++i)
	{
		current = current->next;
	}
	newNode->next = current->next;
	current->next = newNode;
	newNode->prev = current;
	newNode->next->prev = newNode;
}

/**
 * @brief Adds a node at tail
 * 
 * @param      tail          The tail of the list.
 * @param      data          The data
 * @param	   name			 The name of the node.
 * @return Node_t* 
 */
Node_t* addNodeAtTail(Node_t **tail, LIST_DATA_TYPE data, char* name)
{
	Node_t *newNode = malloc(sizeof(Node_t));
	newNode->next = NULL;
	newNode->prev = NULL;

	newNode->data = data;
	newNode->name = name;

	if(*tail == NULL)
	{
		Node_t *head;
		*tail = newNode;
		head = newNode;
		return head;
	} 
	else
	{
		(*tail)->next = newNode;
		newNode->prev = *tail;
		*tail = newNode;
	}
	return NULL;
}

/**
 * @brief Deletes whole list.
 * 
 * @param head 
 * @param tail 
 */
void deleteList(Node_t **head, Node_t **tail)
{
	Node_t *current = *head;
	Node_t *tmp;

	while(current != NULL)
	{
		tmp = current;
		current = current->next;
		deleteNode(&tmp);
	}
	
	*head = NULL;

	if (*tail != NULL)
	{
		*tail = NULL;
	}
	

	if(*head == NULL && *tail == NULL)
	{
		printf("List was erased successfully...\n");
	}
	else
	{
		fprintf(stderr, "List deletion unsuccessful...\n");
	}
}

/**
 * @brief Deletes node at head.
 * 
 * @param head 
 */
void deleteNodeAtHead(Node_t **head)
{
	Node_t *tmp = *head;
	if(*head != NULL)
	{
		*head=((*head)->next);
		deleteNode(&tmp);
	}
}

/**
 * @brief Deletes a node at index.
 * 
 * @param head 
 * @param index 
 */
void deleteNodeAtIndex(Node_t **head, uint16_t index)
{
	Node_t *current = *head;
	Node_t *tmp;

	/* go to node of the list where node will be deleted */
	for (int i = 0; i < index - 1; ++i)
	{
		current = current->next;
	}

	tmp = current->next;
	current->next = current->next->next;

	deleteNode(&tmp);
}

/**
 * @brief Deletes node with specific name
 * 
 * @param head 
 * @param name 
 */
void deleteNodeWithName(Node_t **head, char* name)
{
	Node_t *current = *head;
	Node_t *tmp;


	if (current != NULL)
	{
		/* go to node of the list where node will be deleted */
		while (current != NULL && strcmp(current->name, name) != 0)
		{
			current = current->next;
		}
		printf("currentnode to delete:%s", current->name);
		if (current != NULL)
		{

			tmp = current;
			if (current->prev != NULL)
			{
				current->prev->next = current->next;
			} else
			{
				(*head) = (*head)->next;
			}
			
			deleteNode(&tmp);
		}
	}
	
}

/**
 * @brief Deletes node at tail.
 * 
 * @param head 
 * @param tail 
 */
void deleteNodeAtTail(Node_t **head, Node_t **tail)
{
	Node_t *current = *head;
	while(current->next != *tail)
	{
		current = current->next;
	}

	(*tail) = current;
	current = current->next;

	deleteNode(&current);

	(*tail)->next = NULL;
}

/**
 * @brief Prints list from head to tail.
 * 
 * @param head 
 */
void printList(Node_t *head)
{
	if(head == NULL)
	{
		fprintf(stderr, "List is empty...\n");
		// exit(1);
	}

	Node_t *current = head;

	while(current != NULL)
	{
		printf("[%d, %s]", current->data, current->name);
		current = current->next;
		printf(" --> ");
	}
	printf("\n");
}

/**
 * @brief Counts elements in the lis
 * 
 * @param list_head Pointer to the head of the list
 * @return (uint16_t) Number of nodes in the list 
 */
uint16_t elementsCount(Node_t* list_head)
{
	Node_t* current = list_head;
	uint16_t cnt = 0;
	while (current != NULL)
	{
		current = current->next;
		cnt++;
	}
	return cnt;
}

/**
 * @brief Copies contents of one list to another;
 * 
 * @param src_head Head of the source list.
 * @param dst_head head of the destination list.
 * @return (Node_t*) Returns tail pointer of destination list. 
 */
Node_t* copyList(Node_t* src_head, Node_t** dst_head)
{
	Node_t* src_current = src_head;
	Node_t* dst_tail;

	dst_tail = addNodeAtHead(dst_head, src_head->data, src_head->name);
	src_current = src_current->next;

	while (src_current != NULL)
	{
		addNodeAtTail(&dst_tail, src_current->data, src_current->name);
		src_current = src_current->next;
	}
	return dst_tail;
}

static void deleteNode(Node_t **node)
{
	free(*node);
	*node = NULL;
}