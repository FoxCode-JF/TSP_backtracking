#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <stdbool.h>
// #include "doublyLinkedList.h"
#include "graph.h"

typedef enum adjListGenMethod
{
    RANDOM = 0,
    USER_INPUT = 1,
    CHOOSE_PREDEFINED = 2
}adjListGenMethod_t;

Graph_t* generateAdjacencyList(adjListGenMethod_t method);
bool backtracking(int startCity, void* f_ptr_constraints, Graph_t* graph, Node_t* list_assignedVars);
bool isComplete();
bool isConsistent();
void getUnassignedVars();
void addToAssigned();


#endif /*BACKTRACKING_H*/

