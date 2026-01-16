// header files
#include "chronos_lib.h"


/**
 * Task 1: Uncovering the Unique Code
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the unique integer that appears only once in the array
 * Dependencies: none
 */
int unique_code(int array[], int size)
{
	//loop thoguht the array
	for (int i = 0; i < size; i++)
	{
		//set a temp value that will could when no duplicate
		int temp = 0;
		//loop again that will count the no dupe if theyre  
		for (int j = 0; j < size; j++)
		{
			if(array[i] == array[j])
			{
				temp++;
			}
		if(temp == 1)
		{
			return array[i];
		}

		}
	}
	return -1;
}



/**
 * Task 2: Balancing the Array
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the index where the sum of elements on the left equals the sum on the right
 * Dependencies: none
 */
int balance(int array[], int size)
{
	//declare left and right
	int left = 0;
	int right = 0;
	//loop through the array add the values to left
	for (int i = 0; i >= 0; i--)
	{
		left += array[i];
	}
	//loop through array and add the values to right
	for (int j = 0; j < size; j++)
	{
		right += array[j];
	}
	//if the values are the same return index
	if(left == right)
	{
		return array[i];
	}
	return -1;
}


/**
 * Task 3: Decoding the Scrambled Message
 * Input argument: scrambled_message as a string, reference_message as a string
 * Output argument: none
 * Return: boolean value indicating if the messages are anagrams
 * Dependencies: none
 */
bool decode(const char *scrambled_message, const char *reference_message)
{
	//get the sizes of each string
	int scrambled = strlen(scrambled_message);
	int reference = strlen(reference_message);

	//if the sizes arent the same return false
	if(scrambled != reference)
	{
		return false;
	}
	//if their values are the same return true
	if(strcmp(scrambled_message, reference_message) == 0)
	{
		return true;
	}
	//else return fasle
	return false;
}


/**
 * Task 4: Uncovering the Maximum Sequence
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the maximum sum of a contiguous subarray
 * Dependencies: none
 */

//use kadanes algorithim
int uncover(int array[], int size)
{
	//declare max and current
	int max = 0;
	int current = 0;

	//loop the array
	for (int i = 0; i < size; i++)
	{
		//make current the added values in the array
		current += array[i];

		//if max is less than current make max new value
		if(max < current)
		{
			max = current;
		}
		//if current dips to negative reset it to 0 
		if(current < 0)
		{
			current = 0;
		}
	}
	//return max value
	return max;
}


/**
 * Task 5: Navigating the Rotated Array
 * Input argument: array as a 1D array of integers, size as an integer, data_element as an integer
 * Output argument: none
 * Return: the index of the data_element in the rotated sorted array
 * Dependencies: none
 */
int navigate(int array[], int size, int data_element)
{
	int low = 0;
	int high = size - 1; 

	while(low <= high)
	{
		int middle = (low + high) / 2;
		//if mid is the correct answer return instantly
		return (array[middle] == data_element);


		//find if its left sorted or right sorted
		if(array[low] <= array[middle])
		{
			//if left sorted while the low array is less and element is less
			// than middle 
			if(array[low] <= data_element && data_element <= array[middle])
			{
				//make the new high the middle
				high = middle - 1;
			}
			else
			{
				//if thats not true make the new low the middle
				low = middle + 1;
			}
		}
		//if its not left sorted its right sorted
		else
		{
			//if data is higher than middle and lower than the high index
			if(array[middle] <= data_element && data_element <= array[high])
			{
				// make the new low the middle
				low = middle + 1; 
			}
			else
			{
				//else make the new high the middle
				high = middle - 1;
			}
		}
	}
	//the above while is basuically just checking bot possibilites if left
	// or right sorted delete the other half 
	return -1;
}


/**
 * Task 6: Finding the Critical Minimum
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the minimum value in a rotated sorted array
 * Dependencies: none
 */
int critical_minimum(int array[], int size)
{
	int low = 0; 
	int high = size - 1; 
	int value = 0;

	while(low <= high)
	{
		int mid = (low + high) / 2;

		if(array[low] <= array[mid])
		{
			value = low;
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
			value = mid;
		}

	}
	return value;

}

