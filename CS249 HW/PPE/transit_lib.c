// header files
#include "transit_lib.h"

/**
 * Function: initGraph (provide)
 * Input arguments: Graph* graph - pointer to the graph structure
 * Output argument: graph is initialized
 * Return: none
 * Dependencies: none
 */
void initGraph(Graph* graph) 
{
    // set the number of nodes in the graph to 0
    graph->numNodes = 0;
    // traverse the graph's adjacency list array
    for (int i = 0; i < MAX_NODES; i++) 
    {
        // set each adjacency list to NULL
        graph->adjList[i] = NULL;  
    }
}

/**
 * Task 1: Add a Node to the Graph
 * Input arguments: Graph* graph - pointer to the graph structure
 *                  int stop_id - the ID of the node (stop) to add
 * Output argument: graph is updated
 * Return: none
 * Dependencies: stdlib.h - malloc
 *               stdio.h - printf
 */
void addNode(Graph* graph, int stop_id)
{
    //checl if node exists
    if(graph->adjList[stop_id] != NULL)
    {
        return;
    }  

    //allocate space for new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    //check if the node was made
    if(newNode == NULL)
        {
            return;
        }

    //put data into new node
    newNode->id = stop_id;
    newNode->travel_time = 0;
    newNode->next = NULL;

    //add the node to the list
    graph->adjList[stop_id] = newNode;

    //increment amount of nodes
    graph->numNodes++;

    //print statement
    printf("Node %d successfully added\n", stop_id);
}



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
void addNode(Graph* graph, int stop_id)
{
    //check that src and dest both exist
    if(graph->adjList[src] == NULL || graph->adjList[dest] == NULL)
    {
        return;
    }  

    //malloc space for the new edge
    Node* newNode = (Node*)malloc(sizeof(Node));
    //check if it exists
    if(newNode == NULL)
    {
        return;
    }

    //put data into newNOde
    newNode->id = dest;
    newNode->travel_time = travel_time;
    newNode->next = NULL;


    //add the node to the begininning of the list
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;


    //make the bidirectional edge and add all the data
    Node* secondNode = (Node*)malloc(sizeof(Node));
    //check if it exists
    if(secondNode == NULL)
    {
        return;
    }
    secondNode->id = src;
    secondNode->travel_time = travel_time;
    secondNode->next = NULL;

    //add the node to the other list
    secondNode->next = graph->adjList[dest];
    graph->adjList[dest] = secondNode->next;

    //print statement
    printf("Edge added betewwn %d and %d with a trave time of %d\n"
        , src, dest, travel_time);
}


/**
 * Task 3: Remove a Node and Its Edges from the Graph
 * Input arguments: Graph* graph - pointer to the graph structure
 *                  int stop_id - the ID of the node (stop) to remove
 * Output argument: graph is updated
 * Return: none
 * Dependencies: stdlib.h - free
 *               stdio.h - printf
 */
void addRoute(Graph* graph, int src, int dest, int travel_time)
{
    //check if stop exists
    if(graph->adjList[stop_id] == NULL)
        {
            //print and return
            printf("Node %d does not exist\n", stop_id)
            return;
        }


    //remove all edges connected to the node
    for(int i = 0; i < MAX_NODES; i++)
    {
        //if node exists
        if(graph->adjList[i] != NULL)
        {
            //create current and previous
            Node* current = graph->adjList[i];
            Node* previous = NULL;

            //while current exists and is equal to stop id
            while(current != NULL)
                {
                    if(current->id == stop_id)
                    {
                    //set prevous next to cirrent next
                    previous->next = current->next;
                    }
                    //free current to remove it
                    free(current);
                }
                //set previous to current and current to next
            previous = current;
            current = current->next;
        }
    }
    //remove the edges
    Node* current = graph->adjList[stop_id];
    while(current != NULL)
    {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    //decrement the number of nodes
    graph->numNodes--; 

    //print function
    printf("Node %d removed successfully\n", stop_id)
}


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



/**
 * Task 5: Explore Transit Zones Starting from a Given Node Using DFS
 * Input arguments: Graph* graph - pointer to the graph structure
 *                  int start - the starting node ID
 * Output argument: None
 * Return: None
 * Dependencies: None
 */



/**
 * Funciton: displayNetwork (provided)
 * Input arguments: Graph* graph - pointer to the graph structure
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void displayNetwork(Graph* graph) 
{
    // loop through all the possible nodes (stops) in the graph
    for (int i = 0; i < MAX_NODES; i++) 
    {
        // if the current node has an adjacent list
        if (graph->adjList[i]) 
        {
            // start at the first node in the adjacency list for this node
            Node* temp = graph->adjList[i];
            // print the stop number
            printf("Stop %d ", i);
            // traverse the adjacency list (edges)
            while (temp) 
            {
                // exclude self-loop (a node connected to itself)
                if (temp->id != i) 
                { 
                    // print the connected node's ID and the travel time to it
                    printf("-> %d (Time: %d) ", temp->id, temp->travel_time);
                }
                // move to the next node in the adjacency list
                temp = temp->next;
            }
            // print '-> NULL' to signify the end of the adjacency list
            printf("-> NULL\n");
        }
    }
}