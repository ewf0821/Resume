#ifndef ROUTER_LIB_H
#define ROUTER_LIB_H

// header files
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// global definitions
    // struct for router node
typedef struct RouterNode 
{ 
    int router_id;
    struct RouterNode* left;
    struct RouterNode* right;
}
RouterNode;

    // struct for the queue node
typedef struct QueueNode
{ 
    RouterNode* router;
    struct QueueNode* next;
}
QueueNode;

    // struct for the queue
typedef struct Queue 
{ 
    QueueNode* front;
    QueueNode* rear;
}
Queue;

// function prototypes
/**
 * Function: addRouter
 * Input argument: root - a double pointer to the root of the network
 *                 router_id - the identification for the new router
 * Output argument: the last unfilled position of the last level contains a new 
 *                  router with id router_id
 * Return: none
 * Dependencies: createRouter, createQueue, isEmptyQueue, enqueue, dequeue
 */
void addRouter(RouterNode** root, int router_id);  

/**
 * Function: removeRouter
 * Input argument: root - a double pointer to the root of the network
 *                 router_id - the identification for the new router
 * Output argument: the target router is replaced with the last router in the 
 *                   network (bottomost, rightmost node)
 * Return: none
 * Dependencies: createQueue, isEmptyQueue, enqueue, dequeue
 *               stdlib.h - free
 */
void removeRouter(RouterNode** root, int router_id);  

/**
 * Function: invertNetwork
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: the pointer to the root node, where the tree's left and right sides 
 *          are swapped
 * Dependencies: invertNetwork (recursive)
 */
RouterNode* invertNetwork(RouterNode* root);  

/**
 * Function: isRoutingSymmetric
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: true if the routing is symmetric, false otherwise
 * Dependencies: createQueue, enqueue, dequeue, isEmptyQueue
 */
bool isRoutingSymmetric(RouterNode* root);  

/**
 * Function: getMaxNetworkDepth
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: an integer value representing the maximum depth of the tree
 * Dependencies: getMaxNetworkDepth (recursive)
 */
int getMaxNetworkDepth(RouterNode* root);  

/**
 * Function: getRouterRightView
 * Input argument: root - a pointer to the root of the network
 *                 level - an integer representing the current level (root is 
 *                         at level 0)
 *                  maxLevel - an integer value representing the last level 
 *                         (initially set to -1)
 * Output argument: none
 * Return: none
 * Dependencies: getRouterRightView (recursive)
 *               stdio.h - printf
 */
void getRouterRightView(RouterNode* root, int level, int* maxLevel);

/**
 * Function: findHighTrafficRouters
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: none
 * Dependencies: createQueue, enqueue, dequeue, isEmptyQueue
 *               stdio.h - printf
 */
void findHighTrafficRouters(RouterNode* root);  

/**
 * Function: printNetwork
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void printNetwork(RouterNode* root);  

// utility functions
/**
 * Function: createRouter
 * Input argument: router_id - the router's identification
 * Output argument: none
 * Return: a pointer to the recently created router node
 * Dependencies: stdlib.h - malloc
 */
RouterNode* createRouter(int router_id);

/**
 * Function: createQueue
 * Input argument: none
 * Output argument: none
 * Return: a queue where front and rear pointers are set to NULL
 * Dependencies: none
 */
Queue createQueue();  

/**
 * Function: isEmptyQueue
 * Input argument: queue - a pointer to a queue
 * Output argument: none
 * Return: true if the queue is empty, false otherwise
 * Dependencies: none
 */
bool isEmptyQueue(Queue* queue);  

/**
 * Function: enqueue
 * Input argument: queue - a pointer to a queue
 *                 router - a pointer to the router node to enqueue
 * Output argument: the router is added at the rear of the queue
 * Return: none
 * Dependencies: stdlib.h - malloc
 */
void enqueue(Queue* queue, RouterNode* router);  

/**
 * Function: dequeue
 * Input argument: queue - a pointer to a queue
 * Output argument: the front router is removed from the queue
 * Return: a pointer to the dequeued router node (not the queue node!)
 *         NULL if the queue is empty
 * Dependencies: isEmptyQueue
 *               stdlib.h - free
 */
RouterNode* dequeue(Queue* queue);

#endif // ROUTER_LIB_H  // End of the header guard
