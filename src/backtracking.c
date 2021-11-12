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

static bool isConsistent(uint32_t currentCost);
static Node_t* getUnassignedVar(Node_t* assignedVars, Graph_t* graph);
static uint32_t getActionCost(char* from, char* to, Graph_t* graph);
// static void addToAssigned();
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

bool backtracking(char* startCity, /* void* f_ptr_constraints, */ Graph_t* graph, Node_t** list_assignedVars, uint32_t currentCost, Node_t** currentBestPath, uint32_t minCost)
{
	Node_t* unassignedVar;

	if (*list_assignedVars == NULL)
	{
		addNodeAtHead(list_assignedVars, 0, startCity);
	}
	
	if (isComplete(*list_assignedVars, graph))
	{
		if (minCost > currentCost)
		{
			minCost = currentCost;
			copyList(*list_assignedVars, currentBestPath);
		}
	}
	unassignedVar = getUnassignedVar(*list_assignedVars, graph);

	if (unassignedVar == NULL)
	{
		return false;
	}	

	/* domainVal = {0, 1, 2, 3, 4, 5 ... numOfVertices + 1}, there is + 1 because there is always a way back to the starting point*/
	for (size_t domainVal = 0; domainVal < graph->numOfVertices + 1; domainVal++)
	{
		if (domainVal == graph->numOfVertices)
		{
			uint32_t lastStepCost = getActionCost((*list_assignedVars)->name, startCity, graph);
			addNodeAtHead(list_assignedVars, lastStepCost, startCity);
		} else
		{
			currentCost += unassignedVar->data;
			if (isConsistent(currentCost))
			{
				addNodeAtHead(list_assignedVars, unassignedVar->data, unassignedVar->name);
			} else
			{
				return false;
			}
			printf("list_assignedVars:\n");
			printList(*list_assignedVars);

			// printList(*currentBestPath);
			return backtracking(startCity, graph, list_assignedVars, currentCost, currentBestPath, minCost);
		}
		
	}
	return false;
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
	addEdge(graph, 3, "B", 2);
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
	return (graph->numOfVertices + 1) == elementsCount(assignedVars);
}

static uint32_t getActionCost(char* from, char* destination, Graph_t* graph)
{
	Node_t* startNodeAdjList = NULL;
	/* Find "from" adjacency list */

	for (size_t i = 0; i < graph->numOfVertices; i++)
	{
		if (strcmp(graph->adjLists_head[i]->name, from))
		{
			startNodeAdjList = graph->adjLists_head[i];
			break;
		}
	}

	/* Find cost of goint to "destination" node */
	while (startNodeAdjList != NULL)
	{
		if (strcmp(startNodeAdjList->name, destination))
		{
			return startNodeAdjList->data; 
		}
		startNodeAdjList = startNodeAdjList->next; 
	}
	return 0;
}

static Node_t* getUnassignedVar(Node_t* assignedVars, Graph_t* graph)
{
	Node_t* currentAssignedVar = assignedVars;
	Node_t* currentAdjacencyList = NULL;
	uint16_t currentAdjacencyListIndex = 0;
	bool isOnAssigned = false;

	/* Find adjacency list of current node which is at head of assigned vars */
	for (size_t i = 0; i < graph->numOfVertices; i++)
	{
		/* Head of assignedVars is the last assigned node so respective adjacencyList i.e. neighbouring nodes need to be found */
		if (strcmp(assignedVars->name, graph->adjLists_head[i]->name) == 0)
		{
			currentAdjacencyListIndex = i;
			currentAdjacencyList = graph->adjLists_head[i]->next;
			break;
		}
	}

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
	
	// while (currentAssignedVar != NULL)
	// {

	// 	while (currentAdjacencyList != NULL)
	// 	{
	// 		if (currentAssignedVar->next == NULL)
	// 		{
	// 			break;
	// 		} else if (strcmp(currentAdjacencyList->name, currentAssignedVar->next->name) == 0)
	// 		{
	// 			isOnAssigned = true;
	// 			break;
	// 		}
	// 		currentAdjacencyList = currentAdjacencyList->next;
	// 	}

	// 	if (isOnAssigned)
	// 	{
	// 		currentAdjacencyList = graph->adjLists_head[currentAdjacencyListIndex]->next;
	// 	} else
	// 	{
	// 		return currentAdjacencyList;
	// 	}
	// 	currentAssignedVar = currentAssignedVar->next;
	// }
	return NULL;
}

static bool isConsistent(uint32_t currentCost)
{
	if (minCost == 0)
	{
		return true;
	} else
	{
		return currentCost < minCost;
	}	
}