// header files
#include "fleet_lib.h"

// main program
int main() 
{
    // create a variable to store the user's choice
    int choice = 1;

    while (choice != 8)
    {
        // print the menu options for the user
        printf("\nFleet Control System\n\n");
        printf("1. Validate Delivery Path\n");
        printf("2. Check Symmetric Route\n");
        printf("3. Decode Drone Instructions\n");
        printf("4. Evaluate Path Conditions\n");
        printf("5. Reverse Delivery Routes\n");
        printf("6. Rotate Delivery Schedule\n");
        printf("7. Merge Delivery Routes\n");
        printf("8. Exit\n");

        // prompt for the user's choice
        printf("Choose an option: ");
        // read the option
        scanf("%d", &choice);
        // choose the action
        switch (choice) 
        {
            // Task 1: Validate Delivery Path
            case 1: 
            {
                // print the header
                printf("Validate Delivery Path\n");
                // create the linked list for path
                Node* path = createNode("(");
                path->next = createNode("{");
                path->next->next = createNode("[");
                path->next->next->next = createNode("]");
                path->next->next->next->next = createNode("}");
                path->next->next->next->next->next = createNode(")");
                // validate the delivery path
                if (validateDeliveryPath(path)) 
                {
                    // print the message if valide
                    printf("Valid delivery path\n");
                }
                // otherwise, it is invalid
                else
                {
                    // print the path if invalid
                    printf("Invalid delivery path\n");
                }
                // end case
                break;
            }
            // Task 2: Symmetric Route
            case 2: 
            {
                // print the header
                printf("Symmetric Route\n");
                // Create the linked list for the route
                Node* route = createNode("Route A");
                route->next = createNode("Route B");
                route->next->next = createNode("Route C");
                route->next->next->next = createNode("Route B");
                route->next->next->next->next = createNode("Route A");
                // check if the route is symmetric
                if (isSymmetricRoute(route))
                {
                    // print a message if valid
                    printf("The route is symmetric\n");
                }
                // otherwise, it is invalid
                else
                {
                    // print a message
                    printf("The route is not symmetric\n");
                }
                // end case
                break;
            }
            // Task 3: Decoding Drone Instructions
            case 3: 
            {
                // print the header
                printf("Decoding Drone Instructions\n");
                // create the linked list for instructions
                Node* instructions = createNode("2");
                instructions->next = createNode("[");
                instructions->next->next = createNode("Hover");
                instructions->next->next->next = createNode("1");
                instructions->next->next->next->next = createNode("[");
                instructions->next->next->next->next->next = createNode("Scan");
                instructions->next->next->next->next->next->next = 
                    createNode("2");
                instructions->next->next->next->next->next->next->next = 
                    createNode("[");
                instructions->next->next->next->next->next->next->next->next = 
                    createNode("FlyTo");
                instructions->
                    next->next->next->next->next->next->next->next->next = 
                    createNode("]");
                instructions->
                    next->next->next->next->next->next->next->next->next->next 
                    = createNode("]");
                instructions->
                    next->next->next->next->next->next->next->next->next->next->
                    next = createNode("]");
                // decode the instructions
                decodeInstructions(instructions);
                // end case
                break;
            }
            // Task 4: Evaluating Path Conditions
            case 4: 
            {
                // print the header
                printf("Evaluating Path Conditions\n");
                // Create the linked list for expression
                Node* expression = createNode("6");
                expression->next = createNode("3");
                expression->next->next = createNode("+");
                expression->next->next->next = createNode("4");
                expression->next->next->next->next = createNode("*");
                expression->next->next->next->next->next = createNode("3");
                expression->next->next->next->next->next->next = 
                    createNode("/");

                // evaluate the path conditions
                int result = evaluatePathConditions(expression);
                // print the result
                printf("Result of path evaluation: %d\n", result);
                // end case
                break;
            }
            // Task 5: Reversing Delivery Routes
            case 5: 
            {
                // print the header
                printf("Reversing Delivery Routes\n");
                // create a queue for delivery points
                Queue* queue = createQueue();
                enqueue(queue, "Point D");
                enqueue(queue, "Point B");
                enqueue(queue, "Point A");
                enqueue(queue, "Point E");
                enqueue(queue, "Point F");
                enqueue(queue, "Point C");

                // reverse the delivery routes
                reverseDelivery(queue);

                // traverse the queue
                while (queue->front) 
                {
                    // print the reversed queue
                    printf("%s -> ", dequeue(queue));
                }
                // print the end of the queue
                printf("NULL\n");
                // end case
                break;
            }
            // Task 6: Rotating Delivery Schedule
            case 6:
            {
                // print the header
                printf("Rotating Delivery Schedule\n");
                // create a queue for delivery schedule
                Queue* schedule = createQueue();
                enqueue(schedule, "Delivery 1");
                enqueue(schedule, "Delivery 2");
                enqueue(schedule, "Delivery 3");
                enqueue(schedule, "Delivery 4");
                enqueue(schedule, "Delivery 5");
                enqueue(schedule, "Delivery 6");

                // totate the delivery schedule
                rotateDelivery(schedule, 28);

                // traverse the queue
                while (schedule->front) 
                {
                    // print the rotated queue
                    printf("%s -> ", dequeue(schedule));
                }
                // print the end of the queue
                printf("NULL\n");
                // end case
                break;
            }
            // Task 7: Merging Delivery Routes
            case 7: 
            {
                // print the header
                printf("Task 8: Merging Delivery Routes\n");
                // create the first queue for routes
                Queue* q1 = createQueue();
                enqueue(q1, "Route A1");
                enqueue(q1, "Route A2");
                enqueue(q1, "Route A3");
                // create the second queue for routes
                Queue* q2 = createQueue();
                enqueue(q2, "Route B1");
                enqueue(q2, "Route B2");

                // merge the two delivery routes
                Queue* merged = mergeDeliveryRoutes(q1, q2);

                // traverse the merged queue
                while (merged->front) 
                {
                    // Print the merged queue
                    printf("%s -> ", dequeue(merged));
                }
                // print the end of the queue
                printf("NULL\n");
                // end the case
                break;
            }

            case 8:
                // Exit the program
                printf("Exiting...\n");
                // end case
                break;
            default:
                // the option is invalid, print a message
                printf("Invalid option, please try again.\n");
        }
    }
    // return success
    return 0;
}
