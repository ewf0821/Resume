// header files
#include "music_lib.h"

/**
 * Function: createPlaylist (provided)
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: updated head of the playlist
 * Return: true if the playlist is successfully loaded, false if errors occur
 * Dependencies: addSong, stdio.h, string.h
 */
bool createPlaylist(Song **playlist) 
{
    // open the file
    FILE *file = fopen(FILENAME, "r");
    // if the file could not be open
    if (file == NULL)
    {
        // print a message
        printf("Could not open file %s\n", FILENAME);
        // end the function with an error code
        return false;
    }

    // create variables to hold the readings
    char line[256];
    char title[100];
    char artist[100];
    int genre;

    // if it is the end of the file after the header
    if (fgets(line, sizeof(line), file) == NULL)
    {
        // close the file
        fclose(file);
        // file is empty, return false
        return false;
    }

    // while there is another line to read
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // parse the line using the comma separator
        char *token = strtok(line, ",");
        // if the token is not null
        if (token != NULL)
        {
            // copy the data into the title
            strcpy(title, token);
        }
        // move to the next token
        token = strtok(NULL, ",");
        // if the token is not null
        if (token != NULL)
        {
            // copy the data into the artist
            strcpy(artist, token);
        }
        // move to the next token
        token = strtok(NULL, ",");
        // if the token is not null
        if (token != NULL)
        {
            // copy into genre as an integer
            genre = atoi(token);
        }

        // add the song to the playlist casting Genre to the correct enum
        addSong(playlist, title, artist, (Genre)genre);
    }
    // close the file
    fclose(file);
    // return success
    return true;
}

/**
 * Task 1: Play the Playlist
 * Input argument: playlist - a pointer to a list of songs
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h, ctype.h
 */



/**
 * Task 2: Adding a New Song to the Playlist
 * Input argument: playlist - a double pointer to a list of songs
 *                 title - a string with the title of the song
 *                 artist - a string with the artist of the song
 *                 genre - a Genre enum for the genre of the song
 * Output argument: updated head of the playlist, if needed
 * Return: true if the song is successfully added, false otherwise
 * Dependencies: stdlib.h, stdio.h, string.h
 */



/**
 * Task 3: Removing a Song from the Playlist
 * Input argument: playlist - a double pointer to a list of songs
 *                 title - a string with the title of the song
 * Output argument: updated head of the playlist, if needed
 * Return: true if the song is successfully removed, false otherwise
 * Dependencies: stdlib.h, stdio.h, string.h
 */



/**
 * Task 4: Shuffle Play
 * Input argument: playlist - a pointer to a list of songs
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: stdlib.h, stdio.h
 */



/**
 * Task 5: Play Songs by Artist
 * Input argument: playlist - a pointer to a list of songs
 *                 artist - a string representing the artist name
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: string.h, stdio.h
 */



/**
 * Task 6: Sorting the Playlist by Genre
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist sorted by genre
 * Return: void
 * Dependencies: none
 */



/**
 * Task 7: Detecting a Cycle in the Playlist
 * Input argument: playlist - a pointer to a list of songs
 * Output argument: none
 * Return: true if the last song points to the head of the playlist,
 *         false otherwise
 * Dependencies: none
 */



/**
 * Task 8: Play Non-Stop
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is configured to be circular
 * Return: void
 * Dependencies: detectCycle
 */



/**
 * Task 9: Play Up to the End
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is configured to be linear (last points to null)
 * Return: void
 * Dependencies: detectCycle
 */



/**
 * Task 10: Reversing the Playlist
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is reversed
 * Return: void
 * Dependencies: detectCycle
 */


