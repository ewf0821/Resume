#ifndef WORD_TOOL_LIB_H
#define WORD_TOOL_LIB_H

// header files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// global definitions
#define TABLE_SIZE 100 
#define MAX_WORDS 1000
#define NOT_FOUND -1

// data types
typedef struct 
{
    char word[TABLE_SIZE];   
    char replacement[TABLE_SIZE];
}
ReplacementEntry;

typedef struct DictionaryEntry 
{
    char *word;
    char *definition;
    char **synonyms;
    int synonymsCount;
    char **antonyms;
    int antonymsCount;
    struct DictionaryEntry *next;
}
DictionaryEntry;

// Function prototypes
/**
 * Task 1: Add a New Word to the Dictionary
 * Input arguments: DictionaryEntry *table[] - dictionary hash table
 *                  const char *word - word to add
 *                  const char *definition - definition of the word
 *                  char *synonyms[] - array of synonyms
 *                  int synonymsCount - number of synonyms
 *                  char *antonyms[] - array of antonyms
 *                  int antonymsCount - number of antonyms
 * Output argument: the hash table is updated
 * Return: bool - true if the word was added or updated successfully, 
 *                false otherwise
 * Dependencies: hash, copyString, freeSynonymsOrAntonyms
 *               stdlib - malloc, free
 *               string - strup, strdup
 */
bool addWord(
    DictionaryEntry *table[], const char *word, const char *definition,
    char *synonyms[], int synonymsCount, char *antonyms[], int antonymsCount);

/**
 * Task 2: Search for a Word in the Dictionary
 * Input arguments: DictionaryEntry *table[] - dictionary hash table, 
 *                  const char *word - word to search
 * Output argument: None
 * Return: DictionaryEntry * - pointer to the dictionary entry if found
 *         NULL if not found
 * Dependencies: hash
 *               string.h - strcmp
 */
DictionaryEntry *searchWord(DictionaryEntry *table[], const char *word);

/**
 * Task 3: Remove a Word from the Dictionary
 * Input arguments: DictionaryEntry *table[] - dictionary hash table, 
 *                  const char *word - word to remove
 * Output argument: None
 * Return: bool - true if word was removed successfully, false if word not found
 * Dependencies: hash
 *               string.h - strcmp
 *               stdlib.h - free
 */
bool removeWord(DictionaryEntry *table[], const char *word);

/**
 * Task 4: Replace Words with Synonyms in a Text
 * Input arguments: DictionaryEntry *table[] - dictionary hash table,
 *                  const char *inputFile - input file path,
 *                  const char *outputFile - output file path
 * Output argument: none
 * Return: none
 * Dependencies: searchWord, findReplacement
 *               stdio.h - fopen, fclose, fprintf, fscanf
 *               string.h - strcpy
 *               stdlib.h - srand, rand
 */
void replaceWithSynonyms(
    DictionaryEntry *table[], const char *inputFile, const char *outputFile);

/**
 * Task 5: Replace Words with a Consistent Random Antonym in a Text
 * Input arguments: DictionaryEntry *table[] - dictionary hash table
 *                  const char *inputFile - input file path
 *                  const char *outputFile - output file path
 * Output argument: none
 * Return: none
 * Dependencies: searchWord, findReplacement
 *               stdio.h - fopen, fclose, fprintf, fscanf
 *               string.h - strcpy
 *               stdlib.h - srand, rand
 */
void replaceWithAntonyms(
    DictionaryEntry *table[], const char *inputFile, const char *outputFile);

/**
 * Task 6: Display All Words in the Dictionary
 * Input arguments: DictionaryEntry *table[] - dictionary hash table
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void displayDictionary(DictionaryEntry *table[]);

/**
 * Function: hash
 * Input arguments: const char *word - word to hash
 * Output argument: none
 * Return: unsigned int - hash index for the word
 * Dependencies: none
 */
unsigned int hash(const char *word);

/**
 * Function: findReplacement
 * Input arguments: ReplacementEntry replacements[] - array of replaced entries
 *                  int count - number of entries in the array
 *                  const char *word - word to check for replacement
 * Output argument: none
 * Return: int - index of replacement if found, -1 if not found
 * Dependencies: strcmp
 */
int findReplacement(
    ReplacementEntry replacements[], int count, const char *word);

/**
 * Function: copyString
 * Input arguments: const char *str - the string to copy
 * Output argument: None
 * Return: char* - a pointer to the newly allocated string that is a copy of the input string, 
 *                or NULL if the input string is NULL or memory allocation fails
 * Dependencies: malloc, strlen, strcpy
 */
char *copyString(const char *str);

/**
 * Function: freeSynonymsOrAntonyms
 * Input arguments: char **arr - array to free
 *                  int count - number of elements in the array
 * Output argument: arr is updated
 * Return: none
 * Dependencies: stdlib.h - free
 */
void freeSynonymsOrAntonyms(char **arr, int count);

#endif  // WORD_TOOL_LIB_H
