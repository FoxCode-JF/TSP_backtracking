#include "catch2/catch.hpp"

extern "C"
{
	#include <string.h>
	#include "../includes/backtracking.h"
}


static Node_t* expected_backtrackingResult();
static Graph_t* test_map1();

SCENARIO("Backtracking algo")
{
	GIVEN("Constraints")
	{
			
		WHEN("data initialized")
		{
			Node_t* expectedResult_head = expected_backtrackingResult();
			Graph_t* test_graph = test_map1();
			Node_t* assignedVars = NULL;
			Node_t* obtainedResult_head;
			
			THEN("Check algo successful")
			{
				bool isSuccess = backtracking("A", test_graph, assignedVars, 0, obtainedResult_head, 0);
				bool isSolutionBest = true;

				while (expectedResult_head != NULL)
				{
					if (expectedResult_head->data != obtainedResult_head->data && strcmp(expectedResult_head->name, obtainedResult_head->name) != 0)
					{
						isSolutionBest = false;
					}
				}
				
				REQUIRE((isSuccess && isSolutionBest));
			}
		}
	}
}

static Node_t* expected_backtrackingResult()
{
	Node_t* result_head = NULL;
	Node_t* result_tail = NULL;

	result_tail = addNodeAtHead(&result_head, 0, "A");
	addNodeAtHead(&result_head, 2, "D");
	addNodeAtHead(&result_head, 4, "C");
	addNodeAtHead(&result_head, 2, "B");
	addNodeAtHead(&result_head, 5, "E");
	addNodeAtHead(&result_head, 5, "A");

	return result_head;
}
static Graph_t* test_map1()
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