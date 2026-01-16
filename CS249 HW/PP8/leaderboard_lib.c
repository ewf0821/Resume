// header files
#include "leaderboard_lib.h"

/**
* Task 1: Create leaderboard 
* Input argument: root - a pointer to the root of the leaderboard
* Output argument: none
* Return: none
* Dependencies: none
*/
void createLeaderboard(TreeNode **root)
{
    //set root as null
    *root = NULL;
}


/**
* Task 2: Add a new student 
* Input argument: root - a pointer to the root of the leaderboard
*                 score - the score to add to the leaderboard
* Output argument: none
* Return: a pointer to the root of the leaderboard
* Dependencies: rightRotate, leftRotate, maxHeight, height, getBalance
                addStudent (recursive)
*               stdlib.h - malloc
*/
TreeNode* addStudent(TreeNode *root, int score)
{
    //if root is null allocate space and set right and left to null
    if(root == NULL)
        {
            TreeNode* node = (*Treenode)malloc(sizeof(TreeNode));
            node->score = score;
            node->height = 1;
            node->left = NULL;
            node->right = NULL;
            return node;
        }

        //if score is less than the root add that to the left
    if(score < root->score)
    {
        root->left = addStudent(root->left, score);
    }
    //if score is more than the rood add it to the right
    if(score > root->score)
    {
        root->right = addStudent(root->right,score);
    }
    //if theyre the same just return the root
    if(score == root->score)
        {
            return root;
        }

        //set height to 1+ max height which is left - right
    root->height = 1 + maxHeight(height(root->left), height(root->right));

    //check for balance
    int balance = getBalance(root);

    //if balance is more than 1 check score against left node
    //if greater rotate right
    //if less rotate left and then rotate right
    if(balance > 1)
    {
        if(score < root->left->score)
        {
            return rightRotate(root);
        }
        if(score > root->left->score)
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
    }

    //if balance is -1 check score against  right node
    //if score is greater rotate left
    //if score is less rotate on the right and then rotate left  
    if(balance < -1)
    {
        if(score > root->right->score)
        {
            return leftRotate(root);
        }
        if(score < root->right->score)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    //return root
    return root;


}


/**
* Task 3: Remove a student 
* Input argument: root - a pointer to the root of the leaderboard
*                 score - the score to remove from the leaderboard
* Output argument: none
* Return: a pointer to the root of the leaderboard
* Dependencies: rightRotate, leftRotate, maxHeight, height, getBalance
*               removeStudent (recursive)
*/
TreeNode* removeStudent(TreeNode *node, int score)
{
    //iff root is null return root
    if(root == NULL)
        {
            return root;
        }

        //if score is less than root remove the left
    if(score < root->score)
    {
        root->left = removeStudent(root->left, score);
    }
    //if root is less than score remove the right
    else if(score > root->score)
    {
        root->right = removeStudent(root->right,score);
    }

    else
    {
        //if left or right is null
        if((root->left == NULL) || root->right == NULL)
        {
            // treenode child ptr
            TreeNode* temp; 

            //if root is not null set temp to left
            if(root->left != NULL)
            {
                temp = root->left;  
            }
            //else temp is right
            else
            {
                temp = root->right; 
            }
            // if there is no child
            if(temp == NULL)
                //store root in child
                temp = root;
                // root to null
                root = NULL;
            }
            //ekse create child
            else
            {
                TreeNode* successor = root->right;
                //while left isnt null
                while(root->left != NULL)
                {
                    //successor is left
                    successor = successor->left;
                }
                //root s the left score
                root->score = successor->score

                root->right = removeStudent(root->right, successor->score);
            }

    }
    //if root is null after all that return root
    if(root == NULL)
    {
        return root;
    }

    //set the height
    root->height = 1 + maxHeight(height(root->left), height(root->right));

    //check for balance
    int balance = getBalance(root);

    //if alance is less than 1 check for balance of the left and rotate right
    //rotate right
    //if score is highter than left rotate left on left
    //rotate right
    if(balance > 1)
    {
        if(getBalance(root->left) >= 0)
        {
            return rightRotate(root);
        }
        if(score > root->left->score)
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
    }

    //if balance is less -1 get balance of right
    //left rotate/
    //if score is less rotate right
    //then rotate left
    if(balance < -1)
    {
        if(getBalance(root->right) <= 0)
        {
            return leftRotate(root);
        }
        if(score < root->right->score)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}


/**
* Task 4: Print leaderboard 
* Input argument: root - a pointer to the root of the leaderboard
* Output argument: none
* Return: none
* Dependencies: printLeaderboard (recursive)
*               stdio.h - printf
*/
void printLeaderboard(TreeNode *root)
{
    //if root is null return
    if(root == NULL)
    {
        return;
    }

    //print leaderboard left
    printLeaderboard(root->left);

    //print the scores
    printf("Score: %d\n", root->score);

    //then print the right
    printLeaderboard(root->right)
}


/**
* Function: findKthSmallestScore (provided)
* Input argument: root - a pointer to the root of the leaderboard
*                 k - integer value indicating the order of the smallest 
*                     element to be found
* Output argument: none
* Return: integer value representing the Kth smallest score or -1 if not found
* Dependencies: findKthSmallest
*/
int findKthSmallestScore(TreeNode *root, int k) 
{
    // initialize the count of visited nodes
    int count = 0;
    // initialize result to -1 (indicating not found)       
    int result = -1;
    
    // call the recursive function to perform the in-order traversal
    findKthSmallest(root, k, &count, &result);
    
    // return the Kth smallest score found
    return result;        
}


/**
* Task 5: Find the kth smallest score
* Input argument: root - a pointer to the root of the leaderboard
*                 k - integer value indicating the order of the smallest 
*                     element to be found
*                 count - a pointer to the number of visited nodes
*                 result - a pointer to the integer representing the kth 
*                          smallest score (or -1 if not found)
* Output argument: count and result are updated
* Return: none
* Dependencies: findKthSmallest (recursive)
*/
void findKthSmallest(TreeNode *root, int k, int *count, int *result)
{
    //if root null return
    if(root == NULL)
    {
        return;
    }

    //recusion to find smallest on the left
    findKthSmallest(root->left, k, count, result);

    //increment count of nodes
    (*count)++;

    //if count is equal to k
    if(*count == k)
        {   

            //make result the current score
            *result = root->score;
            //return
            return;
        }

    //traverese the right side
    findKthSmallest(root->right, k, count, result);

}


/**
* Task 6: Calculate the range sum of scores 
* Input argument: root - a pointer to the root of the leaderboard
*                 low, high - integer values to delimit the range
* Output argument: none
* Return: the sum of the scores in the range
* Dependencies: rangeSumScores (recursive)
*/
int rangeSumScores(TreeNode *root, int low, int high)
{
    //if root null return 0
    if(root == NULL)
        {
            return 0;
        }

    //initaillize varaibles
    int sum = 0;

    //if score is >= low and <= add root to sum
    if(root->score >= low && root->score <= high)
    {
        sum += root->score;
    }

    //if root > low check left
    if(root->score > low)
    {
        sum += rangeSumScores(root->left, low, high);
    }

    //if root < high check right
    if(root->score < high)
    {
        sum += rangeSumScores(root->right, low, high)
    }

    //return sum
    return sum;
}


/**
* Task 7: Find common friend 
* Input argument: root - a pointer to the root of the leaderboard
*                 student1, student2 - integer values with student scores
* Output argument: none
* Return: score of the common friend
* Dependencies: findCommonFriendStudent (recursive)
*/



/**
 * Task 8: Measure Academic Connectivity
 * Input argument: root - a pointer to the root of the leaderboard
 * Output argument: none
 * Return: total academic connectivity as an integer
 * Dependencies: height
 */



/**
 * Function: countSubtree (for Task 9)
 * Input argument: root - a pointer to the root of the leaderboard
 *                 sum - a pointer to the sum of the scores in the subtree
 *                 count - a pointer to the number of nodes in a subtree
 * Output argument: sum and count contains the sum and count values for the 
 *                  given subtree
 * Return: none
 * Dependencies: countSubtree (recursive)
 */



/**
 * Task 9: Identify students meeting average performance
 * Input argument: root - a pointer to the root of the leaderboard
 * Output argument: none
 * Return: number of students meeting the average performance as an integer
 * Dependencies: calculateSubtree
 */



// utility functions to maintain the AVL trees
/**
* Function: height (provided)
* Input argument: node - a pointer to a node in an BST
* Output argument: none
* Return: the height of the node as an integer
* Dependencies: none
*/
int height(TreeNode *node) 
{
    // check if the node is NULL
    if (node == NULL)
    {
        // no height
        return 0;
    }
    // return the height attribute of the current node
    return node->height;
}

/**
* Function: maxHeight
* Input argument: left - the height of the left subtree of a node
*                 right - the height of the right subtree of a node
* Output argument: none
* Return: integer value representing the maximum of left and right values
* Dependencies: none
*/
int maxHeight(int left, int right)
{
    //if left is more than right return left
    if(left > right)
        {
            return left;
        }
        //else return right
        return right;
}


/**
* Function: getBalance
* Input argument: node - a node in an AVL tree
* Output argument: none
* Return: the difference between the heights of the left and right children
* Dependencies: none
*/
int getBalance(TreeNode *node)
{
    //if node is null return 0
    if(node = NULL)
    {
        return 0;
    }
    //get height of left and right 
    //return the difference
}


/**
* Function: rightRotate
* Input argument: unbalancedNode - the unbalanced node to rotate in an AVL tree
* Output argument: the height of rotated nodes are updated
* Return: the new root of the rotated subtree
* Dependencies: maxHeight, height
*/
TreeNode* rightRotate(TreeNode *unbalancedNode)
{

}


/**
* Function: leftRotate
* Input argument: unbalancedNode - the unbalanced node to rotate in an AVL tree
* Output argument: the height of rotated nodes are updated
* Return: the new root of the rotated subtree
* Dependencies: maxHeight, height
*/
TreeNode* leftRotate(TreeNode *unbalancedNode)
{

}