#import tkinter
import tkinter as tk
import sys
import time

#set up a big class for all my functions
class Halma:
    def __init__(self, root, board_size = 8, turn_time = 60, player_color = "red", ai_color = None):
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

        #set the ai color
        if ai_color:
            self.ai = AI(ai_color, time_limit = 5, board_size = self.size)
        else:
            self.ai = None

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
        
        if self.ai and self.current_turn == self.ai.color:
            self.root.after(500, self.ai_move)
        
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

    #functon all the ai relating things
    def ai_move(self):
        #if there is no ai
        if not self.ai:
            #return
            return
        
        #get the board state
        board_state = self.piece_color.copy()
        #sets alpha beta pruning and moves
        move = self.ai.choose_move(board_state, alpha_beta = False)

        #if there is a move
        if move:
            #set start and end to move
            start, end = move
            #highlight the piece
            self.selected = start
            #move the piece and set all the extra parameters to end
            self.move_piece(*end)
    



class AI: 
    def __init__(self, color, time_limit = 5, board_size = 8):
        #ai player color
        self.color = color
        #ai time limit
        self.time_limit = time_limit
        #time for when ai starts thinking
        self.start = 0
        #number of prines
        self.prunes = 0
        #number of nodes
        self.nodes = 0
        #opponents color
        self.opponent_color = "green" if color == "red" else "red"
        #board size
        self.board_size = board_size
        #max depth reached
        self.max_depth_reached = 0


    #choses a move and wheather alpha beta pruning is used
    def choose_move(self, board_state, alpha_beta = True):
        #start the timer
        self.start = time.time()
        #set the number of prunes
        self.prunes = 0
        #set the number of noes
        self.nodes = 0

        #set default values
        best_move = None
        depth = 1
        search = True

        #while search is true
        while search:

            #if time limit is reached
            if time.time() - self.start >= self.time_limit:
                #stop searching
                search = False  
            #eslse
            else:
                #if alpha beta
                if alpha_beta:
                    #minmax
                    value, move = self.minmax(board_state, depth, float('-inf'), float('inf'), True)

                #else its not apha beta prune
                else:
                    #use the noprune version of minmax
                    value, move = self.minmax_noprune(board_state, depth, True)

                #if the move is not none
                if move is not None:
                    #set the best move
                    best_move = move
                    #set the max depth to the current depth
                    self.max_depth_reached = depth

                #increment the depth
                depth += 1

            #if time limit is reached
            if time.time() - self.start >= self.time_limit:
                #stop searching
                search = False
        
        #get the time
        time_spent = time.time() - self.start
        #print all the print statements
        print("Ai Stats:")
        print(f"Alpha-Beta Pruning: {'ENABLED' if alpha_beta else 'DISAIBLED'}")
        print(f"Plies Traveled: {self.max_depth_reached}")
        print(f"Time Spent: {time_spent: .3} seconds")
        print(f"Nodes/Boards Explored: {self.nodes}")
        if alpha_beta:
            print(f"Prunes: {self.prunes}")

        #return best move
        return best_move


    #minmax but its noprune
    def minmax_noprune(self, board_state, depth, maximizing):
        #increment the number of nodes
        self.nodes += 1

        #if time limit is reached
        if time.time() - self.start >= self.time_limit:
            #if the time limit is reached return the heuristics
            return self.heuristics(board_state), None

        #if the depth is 0
        if depth == 0:
            #return the heuristics
            return self.heuristics(board_state), None

        #if its the end of the game
        if self.terminal_state(board_state):
            #return the heuristics
            return self.heuristics(board_state), None
        
        #get the current color
        current_color = self.color if maximizing else self.opponent_color
        #get the valid moves
        valid_moves = self.all_valid_moves(board_state, current_color)

        #if there are no valud moves
        if len(valid_moves) == 0:
            #return the heuristics
            return self.heuristics(board_state), None
        
        #if maximizing
        if maximizing: 
            #set the max value
            max_value = float('-inf')
            #and set the best move to none
            best_move = None

            #for each move
            for move in valid_moves:
                #use the move
                new_state = self.use_move(board_state, move)
                #use the noprune version
                score, _ = self.minmax_noprune(new_state, depth - 1, False)

                #if the score is greater than the max value
                if score > max_value:
                    #set the max value
                    max_value = score
                    #set the best move
                    best_move = move

            #return the max value
            return max_value, best_move
        
        #else
        else:
            #set the min value
            min_value = float('inf')
            #and set the best move to none
            best_move = None

            #for each move
            for move in valid_moves:

                #use the new move
                new_state = self.use_move(board_state, move)
                #use the noprune version
                score, _ = self.minmax_noprune(new_state, depth - 1, True)

                #if the score is less than the min value
                if score < min_value:
                    #set the min value
                    min_value = score
                    #set the best move
                    best_move = move

            #return the min value
            return min_value, best_move
        

    #minmax pruning version
    def minmax(self, board_state, depth, alpha, beta, maximizing):
        #increment the nodes
        self.nodes += 1

        #if time limit is reached
        if time.time() - self.start >= self.time_limit:
            #return the heuristics
            return self.heuristics(board_state), None

        #if the depth is 0
        if depth == 0:
            #return the heuristics
            return self.heuristics(board_state), None

        #if its the end of the game
        if self.terminal_state(board_state):
            #return the heuristics
            return self.heuristics(board_state), None
        
        #get the current color
        current_color = self.color if maximizing else self.opponent_color

        #get the valid moves
        valid_moves = self.all_valid_moves(board_state, current_color)

        #if there are no valud moves
        if len(valid_moves) == 0:
            #return the heuristics
            return self.heuristics(board_state), None
        
        #if maximizing
        if maximizing: 
            #set the max value
            max_value = float('-inf')
            #and set the best move to none
            best_move = None

            #for each move
            for move in valid_moves:
                #if beta is less then alpha
                if beta <= alpha:
                    #increment the number of prunes and break
                    self.prunes += 1
                    break
                
                #use the move
                new_state = self.use_move(board_state, move)

                #use the prune version
                score, _ = self.minmax(new_state, depth - 1, alpha, beta, False)

                #if the score is greater than the max value
                if score > max_value:
                    #set the max value
                    max_value = score
                    #set the best move
                    best_move = move

                #if the score is greater than alpha
                if score > alpha:
                    #set alpha
                    alpha = score

            #return the max value
            return max_value, best_move

        #else     
        else:
            #set the min value
            min_value = float('inf')
            #and set the best move to none
            best_move = None

            #for each move
            for move in valid_moves:
                #if beta is less than or equal to alpha
                if beta <= alpha:
                    #increment the number of prunes and break
                    self.prunes += 1
                    break

                #use the move
                new_state = self.use_move(board_state, move)

                #use the prune version
                score, _ = self.minmax(new_state, depth - 1, alpha, beta, True)

                #if the score is less than the min value
                if score < min_value:
                    #set the min value
                    min_value = score
                    #set the best move
                    best_move = move

                #if the score is less than beta
                if score < beta:
                    #set beta
                    beta = score

            #return the min value
            return min_value, best_move

    #all valid moves the ai can make
    def all_valid_moves(self, board_state, color ):
        #create a l;ist of moves
        moves = []

        #for each piece
        for position, piece_color in board_state.items():
            #if the piece color is the player color
            if piece_color == color:

                #get the piece moves
                piece_moves = self.piece_moves(board_state, position[0], position[1])
                #for each end position
                for end_position in piece_moves:
                    #add the move
                    moves.append((position, end_position))

        #return the moves
        return moves
    
    #piece moves
    def piece_moves(self, board, row, col):
        #create a list
        moves = []

        #get the directions
        directions = [(-1, -1), (-1, 0), (-1, 1),
                       (0, -1), (0, 1), (1, -1),
                         (1, 0), (1, 1)]
        
        #for each direction
        for dr, dc in directions:
            #calculate the new row and col
            new_row = row + dr
            new_col = col + dc

            #if the new row and col are in bounds
            if (0 <= new_row < self.board_size and 0 <= new_col < self.board_size and 
                        (new_row, new_col) not in board):
                #add the move
                moves.append((new_row, new_col))

        #find the jumps
        jumps = self.find_jumps_ai(board, row, col, set())

        #for each jump
        for jump in jumps:
            #add the jump
            moves.append(jump)

        #return the moves
        return moves
    
    #find the jumps for the ai
    def find_jumps_ai(self, board, row, col, visited):

        #add the current to the visited
        visited.add((row,col))

        #create a list
        jumps = []

        #get the directions
        directions = [(-1, -1), (-1, 0), (-1, 1),
                       (0, -1), (0, 1), (1, -1),
                         (1, 0), (1, 1)]
        
        #for each direction
        for dr, dc in directions:
            #calculate the new row and col
            new_row = row + dr
            new_col = col + dc

            #set the jump row and columns
            jump_r = row + 2*dr
            jump_c = col + 2*dc

            #if the new row and col are in bounds and not visited
            if ((new_row, new_col) in board and 0 <= jump_r < self.board_size and 
                        0 <= jump_c < self.board_size and (jump_r, jump_c) not in board
                        and (jump_r, jump_c) not in visited):
                    #add the jump
                    jumps.append((jump_r, jump_c))
                    #find the jumps for multi jumps
                    jumps.extend(self.find_jumps_ai(board, jump_r, jump_c, visited.copy()))

        #return the jumps
        return jumps
    

    #function to suggest the move wihtout changing the board
    def use_move(self, board, move):
        #copy the baord
        new_board = board.copy()

        #set start and end to the current move
        start, end = move

        #get the piece color
        color = new_board[start]

        #remove the piece
        del new_board[start]

        #move the piece
        new_board[end] = color

        #return the board
        return new_board
    
    #function for calculating the heuristics
    def heuristics(self, board):
        #set the score to 0
        score = 0

        #for each piece
        for position, color in board.items():
            #get the row
            row = position[0]

            #if the piece color is the player color
            if color == self.color:
                #if the current color is green
                if self.color == "green":
                    #subtract the row from the score
                    score -= row
                #else
                else:
                    #add the row to the score
                    score += row

            #else 
            else:
                #if the current color is green
                if self.color == "green":
                    #add the row to the score
                    score += row
                #else
                else:
                    #subtract the row from the score
                    score -= row

        #return the score
        return score
    
    #this function checks if the game is over
    def terminal_state(self, board_state):
        #get the start size
        start_size = self.board_size // 2

        #get the red goal
        red_goal = set()
        #for row in range of the board size
        for row in range(self.board_size - start_size, self.board_size):
            piece_row = row - (self.board_size - start_size) + 1
            #for col in range of the board size
            for col in range(self.board_size - piece_row, self.board_size):
                #add the position to red goal
                red_goal.add((row, col))

        #get the green goal
        green_goal = set()
        #for row in range of the start size
        for row in range(start_size):
            #for col in range of the start size - row
            for col in range(start_size - row):
                #add the position to green goal
                green_goal.add((row, col))


        #get the red count which is the number of red pieces in red goal
        red_count = sum(1 for position, color in board_state.items()
                        if color == "red" and position in red_goal)

        #get the green count which is the number of green pieces in green goal
        green_count = sum(1 for position, color in board_state.items()
                          if color == "green" and position in green_goal)
        
        #if the red count is equal to the red goal or the green count is equal to the green goal
        return red_count == len(red_goal) or green_count == len(green_goal)




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
    Halma(root, board_size, turn_time, player_color, ai_color = "green")
    root.mainloop()

#call main
main()