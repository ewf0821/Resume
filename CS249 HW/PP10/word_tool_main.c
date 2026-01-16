// header file
#include "word_tool_lib.h"

// main function
int main() 
{
    // initialize the hash table
    DictionaryEntry *dictionary[TABLE_SIZE] = {NULL};  

    // create a variable to store the user's option
    int choice = 0;
    // whil the user does not want to exit
    while (choice != 7) 
    {   
        // print the menu for the word tool application
        printf("\nWord Tool Menu:\n");
        printf("1. Add a New Word to the Dictionary\n");
        printf("2. Search for a Word in the Dictionary\n");
        printf("3. Remove a Word from the Dictionary\n");
        printf("4. Replace Words with Synonyms in a Text\n");
        printf("5. Replace Words with Antonyms in a Text\n");
        printf("6. Display All Words in the Dictionary\n");
        printf("7. Exit\n");

        // prompt the user for the option
        printf("Enter your choice: ");
        // read the option
        scanf("%d", &choice);

        // declare variables to store user input
        char word[100];
        char definition[256];
        char *synonyms[10];
        char *antonyms[10];
        int synonymCount;
        int antonymCount;

        // choose user's option
        switch (choice)
        {
            // add a new word to the dictionary
            case 1:
                // prompt the user to enter the word
                printf("Enter the word: ");
                // read the word
                scanf("%s", word);
                // consume the newline character from scanf buffer
                getchar();
                // prompt the user to enter the word's definition
                printf("Enter the definition: ");
                // read the string until the user hits the return (enter) key
                scanf(" %[^\n]", definition);
                // prompt the user to enter the number of synonyms
                printf("Enter number of synonyms: ");
                // read the number of synonyms
                scanf("%d", &synonymCount);
                // onsume the newline character left after number input
                getchar();
                // loop through the number of synonym count
                for (int i = 0; i < synonymCount; i++)
                {
                    // allocate memory for the current synonym
                    synonyms[i] = (char *)malloc(50);
                    // prompt the user to enter the current synonym
                    printf("Enter synonym %d: ", i + 1);
                    // read the synonym until user hits the return (enter) key
                    scanf(" %[^\n]", synonyms[i]);
                }

                // prompt the user to enter the number of antonyms for the word
                printf("Enter number of antonyms: ");
                // read the number of antonyms
                scanf("%d", &antonymCount);
                // consume the newline character left after number input
                getchar();
                
                // loop through the number of antonym count
                for (int i = 0; i < antonymCount; i++) 
                {
                    // allocate memory for the current antonym
                    antonyms[i] = (char *)malloc(50);
                    // prompt the user to enter the antonym
                    printf("Enter antonym %d: ", i + 1);
                    // read the antonym
                    scanf(" %[^\n]", antonyms[i]);  
                }

                // add the new word to the dictionary
                addWord(
                    dictionary, word, definition, synonyms, synonymCount, 
                    antonyms, antonymCount);
                // end case
                break;
            // search for a word in the dictionary
            case 2:
                // prompt for the word they want to search
                printf("Enter the word to search: ");
                // read the word
                scanf("%s", word);

                // store the result in entry
                DictionaryEntry *entry = searchWord(dictionary, word);
                
                // if the word was found
                if (entry) 
                {
                    // print its definition
                    printf("Definition: %s\n", entry->definition);
                }
                // otherwise
                else
                {
                    // print a message
                    printf("Word not found.\n");
                }
                // end case
                break;
            // remove a word from the dictionary
            case 3:
                // prompt the user for the word they want to remove
                printf("Enter the word to remove: ");
                // read the word
                scanf("%s", word);

                // if the word was removed successfully
                if (removeWord(dictionary, word)) 
                {
                    // print a message
                    printf("Word removed successfully.\n");
                }
                // otherwise
                else 
                {
                    // print a message
                    printf("Word not found.\n");
                }
                // end case
                break;
            // replace words with synonyms in a text file
            case 4:
                // inform the user about the next action
                puts("Replacing words in text_file.txt with synonyms.........");
                // replace words in the file with synonyms
                replaceWithSynonyms(
                    dictionary, "text_file.txt", "synonym_output.txt");
                // print a message
                puts(
                    "Synonym replacement completed. Check synonym_output.txt.");
                // end case
                break;
            // Replace words with antonyms in a text file
            case 5:
                // inform the user about the next action
                puts("Replacing words in text_file.txt with antonyms.........");
                // replace words in the file with antonyms
                replaceWithAntonyms(
                    dictionary, "text_file.txt", "antonym_output.txt");
                // print a message
                puts("Antonym replacement completed. Check antonym_output.txt");
                // end case
                break;
            // display all words in the dictionary
            case 6:
                // print all dictionary entries
                displayDictionary(dictionary);
                // end case
                break;
            // exit the application
            case 7:
                // prints a message
                printf("Exiting the application.\n");
                // end case
                break;
            // handle invalid choices
            default:
                // print a message
                printf("Invalid choice. Please try again.\n");
                // end case
                break;
        }
    }
    // return success
    return 0;
}
