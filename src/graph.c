#include "graph.h"

/**
 * @brief Create a Graph representation of Cities in TSP problem.
 *        Graph is represented as adjacency lists
 * 
 * @param numOfVertices Number of vertices in the graph.
 * @param names         Names of the Cities in the graph.
 * @return Graph_t*     
 */
Graph_t* createGraph(int numOfVertices, char** names)
{
    Graph_t* graph = (Graph_t*)malloc(sizeof(Graph_t));

    graph->numOfVertices = numOfVertices;
    graph->adjLists_head = malloc(numOfVertices * sizeof(Node_t*));
    graph->adjLists_tail = malloc(numOfVertices * sizeof(Node_t*));

    for (size_t i = 0; i < numOfVertices; i++)
    {   
        graph->adjLists_tail[i] = addNodeAtHead(&(graph->adjLists_head[i]), 0, names[i]);
    }

    return graph;
}

/**
 * @brief Prints Graph in form of adjacency lists.
 * 
 * @param graph 
 */
void printGraph(Graph_t* graph) 
{
    for (size_t i = 0; i < graph->numOfVertices; i++)
    {
        Node_t* tmp_head = graph->adjLists_head[i];

        printf("\n Vertex %d\n: ", i);
        printList(tmp_head);
        printf("\n");
    }
}

/**
 * @brief Deletes the graph.
 * 
 * @param graph 
 */
void deleteGraph(Graph_t* graph)
{
    for (size_t i = 0; i < graph->numOfVertices; i++) 
    {
        Node_t* tmp_head = graph->adjLists_head[i];
        
        printf("\n Vertex %d\n: ", i);
        deleteList(&tmp_head, NULL);
        printf("\n");
        free(graph);
    }
}

/**
 * @brief Adds new edge to the chosen vertex adjacency list.
 * 
 * @param graph
 * @param vertexIdx 
 * @param neighbourName 
 * @param neighbourCost 
 */
void addEdge(Graph_t* graph, int vertexIdx, char* neighbourName, int neighbourCost)
{
    addNodeAtTail(&(graph->adjLists_tail[vertexIdx]), neighbourCost, neighbourName);
}