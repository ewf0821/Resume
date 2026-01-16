#import tkinter
import tkinter as tk
import sys

#set up a big class for all my functions
class Halma:
    def __init__(self, root, board_size = 8, turn_time = 60, player_color = "red"):
        #root = tkinter.Tk()
        self.root = root
        #set the board size
        self.size = board_size
        #turn time limit
        self.turn_time = turn_time
        #set default player color
        self.player_color = player_color.lower()
        
        #and size of each box on the board
        self.cell_size = 45
        #add an offset so that there is an edge on the canvas
        self.offset = self.cell_size // 2
        #add an offset for the top
        self.top_offset = 40

        #create the canvase for tkinter
        self.canvas = tk.Canvas(root, width=self.size * self.cell_size + (2 *self.offset), 
                                height=self.size * self.cell_size + (2 *self.offset) + self.top_offset)
        
        #and pack it
        self.canvas.pack()

        #set game state variuables
        self.current_turn = "red"
        self.current_time = self.turn_time
        self.red_score = 0
        self.green_score = 0

        #center the game state
        x = (self.size * self.cell_size + (2 *self.offset)) // 2
        
        y = self.top_offset // 2

        #set the game state at the top of the screen to show turn time and score
        self.gamestate = self.canvas.create_text(x, y, 
                                                 text=f"Player: {self.current_turn.upper()} | Time: {self.current_time} | Score: {self.red_score} - {self.green_score}", 
                                                 font=("Arial", 10))
        #start the timer
        self.timer()

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
                x1 = col * self.cell_size + self.offset
                y1 = row * self.cell_size + self.offset + self.top_offset
                x2 = x1 + self.cell_size
                y2 = y1 + self.cell_size

                #create the rectangles
                self.canvas.create_rectangle(x1, y1, x2, y2, fill="tan",
                                              outline="black")
        for row in range (self.size):
            #add letters for 1 - end of the board
            x = self.offset // 2
            y = row * self.cell_size + self.offset + self.offset // 2 + self.top_offset

            #create the letters
            self.canvas.create_text(x, y, text=str(row + 1), font=("Arial", 10))


        for col in range (self.size):
            #add numbers for a - end of the board
            x = col * self.cell_size + self.offset + self.offset // 2
            y = self.size * self.cell_size + self.offset + self.offset // 2 + self.top_offset

            #create the numbers
            self.canvas.create_text(x, y, text=chr(col + 97), font=("Arial", 10))



    #function for drawing my pieces
    def draw_piece(self, row, col, color):
        #calculate the size of the piece
        x1 = col * self.cell_size + self.offset 
        y1 = row * self.cell_size + self.offset + self.top_offset
        x2 = (col + 1) * self.cell_size + self.offset
        y2 = (row + 1) * self.cell_size + self.offset + self.top_offset

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
                self.draw_piece(row, col, "red")

        #for row in range of the board size - start size
        for row in range(self.size - start_size, self.size):
            #for col in range of the board size
            piece_row = row - (self.size - start_size) + 1

            for col in range(self.size - piece_row, self.size):
                self.draw_piece(row, col, "green")
    
    def click(self, click):

        #get the x and y coordinates for clicks
        x = click.x - self.offset
        y = click.y - self.offset - self.top_offset

        #calculate pixel to board coordinates
        row = y // self.cell_size
        col = x // self.cell_size

        #if the click is on the board
        if 0 <= row < self.size and 0 <= col < self.size:
            #if the click is on a piece
            if (row, col) in self.piece_color:
                if self.piece_color[(row, col)] == self.current_turn:
                    #get rid of previous highlighted piece
                    self.unhighlight_piece()
                    #select the new piece
                    self.selected = (row, col)
                    #highlight the piece
                    self.highlight_piece()
                    #show the possible moves
                    self.possible_moves()
                else:
                    self.canvas.itemconfig(self.gamestate, text =f"Not Your Piece")
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
            x1 = col * self.cell_size + self.offset
            y1 = row * self.cell_size + self.offset + self.top_offset
            x2 = (col + 1) * self.cell_size + self.offset
            y2 = (row + 1) * self.cell_size + self.offset + self.top_offset

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
                x1 = new_col * self.cell_size + self.offset
                y1 = new_row * self.cell_size + self.offset + self.top_offset
                x2 = (new_col + 1) * self.cell_size + self.offset
                y2 = (new_row + 1) * self.cell_size + self.offset + self.top_offset

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
            x1 = jump_spot[1] * self.cell_size + self.offset    
            y1 = jump_spot[0] * self.cell_size + self.offset + self.top_offset
            x2 = (jump_spot[1] + 1) * self.cell_size + self.offset
            y2 = (jump_spot[0] + 1) * self.cell_size + self.offset + self.top_offset
            
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
    
    def is_win(self):
        start_size = self.size // 2

        #create a set for all the red pieces in green
        red_win = set()
        #use the green start as reds end
        for row in range(self.size - start_size, self.size):
            #for col in range of the board size
            piece_row = row - (self.size - start_size) + 1
            for col in range(self.size - piece_row, self.size):
                red_win.add((row, col))

        #create a set for all the green pieces in red
        green_win = set()
        #use the red start as greens end
        for row in range(start_size):
            #for col in range of the board size
            for col in range(start_size - row):
                green_win.add((row, col))

        #count the pieces in thier goals
        red_in_green = 0
        green_in_red = 0

        #if the peices are in their respective ends add 1 to their count
        for piece, color in self.piece_color.items():
            if color == "red" and piece in red_win:
                red_in_green += 1
            elif color == "green" and piece in green_win:
                green_in_red += 1

        #if the counts are equal return the player
        if red_in_green == len(red_win):
            return "red"
        elif green_in_red == len(green_win):
            return "green"
        #else return none
        else:
            return None


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

        #check for the winner
        win = self.is_win()
        #if win is true
        if win:
            self.canvas.itemconfig(self.gamestate, 
                                    text=f"Player: {win.upper()} Wins!", 
                                    font=("Arial", 10))
            #if red is winner add to their score count
            if win == "red":
                self.red_score += 1
            #else green is winner
            else:
                self.green_score += 1

        #switch turns
        if self.current_turn == "red":
            self.current_turn = "green"
        else:
            self.current_turn = "red"

        #reset the timer
        self.current_time = self.turn_time

        #update the timer
        self.canvas.itemconfig(self.gamestate, 
                                text=f"Player: {self.current_turn.upper()} | Time: {self.current_time} | Score: {self.red_score} - {self.green_score}", 
                                font=("Arial", 10))
        
    def timer(self):

        #decrement the timer
        if self.current_time > 0:
            self.current_time -= 1

        #update the timer
        self.canvas.itemconfig(self.gamestate, 
                                text=f"Player: {self.current_turn.upper()} | Time: {self.current_time} | Score: {self.red_score} - {self.green_score}", 
                                font=("Arial", 10))
        #have the timer show for 1 full second
        self.root.after(1000, self.timer)


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
    
def commandLine():
    #set default values for the arguments
    board_size = 8
    turn_time = 60
    player_color = "red"
    
    i = 1
    #if there are arguments
    while i < len(sys.argv):
        if sys.argv[i] == "--size":
            board_size = int(sys.argv[i + 1])
            i += 2
        elif sys.argv[i] == "--time":
            turn_time = int(sys.argv[i + 1])
            i += 2
        elif sys.argv[i] == "--color":
            player_color = sys.argv[i + 1].lower()
            i += 2
        else:
            i += 1

    #return the arguments
    return board_size, turn_time, player_color

    
            
#main
def main():
    board_size, turn_time, player_color = commandLine()

    root = tk.Tk()
    root.title(f"Halma {board_size}x{board_size}")
    Halma(root, board_size, turn_time, player_color)
    root.mainloop()

#call main
main()