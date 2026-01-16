// include guards
#ifndef LEADERBOARD_LIB_H
#define LEADERBOARD_LIB_H

// header files
#include <stdio.h>
#include <stdlib.h>

// global definitions
typedef struct TreeNode 
{
    int score;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
}
TreeNode;

// function prototypes
/**
* Function: createLeaderboard
* Input argument: root - a pointer to the root of the leaderboard
* Output argument: none
* Return: none
* Dependencies: none
*/
void createLeaderboard(TreeNode **root);

/**
* Function: addStudent
* Input argument: root - a pointer to the root of the leaderboard
*                 score - the score to add to the leaderboard
* Output argument: none
* Return: a pointer to the root of the leaderboard
* Dependencies: rightRotate, leftRotate, height, max, getBalance
                addStudent (recursive)
*               stdlib.h - malloc
*/
TreeNode* addStudent(TreeNode *root, int score);

/**
* Function: removeStudent
* Input argument: root - a pointer to the root of the leaderboard
*                 score - the score to remove from the leaderboard
* Output argument: none
* Return: a pointer to the root of the leaderboard
* Dependencies: rightRotate, leftRotate, maxHeight, getBalance
*               removeStudent (recursive)
*/
TreeNode* removeStudent(TreeNode *node, int score);

/**
* Task 4: Print leaderboard 
* Input argument: root - a pointer to the root of the leaderboard
* Output argument: none
* Return: none
* Dependencies: printLeaderboard (recursive)
*               stdio.h - printf
*/
void printLeaderboard(TreeNode *root);

/**
* Function: findKthSmallestScore (provided)
* Input argument: root - a pointer to the root of the leaderboard
*                 k - integer value indicating the order of the smallest 
*                     element to be found
* Output argument: none
* Return: integer value representing the Kth smallest score or -1 if not found
* Dependencies: findKthSmallest
*/
int findKthSmallestScore(TreeNode *root, int k);

/**
* Function: findKthSmallest
* Input argument: root - a pointer to the root of the leaderboard
*                 k - integer value indicating the order of the smallest 
*                     element to be found
*                 count - a pointer to the number of visited nodes
*                 result - a pointer to the integer representing the kth 
*                          smallest score (or -1 if not found)
* Output argument: count and result are updated
* Return: none
* Dependencies: findKthSmallest
*/
void findKthSmallest(TreeNode *root, int k, int *count, int *result);

/**
* Function: rangeSumScores
* Input argument: root - a pointer to the root of the leaderboard
*                 low, high - integer values to delimit the range
* Output argument: none
* Return: the sum of the scores in the range
* Dependencies: rangeSumScores (recursive)
*/
int rangeSumScores(TreeNode *root, int low, int high);

/**
* Function: findCommonFriendStudent
* Input argument: root - a pointer to the root of the leaderboard
*                 student1, student2 - integer values with student scores
* Output argument: none
* Return: score of the common friend
* Dependencies: findCommonFriendStudent (recursive)
*/
int findCommonFriend(TreeNode *root, int student1, int student2);

/**
 * Function: measureConnectivity
 * Input argument: root - a pointer to the root of the leaderboard
 * Output argument: none
 * Return: total academic connectivity as an integer
 * Dependencies: height
 */
int measureConnectivity(TreeNode *root);

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
void countSubtree(TreeNode *node, int *sum, int *count);

/**
 * Function: averagePerformance
 * Input argument: root - a pointer to the root of the leaderboard
 * Output argument: none
 * Return: number of students meeting the average performance as an integer
 * Dependencies: calculateSubtree
 */
int averagePerformance(TreeNode *root);

// utility functions to maintain the AVL trees
/**
* Function: height (provided)
* Input argument: node - a pointer to a node in an BST
* Output argument: none
* Return: the height of the node as an integer
* Dependencies: none
*/
int height(TreeNode *node);

/**
* Function: maxHeight
* Input argument: left - the height of the left subtree of a node
*                 right - the height of the right subtree of a node
* Output argument: none
* Return: integer value representing the maximum of left and right values
* Dependencies: none
*/
int maxHeight(int left, int right);

/**
* Function: getBalance
* Input argument: node - a node in an AVL tree
* Output argument: none
* Return: the difference between the heights of the left and right children
* Dependencies: none
*/
int getBalance(TreeNode *node);

/**
* Function: rightRotate
* Input argument: unbalancedNode - the unbalanced node to rotate in an AVL tree
* Output argument: the height of rotated nodes are updated
* Return: the new root of the rotated subtree
* Dependencies: maxHeight
*/
TreeNode* rightRotate(TreeNode *unbalancedNode);

/**
* Function: leftRotate
* Input argument: unbalancedNode - the unbalanced node to rotate in an AVL tree
* Output argument: the height of rotated nodes are updated
* Return: the new root of the rotated subtree
* Dependencies: maxHeight
*/
TreeNode* leftRotate(TreeNode *unbalancedNode);

#endif // LEADERBOARD_LIB_H
