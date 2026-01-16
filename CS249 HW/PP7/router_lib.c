#include "router_lib.h"


/**
 * Function: addRouter
 * Input argument: root - a double pointer to the root of the network
 *                 router_id - the identification for the new router
 * Output argument: the last unfilled position of the last level contains a new 
 *                  router with id router_id
 * Return: none
 * Dependencies: createRouter, createQueue, isEmptyQueue, enqueue, dequeue
 */
void addRouter(RouterNode** root, int router_id)
{
	//create new router
	RouterNode* newRouter = createRouter(router_id);
	//if root is nulll return
	if(*root = NULL)
	{
		return;
	}
	//create the new queue and add root to it
	Queue* queue = createQueue();

	enqueue(queue, *root);

	//while the queue isnt empty
	while(!isEmptyQueue(queue))
	{
		//dequeue the current
		RouterNode* current = dequeue(queue);

		//if no left
		if(current->left == NULL)
		{
			//set the current to the new 
			current->left = newRouter;
		}

		//else if current isnt null add it to the queu
		else if(current->left == !NULL)
		{

			enqueue(queue, current->left)
		}
		//if the right is null set right to new 
		//else add it to the queue
		if(current->right == NULL)
		{
			current->right = newRouter;

		}
		else if(current->right == !NULL)
		{
			enqueue(queuel, current->right)
		}
	}
	//free the queue
	free(queue)
}  

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
void removeRouter(RouterNode** root, int router_id)
{
	//if root is null 
	if(*root == NULL)
	{
		return;
	}
	//create queue
	Queue* queue = createQueue();
	enqueue(queue, *root);

	//create new vars for
	RouterNode* target = NULL;
	RouterNode* lastNode = NULL;

	while()

}

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
Queue createQueue()
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
 * Function: isEmptyQueue
 * Input argument: queue - a pointer to a queue
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
 * Function: enqueue
 * Input argument: queue - a pointer to a queue
 *                 router - a pointer to the router node to enqueue
 * Output argument: the router is added at the rear of the queue
 * Return: none
 * Dependencies: stdlib.h - malloc
 */
void enqueue(Queue* queue, RouterNode* router)
{
	    //create the new node with value
    Router* newnode = createNode(value);

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
 * Input argument: queue - a pointer to a queue
 * Output argument: the front router is removed from the queue
 * Return: a pointer to the dequeued router node (not the queue node!)
 *         NULL if the queue is empty
 * Dependencies: isEmptyQueue
 *               stdlib.h - free
 */
RouterNode* dequeue(Queue* queue)
{
	//if queue is empty return null
    if(isEmptyQueue(queue))
    {
        return NULL;
    }
    RouterNode* data = queue->front;

    queue->front = queue->front->next;

    free(queue->front);
    //return datas value
    return data;
}