import sys
import time


def loadBoard(filename):
    #load the array
    board = []
    #open the file
    with open(filename, "r") as file:
        #read the lines in the file
        for line in file:
            #get rid of all the whitespae
            row = line.strip().split()
            #add to this list
            board.append([char.upper() for char in row])
    return board

def printBoard(board):
    #print the array
    for row in board:
        #without brackets and commas
        print(' '.join(row))

def possibleMoves(position, board):
    #array for possible moves
    row,col = position
    #createm moves list
    moves = []
    #check all directions
    for change_row in [-1, 0, 1]:
        for change_col in [-1, 0, 1]:
            #0,0 would be no change so we can skip that
            if change_row == 0 and change_col == 0:
                continue
            #set the new row and col using our change 
            new_row = row + change_row
            new_col = col + change_col
            #then check if they're in the bounds
            if (new_row < 0 or new_row >= len(board)) or (new_col < 0 or new_col >= len(board[0])):
                continue
            #add to the list
            moves.append((new_row,new_col))
    return moves

def loadDictionary(filename):
    #set for dictionary
    dictionary = set()
    #open the file
    with open(filename, "r") as file:
    #loop through file
        for line in file:
            #get rid of whitespaces and capitalize
            word = line.strip().upper()
            #if there is a word add to the dictionary
            if word:
                dictionary.add(word)
    #return the frozen set
    return frozenset(dictionary)

def possibleWord(board, dictionary):

    #create a set for all the words
    found_words = set()
    #set max rows and cols
    max_rows = len(board)
    max_cols = len(board[0])
    #set visited count
    visited_count = 0

    #assume we have to do depth-first search
    def search():

def checkIsValid(word, dictionary):

    #upper all words
    word = word.upper()

    #check if the word is in the dictionary and set prefix to false
    valid_word = word in dictionary
    valid_prefix = False

    #check all the words in the dictionary and check if they start with word
    #cant use word instead of dictionary_word because we use it later in the function
    for dictionary_word in dictionary:
        if dictionary_word.startswith(word) and len(dictionary_word) > len(word):
            valid_prefix = True
            break

    #set all the states depending on what is true
    #if prefix and word return both
    if valid_word and valid_prefix:
        return "BOTH"
    #if just word return word
    elif valid_word:
        return "WORD"
    #if just prefix return prefix
    elif valid_prefix:
        return "PREFIX"
    #else return none
    else:
        return "NONE"
    
#main function
def main():

    #setting dictionary and board files for the command line
    dict_file = sys.argv[1]
    board_file = sys.argv[2]

    #setting the dictionary and board
    dictionary = loadDictionary(dict_file)
    board = loadBoard(board_file)

    #print the board
    print("OUTPUT FROM AN EXUASTIVE")
    printBoard(board)
    print("And we're off!")

    #set start and end time and get elapsed time
    start_time = time.time()
    end_time = time.time()
    elapsed = end_time - start_time

    #print elapsed time
    print("All done ")
    print(f"Searched total of {} moves in {elapsed:.3f} seconds")




    
