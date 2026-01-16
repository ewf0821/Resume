# put your code for loadBoard, printBoard, possibleMoves here.
def loadBoard(filename):
    #load the array
    board = []
    #open the file
    with open(filename, "r") as file:
        #read the lines in the file
        for line in file:
            #get rid of all the whitespae
            row = line.strip()
            #add to this list
            board.append(row)
    return board

def printBoard(board):
    #print the array
    for row in board:
        #without brackets and commas
        print(row)

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
    print(moves)





print(">>> myBoard = loadBoard('board.txt') #loads the specified file into a myBoard variable")
myBoard = loadBoard("board.txt")
print()

print(">>> printBoard(myBoard)")
printBoard(myBoard)
print()

print(">>> possibleMoves((0,0), myBoard)")
possibleMoves((0,0),myBoard)
print()

print(">>> possibleMoves((2,2), myBoard)")
possibleMoves((2,2),myBoard)
