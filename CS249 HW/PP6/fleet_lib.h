#ifndef FLEET_LIB_H
#define FLEET_LIB_H

// header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// global definitions
# define MESSAGE_LEN 1024
    // linked list node
typedef struct Node
{
    char* data;
    struct Node* next;
}
Node;

    // queue structure
typedef struct Queue
{
    Node* front;
    Node* rear;
}
Queue;

    // stack structure
typedef struct Stack
{
    Node* top;
}
Stack;

// function prototypes
/**
 * Function: validateDeliveryPath
 * Input argument: routeHead - a pointer to the head node of a linked list
 *                  representing the delivery route
 * Output argument: none
 * Return: true if the path is valid, false otherwise
 * Dependencies: createStack, push, pop
 */
bool validateDeliveryPath(Node* routeHead);

/**
 * Function: isSymmetricRoute
 * Input argument: routeHead - a pointer to the head node of a linked list 
 *                  representing the delivery route
 * Output argument: none
 * Return: true if the delivery route is symmetric, false otherwise
 * Dependencies: createStack, push, pop
 *               string.h - strcmp
 */
bool isSymmetricRoute(Node* routeHead);

/**
 * Function: decodeInstructions
 * Input argument: instructionHead - a pointer to the head node of a linked 
 *                  list containing encoded drone instructions
 * Output argument: none
 * Return: none
 * Dependencies: createStack, push, pop
 *               stdlib.h - malloc, atoi
 *               string.h - strcmp, strcat, strcpy
 */
void decodeInstructions(Node* instructionHead);

/**
 * Function: evaluatePathConditions
 * Input argument: expressionHead - a pointer to the head node of a linked list 
 *                 representing a Reverse Polish Notation expression
 * Output argument: none
 * Return: integer value representing the result of the evaluated expression
 * Dependencies: create, push, pop, intToStr
 *               stdlib.h - atoi
 */
int evaluatePathConditions(Node* expressionHead);

/**
 * Function: reverseDelivery
 * Input argument: queue - a pointer to a Queue structure representing the list of deliveries.
 * Output argument: None
 * Return: None
 * Dependencies: Stack functions to reverse the elements in the queue.
 */
void reverseDelivery(Queue* q);

/**
 * Function: rotateDelivery
 * Input argument: queue - a pointer to a Queue representing the list of 
 *                  deliveries
 *                 k - an integer indicating the number of positions to rotate
 * Output argument: rotated queue
 * Return: none
 * Dependencies: isEmptyQueue
 */
void rotateDelivery(Queue* queue, int k);

/**
 * Task 7: Merging Delivery Routes
 * Input argument: queue1 - a pointer to the first Queue representing a 
 *                  delivery route
 *                 queue2 - s pointer to the second Queue representing a    
 *                  delivery route
 * Output argument: none
 * Return: a pointer to a new Queue containing the merged elements
 * Dependencies: createQueue, dequeue, enqueue, isEmptyQueue
 */
Queue* mergeDeliveryRoutes(Queue* q1, Queue* q2);

// stack-related functions
/**
 * Function: createStack
 * Input argument: none
 * Output argument: none
 * Return: a pointer to a newly allocated Stack structure
 * Dependencies: stdlib.h - malloc
 */
Stack* createStack();

/**
 * Function: push
 * Input argument: stack - a pointer to a Stack structure
 *                 value - a pointer to a string to be pushed onto the stack
 * Output argument: the stack contains an additional node at the top
 * Return: none
 * Dependencies: createNode
 */
void push(Stack* stack, char* value);

/**
 * Function: pop
 * Input argument: stack - a pointer to a Stack structure
 * Output argument: stack's top element is removed
 * Return: a pointer to the string popped from the top of the stack
 *         NULL if the stack is empty
 * Dependencies: isEmptyStack
 *               stdlib.h - free
 */
char* pop(Stack* stack);

/**
 * Function: isEmptyStack
 * Input argument: stack - a pointer to a Stack
 * Output argument: none
 * Return: true if the stack is empty, false otherwise
 * Dependencies: none
 */
bool isEmptyStack(Stack* stack);

// Queue-related functions

/**
 * Function: createQueue
 * Input argument: none
 * Output argument: none
 * Return: a pointer to a newly allocated Queue
 * Dependencies: stdlib.h - malloc
 */
Queue* createQueue();

/**
 * Function: enqueue
 * Input argument: queue - a pointer to a Queue
 *                 value - a pointer to a character string to be added to the 
 *                  rear of the queue
 * Output argument: an updated queue
 * Return: none
 * Dependencies: createNode, isEmptyQueue
 */
void enqueue(Queue* queue, char* value);

/**
 * Function: dequeue
 * Input argument: queue - a pointer to a Queue
 * Output argument: an updated queue
 * Return: A pointer to the character string removed from the front of the queue.
 * Dependencies: isEmptyQueue
 *               stdlib.h - free
 */
char* dequeue(Queue* queue);

/**
 * Function: isEmptyQueue
 * Input argument: queue - a pointer to a Queue
 * Output argument: none
 * Return: true if the queue is empty, false otherwise
 * Dependencies: none
 */
bool isEmptyQueue(Queue* queue);

// other utility functions
/**
 * Function: createNode (provided)
 * Input argument: value - a pointer to a string to be stored in the new node
 * Output argument: none
 * Return: a pointer to a newly allocated Node with the given value
 * Dependencies: stdlib.h - malloc
 */
Node* createNode(char* value);

/**
 * Function: intToStr (provided)
 * Input argument: num - an integer value to be converted to a string
 * Output argument: none
 * Return: a pointer to a dynamically allocated string representing the integer
 * Dependencies: stdlib.h - malloc
 */
char* intToStr(int num);

#endif  // end FLEET_LIB_H