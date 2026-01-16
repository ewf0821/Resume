// header files
#include "fleet_lib.h"

/**
 * Task 1: Validate Delivery Path
 * Input argument: routeHead - a pointer to the head node of a linked list
 *                  representing the delivery route
 * Output argument: none
 * Return: true if the path is valid, false otherwise
 * Dependencies: createStack, push, pop
 */
bool validateDeliveryPath(Node* routeHead)
{

}


/**
 * Task 2: Symmetric Route
 * Input argument: routeHead - a pointer to the head node of a linked list 
 *                  representing the delivery route
 * Output argument: none
 * Return: true if the delivery route is symmetric, false otherwise
 * Dependencies: createStack, push, pop
 *               string.h - strcmp
 */
bool isSymmetricRoute(Node* routeHead)
{

}


/**
 * Task 3: Decoding Drone Instructions
 * Input argument: instructionHead - a pointer to the head node of a linked 
 *                  list containing encoded drone instructions
 * Output argument: none
 * Return: none
 * Dependencies: createStack, push, pop, isEmptyStack
 *               stdlib.h - malloc, atoi
 *               string.h - strcmp, strcat, strcpy
 */
void decodeInstructions(Node* instructionHead)
{

}



/**
 * Task 4: Evaluate Delivery Paths
 * Input argument: expressionHead - a pointer to the head node of a linked list 
 *                 representing a Reverse Polish Notation expression
 * Output argument: none
 * Return: integer value representing the result of the evaluated expression
 * Dependencies: create, push, pop, intToStr
 *               stdlib.h - atoi
 */
int evaluatePathConditions(Node* expressionHead)
{

}


/**
 * Task 5: Reversing Delivery Routes
 * Input argument: queue - A pointer to a Queue representing the list of 
 *                  deliveries
 * Output argument: reversed delivery list
 * Return: none
 * Dependencies: createStack, push, pop, enqueue, dequeue, isEmptyQueue, 
 *               isEmptyStack
 */
void reverseDelivery(Queue* q)
{

}


/**
 * Task 6: Rotating Delivery Schedules
 * Input argument: queue - a pointer to a Queue representing the list of 
 *                  deliveries
 *                 k - an integer indicating the number of positions to rotate
 * Output argument: rotated queue
 * Return: none
 * Dependencies: isEmptyQueue
 */
void rotateDelivery(Queue* queue, int k)
{

}


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
Queue* mergeDeliveryRoutes(Queue* q1, Queue* q2)
{

}


// Stack & Queue implementations
/**
 * Function: createStack
 * Input argument: none
 * Output argument: none
 * Return: a pointer to a newly allocated Stack structure
 * Dependencies: stdlib.h - malloc
 */
Stack* createStack()
{
    //allocate memory for stack
    Stack* stack = (*Stack)malloc(sizeof(Stack));
    //set the top of the stack to NULL
    stack->top == NULL;
    //return the stack
    retun stack;
}


/**
 * Function: push
 * Input argument: stack - a pointer to a Stack structure
 *                 value - a pointer to a string to be pushed onto the stack
 * Output argument: the stack contains an additional node at the top
 * Return: none
 * Dependencies: createNode
 */
void push(Stack* stack, char* value)
{
    //create a new node with value
    Node* newnode = createNode(value);
    //set new node as the next for the top
    newnode->next = stack->top;
    //set the new top to new node
    stack->top = newnode


}


/**
 * Function: pop
 * Input argument: stack - a pointer to a Stack structure
 * Output argument: stack's top element is removed
 * Return: a pointer to the string popped from the top of the stack
 *         NULL if the stack is empty
 * Dependencies: isEmptyStack
 *               stdlib.h - free
 */
char* pop(Stack* stack)
{
    //check if the stack is empty
    if(isEmptyStack(stack))
    {
        //f stack is empty return null
        return NULL;
    }

    //create a temporary node that is the top of the stack
    Node* temp = stack->top;
    //set popped to hold the temp data which is the top of the stack
    char* popped = temp->data;
    //set the new top to the next node
    stack->top = temp->next;
    //free the old node
    free(temp);
    //return popped
    return popped;

}


/**
 * Function: isEmptyStack
 * Input argument: stack - a pointer to a Stack
 * Output argument: none
 * Return: true if the stack is empty, false otherwise
 * Dependencies: none
 */
bool isEmptyStack(Stack* stack)
{
    return stack->top == NULL;
}


/**
 * Function: createQueue
 * Input argument: none
 * Output argument: none
 * Return: a pointer to a newly allocated Queue
 * Dependencies: stdlib.h - malloc
 */
Queue* createQueue()
{
    //dynamiclally allocates the memmory for the queue
    Queue* queue = (Queue*)malloc(sizeof(Queue));

    //if malloc can allocate return null
    if(queue == NULL)
    {
        return NULL;
    }
    //set the front and rear to null as placeholder
    queue->front = NULL;
    queue->rear = NULL; 
    //return the queue
    return queue;
}


/**
 * Function: enqueue
 * Input argument: queue - a pointer to a Queue
 *                 value - a pointer to a character string to be added to the 
 *                  rear of the queue
 * Output argument: an updated queue
 * Return: none
 * Dependencies: createNode, isEmptyQueue
 */
void enqueue(Queue* queue, char* value)
{
    //create the new node with value
    Node* newnode = createNode(value);

    //if queue is empty set the front and back to new node
    if(isEmptyQueue(queue))
    {
        queue->front = newnode;
        queue->rear = newnode;
    }
    //else set the rear to the new node
    queue->rear->next = newnode;
    queue->rear = newnode;
}


/**
 * Function: dequeue
 * Input argument: queue - a pointer to a Queue
 * Output argument: an updated queue
 * Return: A pointer to the character string removed from the front of the queue.
 * Dependencies: isEmptyQueue
 *               stdlib.h - free
 */
char* dequeue(Queue* queue)
{
    //if queue is empty return null
    if(isEmptyQueue(queue))
    {
        return NULL;
    }

    //set data to be the first in the queue
    char* data = queue->front;
    //set the front to the next in the queue
    queue->front = queue->next;
    //free the front 
    free(queue->front);
    //return datas value
    return data;
}


/**
 * Function: isEmptyQueue
 * Input argument: queue - a pointer to a Queue
 * Output argument: none
 * Return: true if the queue is empty, false otherwise
 * Dependencies: none
 */
bool isEmptyQueue(Queue* queue)
{
    //if the queue size is 0 return true else return false
    if(queue->size == 0)
    {
        return true;
    }
    return false;
}


/**
 * Function: createNode (provided)
 * Input argument: value - a pointer to a string to be stored in the new node
 * Output argument: none
 * Return: a pointer to a newly allocated Node with the given value
 * Dependencies: stdlib.h - malloc
 */
Node* createNode(char* value)
{
    // allocate memory for the new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    // set the data field
    newNode->data = value;
    // initialize the next pointer to NULL
    newNode->next = NULL;
    // return the new node
    return newNode;
}

/**
 * Function: intToStr (provided)
 * Input argument: num - an integer value to be converted to a string
 * Output argument: none
 * Return: a pointer to a dynamically allocated string representing the integer
 * Dependencies: stdlib.h - malloc
 */
char* intToStr(int num)
{
    // declare a variable to hold the lenght of the number (#digits)
    int len = 0;
    // declare a variable to help calculating the # of digits
    int temp = num;

    // if the number is 0
    if (num == 0)
    {
        // the length is 1
        len = 1;
    }
    // otherwise
    else
    {
        // while the temporary variable is greater than 0
        while (temp > 0)
        {
            // count a digit
            len++;
            // divide the number by 10
            temp /= 10;
        }
    }
    
    // allocate memory for the string
    char* str = (char*)malloc((len + 1) * sizeof(char));
    // null-terminate the string
    str[len] = '\0';

    // while there are digits in the number
    while (len > 0)
    {
        // decrement the length
        len--;
        // convert the rightmost digit to a character
        //      and assign to current position len in the string
        str[len] = (num % 10) + '0';
        // divide the number by 10
        num /= 10;
    }
    // return the string
    return str;
}