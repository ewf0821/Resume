// header files
#include "word_tool_lib.h"

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
    char *synonyms[], int synonymsCount, char *antonyms[], int antonymsCount)
{
        //hash to get index
        int index = hash(word);
        //set up current to our table index
        DictionaryEntry* current = table[index];
        //previous to nul
        DictionaryEntry* previous = NULL;
        //found to false
        bool found = false;

        //while current isnt null and found
        while(current != NULL && !found)
        {
            //compare given word to current if same found is true
            if(strcmp(current->word, word) == 0)
            {
                found = true;
            }
            //else previous is current and advance current
            else
            {
            //set previous to current and current to next
            previous = current;
            current = current->next;
            }
        }

        //if found is false
        if(found)
        {
            //free everything
            free(current->definition);
            freeSynonymsOrAntonyms(current->synonyms, current->synonymsCount);
            freeSynonymsOrAntonyms(current->antonyms, current->antonymsCount);

        }
        else
        {
            //else allocate space for current
            current = (DictionaryEntry*)malloc(sizeof(DictionaryEntry));
            //if previous is null set the current to the next index
            if(previous == NULL)
            {
                table[index] = current;
            }
            //if not null previous next is current
            else
            {
                previous->next = current;
            }
            //if current is null return false
            if(current == NULL)
            {
                return false;
            }
        }

        //word is the copied word and definition is the copied definition
        current->word = copyString(word);
        current->definition = copyString(definition);

        //make size for synonmys and loop to copy all the synonyms
        //and update count
        current->synonyms = malloc(sizeof(char*) * synonymsCount);
        for(int i = 0; i < synonymsCount; i++)
        {
            current->synonyms[i] = copyString(synonyms[i]);
        }
        current->synonymsCount = synonymsCount;

        //same for antonyms
        current->antonyms = malloc(sizeof(char*) * antonymsCount);
        for(int i = 0; i < antonymsCount; i++)
        {
            current->antonyms[i] = copyString(antonyms[i]);
        } 
        current->antonymsCount = antonymsCount;
        //return true
        return true; 
}


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
DictionaryEntry *searchWord(DictionaryEntry *table[], const char *word)
{
    //get the index
    int index = hash(word);

    //head is the first in the linked list at index
    DictionaryEntry* current = table[index];

    //while head exists
    while(current != NULL)
    {
        //compare to origional word
        //if theyre the same return head
        if(strcmp(current->word, word) == 0 )
        {
            return current;
        }

        //else advance
        current = current->next;
    }
    //if head is null return null
    return NULL;
}


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
bool removeWord(DictionaryEntry *table[], const char *word)
{
    //get index and set up current and previous
    int index = hash(word);
    DictionaryEntry* current = table[index];
    DictionaryEntry* previous = NULL;

    //while current isnt null
    while(current != NULL)
    {
        //compare strings if the same
        if(strcmp(current->word, word) == 0)
        {
            //set previous next to skip current and go to next
            previous->next = current->next;

            //free all of current and return true
            free(current->word);
            free(current->definition);
            freeSynonymsOrAntonyms(current->synonyms, current->synonymsCount);
            freeSynonymsOrAntonyms(current->antonyms, current->antonymsCount);
            free(current);
            return true;
        }
    }
    //else return false
    return false;
}

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
    DictionaryEntry *table[], const char *inputFile, const char *outputFile)
{
    //declare var
    int index;
    DictionaryEntry* NewEntry;
    ReplacementEntry synonyms[MAX_WORDS];
    int randomIndex;

    //set up files
    FILE* in_file = fopen(inputFile, "r");
    FILE* out_file = fopen(outputFile, "w");

    //if eith file cant open just return
    if(in_file == NULL)
    {
        return;
    }

    if(out_file == NULL)
    {
        return;
    }

    //set the seed
    srand(time(NULL));

    //while you can search for word till end of file
    while(fscanf(in_file, "%s", NewEntry->word) != EOF)
    {
        //set the index as findreplacement
        index = findReplacement(synonyms, NewEntry->synonymsCount,
            NewEntry->word);

        //if index is -1
        if(index == -1)
        {   
            //set new entry to the searched word
            NewEntry = searchWord(table, NewEntry->word);

            //if new entry exists and is more than 0
            if(NewEntry != NULL && NewEntry->synonymsCount > 0)
            {
                //generate random number from synonym count
                randomIndex = rand() % NewEntry->synonymsCount;
                //copy and replace
                strcpy(synonyms[NewEntry->synonymsCount].word, NewEntry->word);
                //add to replacement list
                strcpy(synonyms[NewEntry->synonymsCount].replacement, 
                    NewEntry->synonyms[randomIndex]);
                //add count
                NewEntry->synonymsCount++;

                //add to output file
                fprintf(out_file, "%s ", NewEntry->synonyms[randomIndex]);
            }
            //add inout to outout
            fprintf(out_file, "%s ", NewEntry->word);
        }
        //use index to access synonym
        fprintf(out_file, "%s ", synonyms[index].replacement);

    }
    //close both files
    fclose(in_file);
    fclose(out_file);
}


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
    DictionaryEntry *table[], const char *inputFile, const char *outputFile)
{
    //delcare vars
    int index;
    DictionaryEntry* NewEntry;
    ReplacementEntry antonyms[MAX_WORDS];
    int randomIndex;

    //set up files
    FILE* in_file = fopen(inputFile, "r");
    FILE* out_file = fopen(outputFile, "w");

    //if files cant open return
    if(in_file == NULL)
    {
        return;
    }

    if(out_file == NULL)
    {
        return;
    }

    //generate seed
    srand(time(NULL));

    //while loop till end of file
    while(fscanf(in_file, "%s", NewEntry->word) != EOF)
    {
        //index = find replacement
        index = findReplacement(antonyms, NewEntry->antonymsCount,
            NewEntry->word);
        // index is -1
        if(index == -1)
        {
            //search word
            NewEntry = searchWord(table, NewEntry->word);

            //if word found && has antonym
            if(NewEntry != NULL && NewEntry->antonymsCount > 0)
            {
                //randomindex
                randomIndex = rand() % NewEntry->antonymsCount;
                //strcpy
                strcpy(antonyms[NewEntry->antonymsCount].word, NewEntry->word);
                //replace
                strcpy(antonyms[NewEntry->antonymsCount].replacement, 
                    NewEntry->antonyms[randomIndex]);
                //add antonym
                NewEntry->antonymsCount++;

                //add to output file
                fprintf(out_file, "%s ", NewEntry->antonyms[randomIndex]);
            }
            //add input to output
            fprintf(out_file, "%s ", NewEntry->word);
        }
        //use index to access the antonyms
        fprintf(out_file, "%s ", antonyms[index].replacement);

    }
    //close the files
    fclose(in_file);
    fclose(out_file);
}



/**
 * Task 6: Display All Words in the Dictionary
 * Input arguments: DictionaryEntry *table[] - dictionary hash table
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void displayDictionary(DictionaryEntry *table[])
{
    //loop for the table size
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        //current is the table at looped index
        DictionaryEntry* current = table[i];

        //while current is not null
        while(current)
        {
            //do all the print statements
            printf("Word: %s\n", current->word);
            printf("Definition: %s\n", current->definition);
            for(int j = 0; j < current->synonymsCount; j++)
            {
                printf("Synonyms: %s\n", current->synonyms[j]);
            }
            for(int j = 0; j < current->antonymsCount; j++)
            {
                printf("Antonyms: %s\n", current->antonyms[j]);
            }
            //advance current
            current = current->next;
        }
    }
}


/**
 * Function: hash
 * Input arguments: const char *word - word to hash
 * Output argument: none
 * Return: unsigned int - hash index for the word
 * Dependencies: none
 */
unsigned int hash(const char *word)
{
    //value = 0
    unsigned int value = 0;

    //while word isnt ending in \0
    while(*word != '\0')
    {
        //value * 31 + word is new value
        value = (value * 31) + *word;
        //increment word
        word++;
    }
    //return value % table size
    return value % TABLE_SIZE;
}


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
    ReplacementEntry replacements[], int count, const char *word)
{

    //loop until count
    for(int i = 0; i < count; i++)
    {
        //if theyre the same word
        if(strcmp(word, replacements[i].word) == 0)
        {
            //return the index found at
            return i;
        }
    }
    //else return -1
    return -1;
}


/**
 * Function: copyString
 * Input arguments: const char *str - the string to copy
 * Output argument: None
 * Return: char* - a pointer to the newly allocated string that is a copy of the input string, 
 *                or NULL if the input string is NULL or memory allocation fails
 * Dependencies: malloc, strlen, strcpy
 */
char *copyString(const char *str) 
{
    // if the input string is NULL
    if (str == NULL)  
    {
        // there is nothing to copy, return NULL
        return NULL;  
    }
    // calculate the length of the string + 1 for the null terminator
    size_t len = strlen(str) + 1;
    // allocate memory for the new string
    char *copy = (char *)malloc(len);
    // if memory allocation was successful
    if (copy != NULL)
    {
        // copy the original string to the new memory location
        strcpy(copy, str);  
    }
    // return the pointer to the newly copied string
    return copy;
}

/**
 * Function: freeSynonymsOrAntonyms
 * Input arguments: char **arr - array to free
 *                  int count - number of elements in the array
 * Output argument: arr is updated
 * Return: none
 * Dependencies: stdlib.h - free
 */
void freeSynonymsOrAntonyms(char **arr, int count) 
{
    // if the array is NULL
    if (arr != NULL)
    {
        // traverse the array
        for (int i = 0; i < count; i++)
        {
            // free each dynamically allocated string
            free(arr[i]);
        }
        // free the array itself
        free(arr);
    }
}


