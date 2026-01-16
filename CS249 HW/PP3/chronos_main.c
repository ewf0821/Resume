// header files
#include <stdio.h>
#include <stdlib.h>
#include "chronos_lib.h"

// main program
int main()
{
    // declare and initialize the test data
    int hiddenCodeArray[] = {7, 5, 3, 7, 15, 5, 9, 3, 9};  // Task 1
    int systemLogs[] = {8, -2, -1, 4, 7, 0, 4, 5};  // Task 2
    char scrambledMessage[] = "aabbccddeeffgghhiijj";
    char referenceMessage[] = "cajehfbcidefbghgdiaj";  // Task 3
    int criticalLog[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};  // Task 4
    int rotatedData[] = {7, 8, 9, 10, 1, 2, 3, 4, 5, 6};  // Task 5
    int rotatedMin[] = {7, 8, 9, 10, 1, 2, 3, 4, 5, 6};  // Task 6

    // Task 1: Find the unique code
    int uniqueCode = unique_code(hiddenCodeArray, sizeof(hiddenCodeArray) /
        sizeof(hiddenCodeArray[0]));
    printf("Dear TechnoCity Restorer, the Chronos system needs your expertise " 
        "to restore order and functionality! Each step you take helps us "
        "uncover vital information and secure our city.\n\n");
    printf(
        "================================================================\n\n");
    printf("The Hidden Code in the Data Breach:\n\n");
    printf("In the chaos of the cyberattack, essential security codes have been"
        " scrambled. Your task was to identify the unique code amidst the "
        "duplicates that has been corrupted beyond recognition.\n\n");
    printf("The unique code in the data breach is: %d\n\n", uniqueCode);
    printf("You've successfully pinpointed the unique code that will help us "
        "reestablish secure access controls. Great job!\n\n");

    // Task 2: Find the balance point in the system logs
    int balancePoint = balance(systemLogs, sizeof(systemLogs) / sizeof(systemLogs[0]));
    printf("=================================================================\n\n");
    printf("Balancing the System Logs:\n\n");
    printf("Our system logs are in disarray, and we need to find the balance"
        "point where the activity before equals the activity after. This "
        "balance point is crucial for assessing the impact of the attack and "
        "ensuring stability.\n\n");
    printf("The balance point in the system logs is at index: %d\n\n",
        balancePoint);
    printf("You've found the equilibrium point, restoring balance to our logs "
        "and paving the way for further analysis.\n\n");

    // Task 3: Decode the scrambled message
    int isDecoded = decode(scrambledMessage, referenceMessage);
    printf(
        "================================================================\n\n");
    if (isDecoded == true) 
    {
        printf("The scrambled message can be decoded to match the reference "
            "message.\n\n");
        printf("You've successfully decoded the messages, unlocking vital "
            "information necessary for a comprehensive response to the attack."
            "\n\n");
    } 

    else {
        printf("The scrambled message cannot be decoded to match the reference "
            "message.\n\n");
        printf("You've encountered issues in decoding the messages, which may "
            "require further investigation.\n\n");
    }

    // Task 4: Find the maximum sum of a contiguous subarray
    int maxSum = uncover(criticalLog, 
        sizeof(criticalLog) / sizeof(criticalLog[0]));
    printf(
        "================================================================\n\n");
    printf("Uncovering the Critical System Log:\n\n");
    printf("Among the clutter of system logs, the most significant sequence of "
        "events is hidden. Finding the maximum sum of a contiguous subarray "
        "reveals the most critical period of activity.\n\n");
    printf("The maximum sum of a contiguous subarray is: %d\n\n", maxSum);
    printf("Congratulations! You've identified the most impactful period of "
        "activity, providing key insights into the attack's effects.\n\n");

    // Task 5: Search for a specific entry in a rotated sorted array
    int dataElement = 3;
    int index = navigate(rotatedData, sizeof(rotatedData) / sizeof(rotatedData[0]), dataElement);
    printf(
        "================================================================\n\n");
    printf("Navigating Through Rotated Data:\n\n");
    printf("A critical part of our dataset was rotated, making searches "
    "challenging. Your task was to locate a specific entry within this rotated "
    "sorted array.\n\n");
    if (index != NOT_FOUND) 
    {
        printf("The data element %d is present at index: %d\n\n", 
            dataElement, index);
        printf("You've successfully navigated the rotated data, retrieving "
            "crucial information from the disarrayed dataset.\n\n");
    }
    else
    {
        printf("The data element %d is not present in the array.\n\n", 
            dataElement);
        printf("The data element was not found, which may suggest further "
            "investigation is needed.\n\n");
    }

    // Task 6: Find the minimum value in a rotated sorted array
    int minValue = critical_minimum(rotatedMin, sizeof(rotatedMin) / sizeof(rotatedMin[0]));
    printf(
        "================================================================\n\n");
    printf("Finding the Critical Minimum:\n\n");
    printf("The dataset's rotation has made it necessary to find the minimum "
        "value within the rotated sorted array. This value is crucial for "
        "diagnostic purposes.\n\n");
    printf("The minimum value in the rotated sorted array is: %d\n\n", 
        minValue);
    printf("You've identified the minimum value, helping us understand the  "
        "rotation's impact and facilitate accurate analysis.\n\n");

    // return success
    return 0;
}
