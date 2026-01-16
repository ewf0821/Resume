#ifndef TRANSIT_LIB_H   
#define TRANSIT_LIB_H   

// header files
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// global definitions
#define MAX_NODES 100

// data types
typedef struct Node
{  
    int id;            
    int travel_time;   
    struct Node* next; 
}
Node;

typedef struct Graph 
{  
    Node* adjList[MAX_NODES]; 
    int numNodes;            
}
Graph;

/**
 * Function: initGraph (provide)
 * Input arguments: Graph* graph - pointer to the graph structure
 * Output argument: graph is initialized
 * Return: none
 * Dependencies: none
 */
void initGraph(Graph* graph);   

/**
 * Task 1: Add a Node to the Graph
 * Input arguments: Graph* graph - pointer to the graph structure
 *                  int stop_id - the ID of the node (stop) to add
 * Output argument: graph is updated
 * Return: none
 * Dependencies: stdlib.h - malloc
 *               stdio.h - printf
 */
void addNode(Graph* graph, int stop_id);   

/**
 * Task 2: Add Route between stops
 * Input arguments: Graph* graph - pointer to the graph structure
 *                  int src - the source node ID
 *                  int dest - the destination node ID
 *                  int travel_time - the cost of travel from src to dest
 * Output argument: graph is updated
 * Return: none
 * Dependencies: stdlib.h - malloc
 *               stdio.h - printf
 */
void addRoute(Graph* graph, int src, int dest, int travel_time);  

/**
 * Task 3: Remove a Node and Its Edges from the Graph
 * Input arguments: Graph* graph - pointer to the graph structure
 *                  int stop_id - the ID of the node (stop) to remove
 * Output argument: graph is updated
 * Return: none
 * Dependencies: stdlib.h - free
 *               stdio.h - printf
 */
void removeNode(Graph* graph, int stop_id);  

/**
 * Task 4: Remove Route between stops
 * Input arguments: Graph* graph - pointer to the graph structure
 *                  int src - the source node ID
 *                  int dest - the destination node ID
 * Output argument: graph is updated
 * Return: none
 * Dependencies: stdlib.h - free
 *               stdio.h - pr
 */
void removeRoute(Graph* graph, int src, int dest);   

/**
 * Task 5: Explore Transit Zones Starting from a Given Node Using DFS
 * Input arguments: Graph* graph - pointer to the graph structure
 *                  int start - the starting node ID
 * Output argument: None
 * Return: None
 * Dependencies: None
 */
void exploreTransitZones(Graph* graph, int start);  

/**
 * Funciton: displayNetwork (provided)
 * Input arguments: Graph* graph - pointer to the graph structure
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void displayNetwork(Graph* graph);  

#endif  
