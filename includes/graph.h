#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include "doublyLinkedList.h"


typedef struct Graph
{
    int numOfVertices;
    Node_t** adjLists_head;
    Node_t** adjLists_tail; 
} Graph_t;

Graph_t* createGraph(int numOfVertices, char** names);
void addEdge(Graph_t* graph, int vertexIdx, char* neighbourName, int neighbourCost);
void printGraph(Graph_t* graph);
void deleteGraph(Graph_t* graph);

#endif // GRAPH_H

