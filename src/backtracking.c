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
		map1();
		break;
	default:
		break;
	}
	return NULL;
}

bool backtracking(int startCity, void* f_ptr_constraints, Graph_t* graph, Node_t* list_assignedVars)
{
	return false;
}

static Graph_t* map1()
{
	int numOfVertices = 5;

	char* names[5] = {"A", "B", "C", "D", "E"};
	Graph_t* graph = createGraph(numOfVertices, names);
	printGraph(graph);

	addEdge(graph, 2, "B", 2);
	printGraph(graph);
}

