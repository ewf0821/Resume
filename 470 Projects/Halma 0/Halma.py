#import tkinter
import tkinter as tk

#set up a big class for all my functions
class Halma:
    def __init__(self, root):
        #root = tkinter.Tk()
        self.root = root
        #set the board size
        self.size = 8
        #and size of each box on the board
        self.cell_size = 45

        #create the canvase for tkinter
        self.canvas = tk.Canvas(root, width=self.size * self.cell_size, 
                                height=self.size * self.cell_size)
        #and pack it
        self.canvas.pack()

        #dictionary for all the piece colors
        self.piece_color = {}
        #dictionary for all the piece locations
        self.all_pieces = {}
        #highlighted piece
        self.selected = None
        #highlighted moves
        self.highlighted_moves = []
        #valid moves
        self.valid_moves = []

        #draw the board
        self.board()
        #place the pieces
        self.place_piece()
        #bind the click
        self.canvas.bind("<Button-1>", self.click)

    #function for drawing the board
    def board(self):
        #for rows in size
        for row in range(self.size):
            #for cols in size
            for col in range(self.size):
                #create a rectangle for each row and column that has the given
                #cell size
                x1 = col * self.cell_size
                y1 = row * self.cell_size
                x2 = x1 + self.cell_size
                y2 = y1 + self.cell_size

                #create the rectangles
                self.canvas.create_rectangle(x1, y1, x2, y2, fill="tan",
                                              outline="black")

    #function for drawing my pieces
    def draw_piece(self, row, col, color):
        #calculate the size of the piece
        x1 = col * self.cell_size
        y1 = row * self.cell_size
        x2 = (col + 1) * self.cell_size
        y2 = (row + 1) * self.cell_size

        #create the piece
        piece_id = self.canvas.create_oval(x1, y1, x2, y2, fill=color,
                                            outline="black")
        #add the pieces to their dictionaries
        self.piece_color[(row, col)] = color
        self.all_pieces[(row, col)] = piece_id

    #function for placing all the pieces at the start
    def place_piece(self):
        #calculate the size of the pieces
        start_size = self.size // 2
        
        #for row in range of the board size
        for row in range(start_size):
            #for col in range of the board size
            for col in range(start_size - row):
                #draw the white pieces
                self.draw_piece(row, col, "white")

        #for row in range of the board size - start size
        for row in range(self.size - start_size, self.size):
            #for col in range of the board size
            piece_row = row - (self.size - start_size) + 1

            for col in range(self.size - piece_row, self.size):
                self.draw_piece(row, col, "black")
    
    def click(self, click):

        #get the x and y coordinates for clicks
        x = click.x
        y = click.y

        #calculate pixel to board coordinates
        row = y // self.cell_size
        col = x // self.cell_size

        #if the click is on the board
        if 0 <= row < self.size and 0 <= col < self.size:
            #if the click is on a piece
            if (row, col) in self.piece_color:
                #get rid of previous highlighted piece
                self.unhighlight_piece()
                #select the new piece
                self.selected = (row, col)
                #highlight the piece
                self.highlight_piece()
                #show the possible moves
                self.possible_moves()
            #else if the click is on a valid move square
            elif self.selected and self.is_valid(row, col):
                #move the piece
                self.move_piece(row, col)
            else:
                #unhighlight the piece
                self.unhighlight_piece()
                #unselect the piece
                self.selected = None

    #function for highlighting a piece
    def highlight_piece(self):
        #if there is a selected piece
        if self.selected:
            #get the coordinates
            row, col = self.selected
            #calculate the coordiates of the piece
            x1 = col * self.cell_size
            y1 = row * self.cell_size
            x2 = (col + 1) * self.cell_size
            y2 = (row + 1) * self.cell_size

            #create a yellow ractangle on the selected piece
            self.highlighted_piece = self.canvas.create_rectangle(
                                                x1, y1,x2, y2, fill="yellow")
            #add it to the highlighted moves
            self.highlighted_moves.append(self.highlighted_piece)

    #function for unhighlighting a piece
    def unhighlight_piece(self):
        #if the item is in highlighted moves
        for item in self.highlighted_moves:
            #delete it
            self.canvas.delete(item)

        #set highlighted moves to empty
        self.highlighted_moves = []
        #set valid moves to empty
        self.valid_moves = []

    #function for finding possible moves
    def possible_moves(self):
        #get all the directions for possible moves
        directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1),
                       (1, -1), (1, 0), (1, 1)]

        #for each direction in directions
        for direction in directions:
            #calculate new row and col based on direction
            new_row = self.selected[0] + direction[0]
            new_col = self.selected[1] + direction[1]

            #if the new row and col are in the board and is empty
            if (0 <= new_row < self.size and 0 <= new_col < self.size
                            and (new_row, new_col) not in self.piece_color):
                #get the coordinates for the square
                x1 = new_col * self.cell_size
                y1 = new_row * self.cell_size
                x2 = (new_col + 1) * self.cell_size
                y2 = (new_row + 1) * self.cell_size

                #highlight the square green and add it to valid moves and highlighted moves
                self.highlighted_moves.append(self.canvas.create_rectangle(
                                                x1, y1, x2, y2, fill="green"))
                self.valid_moves.append((new_row, new_col))

        #find all possible jumps for the piece incliding multiple jumps
        all_jump_spots = self.find_jumps(self.selected[0],
                                          self.selected[1], set())
        #for each jump in all_jump_spots
        for jump_spot in all_jump_spots:
            #get the coordingates
            x1 = jump_spot[1] * self.cell_size
            y1 = jump_spot[0] * self.cell_size
            x2 = (jump_spot[1] + 1) * self.cell_size
            y2 = (jump_spot[0] + 1) * self.cell_size
            
            #highlight the square red and add it to the list of valid moves
            self.highlighted_moves.append(self.canvas.create_rectangle(
                                                    x1, y1, x2, y2, fill="red"))
            self.valid_moves.append(jump_spot)
                
    #function for valid moves
    def is_valid(self, new_row, new_col):
        #if the new row and col are in valid moves
        if (new_row, new_col) in self.valid_moves:
            #return true
            return True
        #else return valse
        return False

    #function for moving pieces
    def move_piece(self, new_row, new_col):
        #delete the piece at its old location
        self.canvas.delete(self.all_pieces[self.selected])
        #draw the piece at its new loction
        self.draw_piece(new_row, new_col, self.piece_color[self.selected])

        #delete the piece from the dictionaries
        del self.piece_color[self.selected]
        del self.all_pieces[self.selected]

        #unhighlight the piece
        self.unhighlight_piece()

        #set selected to none
        self.selected = None

    #function for finding jumps
    def find_jumps(self, row, col, visited):
        #create a list for visited squares and add the current to it
        visited.add((row, col))
        #craete a list for the jumps
        jumps = []

        #get all the directions
        directions = [(-1, -1), (-1, 0), (-1, 1),
                       (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]

        #for each direction
        for direction in directions:
            piece_row = row + direction[0]
            piece_col = col + direction[1]

            #calculate the coordinates for the jump
            jump_row = row + 2*direction[0]
            jump_col = col + 2*direction[1]

            #if the piece is in the board and the jump is in the board
            if (0 <= piece_row < self.size and 0 <= piece_col < self.size 
                            and (piece_row, piece_col) in self.piece_color):

                #if the jump is in the board and not visited
                if (0 <= jump_row < self.size and 0 <= jump_col < self.size 
                                and (jump_row, jump_col) not in self.piece_color 
                                and (jump_row, jump_col) not in visited):
                    #add that jump to the list
                    jumps.append((jump_row, jump_col))

                    #recursively call find jumps to get more jumps and copy the 
                    #visited list
                    more_jumps = self.find_jumps(jump_row, jump_col, 
                                                 visited.copy())

                    #add all the more jumps to the jumps list
                    jumps.extend(more_jumps)
        #return the list of jumps
        return jumps
            
#main
def main():
    root = tk.Tk()
    Halma(root)
    root.mainloop()

#call main
main()