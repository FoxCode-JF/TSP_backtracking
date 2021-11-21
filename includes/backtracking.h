#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <stdbool.h>
#include "graph.h"

typedef enum adjListGenMethod
{
    RANDOM = 0,
    USER_INPUT = 1,
    CHOOSE_PREDEFINED = 2
}adjListGenMethod_t;

Graph_t* generateAdjacencyList(adjListGenMethod_t method);
bool backtracking(char* startCity, Graph_t* graph, Node_t* list_assignedVarsss, uint32_t currentCost, Node_t** currentBestPath);

#endif /*BACKTRACKING_H*/

