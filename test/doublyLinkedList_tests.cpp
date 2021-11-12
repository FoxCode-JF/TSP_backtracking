#include "catch2/catch.hpp"

extern "C"
{
	#include <string.h>
	#include "../includes/graph.h"
	#include "../includes/doublyLinkedList.h"
	#include "../includes/backtracking.h"
}


SCENARIO("Create a list with first node and add another at head and delete node at head")
{
	GIVEN("List is not created")
	{
		WHEN("Head and tail are empty")
		{
			Node_t* head = NULL; 
			Node_t* tail = NULL;

			THEN("Create list by adding a node")
			{
				tail = addNodeAtHead(&head, 1, "A");
				REQUIRE(((tail == head) && (head->data == 1)));
			
				THEN("Add another node at head")
				{
					(void)(addNodeAtHead(&head, 2, "A"));
					REQUIRE(((tail != head) && (head->data == 2) && (strcmp(head->name, "A") == 0)));
					
					WHEN("Nodes added at head")
					{
						int data_beforeDelete = head->data;
						char* name_beforeDelete = head->name;
						THEN("Delete Node at head")
						{
							deleteNodeAtHead(&head);
							int data_afterDelete = head->data;
							char* name_afterDelete = head->name;
							REQUIRE
							(
								(data_beforeDelete != data_afterDelete ||
								strcmp(name_beforeDelete, name_afterDelete) != 0)
							);
						}
					}
				}
			}
		}
	}
}

SCENARIO("Add node at tail and delete node at tail")
{
	GIVEN("List")
	{
		size_t listSize = 6;
		Node_t* head = NULL; 
		Node_t* tail = NULL;
		char* names[6] = {"A", "B", "C", "D", "E", "F"};

		for (size_t i = 0; i < listSize; i++)
		{
			if ( tail == NULL)
			{
				tail = addNodeAtHead(&head, i, names[i]);
			}
			else 
			{
				(void)addNodeAtHead(&head, i, names[i]);
			}
		}

		WHEN("Node added at tail")
		{	
			int valueToAdd = 1111;
			char* nameToAdd = "LODZ";
			addNodeAtTail(&tail, valueToAdd, nameToAdd);
			printList(head);
			THEN("Expected data present at tail")
			{
				REQUIRE
				(
					(tail->data == valueToAdd &&
					strcmp(tail->name, nameToAdd) == 0)
				);
			}
		}	
	}
}

SCENARIO("Add node at index and delete that node")
{
	GIVEN("List and index")
	{
		size_t listSize = 6;
		uint8_t index = 3;
		Node_t* head = NULL; 
		Node_t* tail = NULL;
		char* names[6] = {"A", "B", "C", "D", "E", "F"};

		for (size_t i = 0; i < listSize; i++)
		{
			if ( tail == NULL)
			{
				tail = addNodeAtHead(&head, i, names[i]);
			}
			else 
			{
				(void)addNodeAtHead(&head, i, names[i]);
			}
		}

		WHEN("Node added at index")
		{	
			int valueToAdd = 1111;
			char* nameToAdd = "WARSZAWA";
			printList(head);
			addNodeAtIndex(&head, valueToAdd, index, nameToAdd);
			printList(head);

			THEN("Expected data present at index")
			{	
				Node_t* current;
				current = head;

				for (size_t i = 0; i < index; i++)
				{
					current = current->next;
				}

				printList(head);
				REQUIRE
				(
					(current->data == valueToAdd &&
					 strcmp(current->name, nameToAdd) == 0)
				);
			}

			WHEN("Data present at index")
			{
				Node_t* current;
				current = head;

				for (size_t i = 0; i < index; i++)
				{
					current = current->next;
				}

				int data_beforeDelete = current->data;
				char* name_beforeDelete = current->name;

				THEN("Delete node at index")
				{
					deleteNodeAtIndex(&head, index);
					
					current = head;
					for (size_t i = 0; i < index; i++)
					{
						current = current->next;
					}
					int data_afterDelete = current->data;
					char* name_afterDelete = current->name;
					REQUIRE
					(
						(data_beforeDelete != data_afterDelete ||
						strcmp(name_beforeDelete, name_afterDelete) != 0)
					);
				}
			}
		}	
	}
}

SCENARIO("Copy entire list")
{
	GIVEN("List")
	{
		size_t listSize = 6;
		Node_t* head = NULL; 
		Node_t* tail = NULL;
		char* names[6] = {"A", "B", "C", "D", "E", "F"};

		for (size_t i = 0; i < listSize; i++)
		{
			if (tail == NULL)
			{
				tail = addNodeAtHead(&head, i, names[i]);
			}
			else 
			{
				(void)addNodeAtHead(&head, i, names[i]);
			}
		}

		WHEN("List is created")
		{
			THEN("Copy whole list")
			{
				Node_t** dst_head;
				Node_t* dst_tail = NULL;
				Node_t* current_src_head = NULL;
				Node_t* current_dst_head = NULL;
				bool isCorrectlyCopied = true;

				*dst_head = NULL;	
				dst_tail = copyList(head, dst_head);
				
				printf("SOURCE:\n");
				printList(head);
				printf("DESTINATION:\n");
				printList(*dst_head);
				
				current_dst_head = *dst_head;
				current_src_head = head;

				while (current_src_head != NULL)
				{	
					if (current_src_head->data != current_dst_head->data || 
						strcmp(current_src_head->name, current_dst_head->name) != 0)
					{
						isCorrectlyCopied = false;
					}
					current_src_head = current_src_head->next;
					current_dst_head = current_dst_head->next;
				}
					REQUIRE( isCorrectlyCopied );
			}
		}
	}
}


SCENARIO("Delete entire List")
{
	GIVEN("List")
	{
		size_t listSize = 6;
		Node_t* head = NULL; 
		Node_t* tail = NULL;
		char* names[6] = {"A", "B", "C", "D", "E", "F"};

		for (size_t i = 0; i < listSize; i++)
		{
			if (tail == NULL)
			{
				tail = addNodeAtHead(&head, i, names[i]);
			}
			else 
			{
				(void)addNodeAtHead(&head, i, names[i]);
			}
		}

		WHEN("List is created")
		{
			THEN("Delete whole list")
			{
				deleteList(&head, &tail);
				REQUIRE(((head == NULL) && (tail == NULL)));
			}
		}
	}
}