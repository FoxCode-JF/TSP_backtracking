/**
 * @defgroup   BACKTRACKING
 *
 * @brief      This file implements backtracking algorithm which solves Optimal Constraint Satisfaction Problem (CSP) 
 * 			   (https://en.wikipedia.org/wiki/Constraint_satisfaction_problem). 
 * 		       
 * 		       Implemented specifficaly to sole Travelling Salesman Problem (TSP) 
 * 		       (https://en.wikipedia.org/wiki/Travelling_salesman_problem).
 *
 * @author     Fox
 * @date       2021
 */


#include <string.h>
#include "backtracking.h"
#include "graph.h"

static uint32_t minCost = 0;

static bool isConsistent(Node_t* list_assignedVars, Node_t* unassignedVar, uint32_t currentCost);
static Node_t* getUnassignedVar(Node_t* assignedVars, Node_t* currentAdjacencyList);
static Node_t* getUnassignedVar2(Node_t* assignedVars, Graph_t* graph);
static Node_t* getNodeAdjList(Node_t* assignedVars, Graph_t* graph);
static uint32_t getActionCost(char* from, char* to, Graph_t* graph);
static void addToAssigned(Node_t** list_assignedVars, Node_t* unassignedVar);
static bool isComplete(Node_t* assignedVars, Graph_t* graph);
static Graph_t* map1();

Graph_t* generateAdjacencyList(adjListGenMethod_t method)
{
	switch (method)
	{
	case RANDOM:
		
		break;
	case USER_INPUT:

		break;
	case CHOOSE_PREDEFINED:
		return map1();
		break;
	default:
		break;
	}
	return NULL;
}

bool backtracking(char* startCity, Graph_t* graph, Node_t* list_assignedVars, uint32_t currentCost, Node_t** currentBestPath)
{
	Node_t* assignedVars = list_assignedVars;
	Node_t* currentBestPath_tail;


	if (assignedVars == NULL)
	{
		addNodeAtHead(&assignedVars, 0, startCity);
	}
	
	if (elementsCount(assignedVars) == graph->numOfVertices)
	{
		uint32_t lastStepCost = getActionCost((assignedVars)->name, startCity, graph);
		addNodeAtHead(&assignedVars, lastStepCost, startCity);
		currentCost += lastStepCost;
	}
	
	/* solution is complete when full path is found i.e. is complete */
	if (isComplete(assignedVars, graph))
	{	
		printf("\n*****Found full path:\n");
		printList(assignedVars);
		printf("*****with cost: %d\n", currentCost);
		printf("*****min cost: %d\n", minCost);
		/* If a solution is reached check if it is currently the best (lowest cost) solution. */
		if (minCost > currentCost || minCost == 0)
		{
			if (*currentBestPath != NULL)
			{
				deleteList(currentBestPath, &currentBestPath_tail);
			}
			
			minCost = currentCost;
			currentBestPath_tail = copyList(assignedVars, currentBestPath);
		}
		deleteNodeAtHead(&assignedVars);
		return true;
	}

	Node_t* currentAdjList = getNodeAdjList(assignedVars, graph);

	while (currentAdjList !=  NULL)
	{

		currentCost += currentAdjList->data;
		if (isConsistent(assignedVars, currentAdjList, currentCost))
		{
			addToAssigned(&assignedVars, currentAdjList);
			backtracking(startCity, graph, assignedVars, currentCost, currentBestPath);
			deleteNodeAtHead(&assignedVars);
		}
		
		currentCost -= currentAdjList->data;
		currentAdjList = currentAdjList->next;
	}
	
	return true;

}

static Graph_t* map1()
{
	int numOfVertices = 5;

	char* names[5] = {"A", "B", "C", "D", "E"};
	Graph_t* graph = createGraph(numOfVertices, names);

	addEdge(graph, 0, "B", 3);
	addEdge(graph, 0, "C", 4);
	addEdge(graph, 0, "D", 2);
	addEdge(graph, 0, "E", 5);
	
	addEdge(graph, 1, "A", 3);
	addEdge(graph, 1, "C", 2);
	addEdge(graph, 1, "D", 5);
	addEdge(graph, 1, "E", 5);
	
	addEdge(graph, 2, "A", 4);
	addEdge(graph, 2, "B", 2);
	addEdge(graph, 2, "D", 4);
	addEdge(graph, 2, "E", 6);
	
	addEdge(graph, 3, "A", 2);
	addEdge(graph, 3, "B", 5);
	addEdge(graph, 3, "C", 4);
	addEdge(graph, 3, "E", 6);
	
	addEdge(graph, 4, "A", 5);
	addEdge(graph, 4, "B", 5);
	addEdge(graph, 4, "C", 6);
	addEdge(graph, 4, "D", 6);

	return graph;
}

static bool isComplete(Node_t* assignedVars, Graph_t* graph)
{
	uint32_t elCnt = elementsCount(assignedVars);
	return elCnt == (graph->numOfVertices) + 1;
}

static uint32_t getActionCost(char* from, char* destination, Graph_t* graph)
{
	Node_t* startNodeAdjList = NULL;
	/* Find "from" adjacency list */

	for (size_t i = 0; i < graph->numOfVertices; i++)
	{
		if (strcmp(graph->adjLists_head[i]->name, from) == 0)
		{
			startNodeAdjList = graph->adjLists_head[i];
			break;
		}
	}

	/* Find cost of going to "destination" node */
	while (startNodeAdjList != NULL)
	{
		if (strcmp(startNodeAdjList->name, destination) == 0)
		{
			return startNodeAdjList->data; 
		}
		startNodeAdjList = startNodeAdjList->next; 
	}
	return 0;
}

static Node_t* getUnassignedVar2(Node_t* assignedVars, Graph_t* graph)
{
	Node_t* currentAssignedVar = assignedVars;
	Node_t* currentAdjacencyList = NULL;
	
	bool isOnAssigned = false;

	for (size_t i = 0; i < graph->numOfVertices; i++)
	{
		if (strcmp(assignedVars->name, graph->adjLists_head[i]->name) == 0)
		{
			Node_t* currentNeighbour = graph->adjLists_head[i]->next;
			while (currentNeighbour != NULL)
			{
				while (currentAssignedVar != NULL)
				{
					if (strcmp(currentAssignedVar->name, currentNeighbour->name) == 0)
					{
						isOnAssigned = true;
						break;
					}
					currentAssignedVar = currentAssignedVar->next;
				}

				if (isOnAssigned)
				{
					currentAssignedVar = assignedVars;
					isOnAssigned = false;
				} else
				{
					addNodeAtHead(&currentAdjacencyList, currentNeighbour->data, currentNeighbour->name);
				}

				currentNeighbour = currentNeighbour->next;
			}
			break;
		}
	}
	return currentAdjacencyList;
}

static Node_t* getUnassignedVar(Node_t* assignedVars, Node_t* currentAdjacencyList)
{
	Node_t* currentAssignedVar = assignedVars;
	bool isOnAssigned = false;

	/* Finding any node that is not on assigned but is on adjacency list */
	while (currentAdjacencyList != NULL)
	{
		while (currentAssignedVar != NULL)
		{
			if (strcmp(currentAssignedVar->name, currentAdjacencyList->name) == 0)
			{
				isOnAssigned = true;
			}
			currentAssignedVar = currentAssignedVar->next;
		}

		if (isOnAssigned)
		{
			currentAdjacencyList = currentAdjacencyList->next;
			currentAssignedVar = assignedVars;
			isOnAssigned = false;
		} else
		{
			return currentAdjacencyList;
		}
	}	
	return NULL;
}

static bool isConsistent(Node_t* list_assignedVars, Node_t* unassignedVar/*  , uint32_t minCost */, uint32_t currentCost/* , uint32_t domainVal */)
{
	if (unassignedVar == NULL)
	{
		return false;
	}

	if (minCost == 0)
	{
		return true;
	} else
	{
		return currentCost < minCost;
	}	
}

static Node_t* getNodeAdjList(Node_t* assignedVars, Graph_t* graph)
{
	Node_t* currentAdjList_head = NULL;
	Node_t* currentAdjList_tail = NULL;
	Node_t* adjList = NULL;
	Node_t* currentAssignedVar = assignedVars;

	// Node_t* currentAdjacencyList = NULL;
	bool isOnAssigned = false;

	// printList(assignedVars);
	/* Find adjacency list of current node which is at head of assigned vars */
	for (size_t i = 0; i < graph->numOfVertices; i++)
	{
		/* Head of assignedVars is the last assigned node so respective adjacencyList i.e. neighbouring nodes need to be found */
		if (strcmp(assignedVars->name, graph->adjLists_head[i]->name) == 0)
		{
			adjList = graph->adjLists_head[i]->next;

			// printf("ADJLIST:::    ");
			// printList(adjList);
			break;
			// return currentAdjacencyList;
		}
	}

	while (adjList != NULL)
	{
		while (currentAssignedVar != NULL)
		{
			if (strcmp(adjList->name , currentAssignedVar->name) == 0)
			{
				isOnAssigned = true;
			}
			currentAssignedVar = currentAssignedVar->next;
		}

		if (isOnAssigned != true)
		{
			if (currentAdjList_head == NULL)
			{
				currentAdjList_head = addNodeAtTail(&currentAdjList_tail, adjList->data, adjList->name);
			} else
			{
				addNodeAtTail(&currentAdjList_tail, adjList->data, adjList->name);
			}
		} else 
		{
			isOnAssigned = false;
		}
		currentAssignedVar = assignedVars;
		adjList = adjList->next;
	}

	return currentAdjList_head;
}

static void addToAssigned(Node_t** list_assignedVars, Node_t* unassignedVar)
{
	addNodeAtHead(list_assignedVars, unassignedVar->data, unassignedVar->name);
}