# Define Searcher class here.
import warnings
warnings.filterwarnings('ignore', category=UserWarning, module='matplotlib')
from DRDViz import DRDViz
import math

class SearchNode:
    def __init__(self, label, pathcost=None, g=0, h=0, depth=0, parent=None):
        self.label = label
        self.pathcost = pathcost
        self.g = g
        self.h = h
        self.f = g + h
        self.depth = depth
        self.parent = parent

    def showverbose(self):        
        return f"{self.label};{self.depth};{self.g:.0f}; {self.h:.2f};{self.f:.2f}"
    
    def __lt__(self, other):
        return self.label < other.label
    
    #-------------- FROM THE LAST PART -----------
def hSLD(label, searcher):
    # Calculate straight-line distance (Euclidean) between label node and goal node
    node1 = None
    node2 = None
    
    # Find the two nodes in the graph
    for node in searcher.myViz.nodes:
        if node.label == label:
            node1 = node
        if node.label == searcher.goal:
            node2 = node
    
    # Calculate Euclidean distance
    if node1 and node2:
        dx = node1.x - node2.x
        dy = node1.y - node2.y
        return math.sqrt(dx*dx + dy*dy)
    
    return 0


#--------- FROM PART 0 WITH UPDATED INIT ---------
class Searcher:
    def __init__(self, file_name, searchType, verbose):
        self.myViz = DRDViz()
        self.myViz.loadGraphFromFile(file_name)
        self.start = None
        self.goal = None
        self.open = []
        self.searchType = searchType
        self.verbose = verbose
        print(f"Loaded search type {self.searchType} with map in file: {file_name}")

    def setStartGoal(self, start, goal):
        self.start = start.upper()
        self.goal = goal.upper()
        self.open.append(SearchNode(self.start,pathcost=0, g=0, h=0, depth=0, parent=None))

    def successors(self, node_label):
        children = []
        for edge in self.myViz.edges:
            if edge.endlabel1 == node_label:
                children.append(SearchNode(edge.endlabel2, pathcost=int(edge.label)))
            elif edge.endlabel2 == node_label:
                children.append(SearchNode(edge.endlabel1, pathcost=int(edge.label)))
        # Sort alphabetically by label
        return sorted(children)

    def insert_front(self, node):
        # Must handle both single node and list
        if isinstance(node, list):
            for n in reversed(node):
                self.open.insert(0, n)
        else:
            self.open.insert(0, node)

    def insert_end(self, node):
        # Must handle both single node and list
        if isinstance(node, list):
            for n in node:
                self.open.append(n)
        else:
            self.open.append(node)

    def insert_ordered(self, node):
        # Must handle both single node and list
        if isinstance(node, list):
            for n in node:
                self._insert_single(n)
        else:
            self._insert_single(node)
    
    def _insert_single(self, node):
        # Insert in order by value
        for i, existing in enumerate(self.open):
            if node.f < existing.f:
                self.open.insert(i, node)
                return
        self.open.append(node)

    def reset(self):
        self.open = []
        if self.start:
            self.open.append(SearchNode(self.start, pathcost=0, g=0, h=0, depth=0, parent=None))

#-------------- CREATED FUNCTION FOR DUPLICATES --------------
    def duplicate(self, label):
        return any(n.label == label for n in self.open)

#----------- NEW STUFF ----------

#this just checks what search type is being used and then calls the correct function
    def search(self):
        #if search type is depth
        if self.searchType == "DEPTH":
            #call dfs
            self.dfs()
        #if search type is breadth
        if self.searchType == "BREADTH":
            #call bfs
            self.bfs()
        #if search type is best
        if self.searchType == "BEST":
            #call best first
            self.greedy()
        #if search type is A*
        if self.searchType == "A*":
            #call A*
            self.astar()


#----------- DFS ------------
    def dfs(self):
        #create a set to keep track of visited nodes
        self.closed = set()
        #loop through the list of nodes
        while self.open:
            #pop the first node off the list
            node = self.open.pop(0)
            #show the node that youre going to explore
            if self.verbose:
                #function print
                print(f"Exploring node: {node.label}")

            #if current node is goal node
            if node.label == self.goal:
                #create a list
                path = []
                current = node

                #while at node 
                while current:
                    #add the the node to the list
                    path.append(current.label)
                    #change to the parent
                    current = current.parent
                #reverse the list which puts it in order
                path.reverse()
                #print the path
                #function print
                print(f"Success! Reached goal node {self.goal} with path: {path}")    
                #return path
                return path
            
            #if the node is not in the closed list
            if node.label not in self.closed:
                #add to closed list 
                self.closed.add(node.label)

                #create the children
                #function successors
                children = self.successors(node.label)

                #filter out visited children
                open_children = [c for c in children if c.label not in self.closed]

                #insert the new children that are not in the closed list
                if self.verbose and open_children:
                    #function print
                    print(f"Inserting new children: {[c.label for c in open_children]}")

                #create a list to hold all the children
                allowed_children = []
                #for child in children
                for child in children:
                    #if child is not in the closed list
                    if child.label not in self.closed:
                        #add the child and characteristics if not duplicate
                        #function duplicate
                        if not self.duplicate(child.label):
                            child.parent = node
                            child.depth = node.depth + 1
                            child.g = node.g + child.pathcost
                            #set h to zero because we dont need heuristic
                            child.h = 0
                            child.f = child.g
                            allowed_children.append(child)

            #reverse the children when coming back to the parent
            for child in reversed(allowed_children):
                self.insert_front(child)

            #print the open list
            if self.verbose and open_children:
                #function print
                print(f"Open list: {[n.showverbose() for n in self.open]}")


#----------EXACT SAME AS DFS BUT INSTEAD OF INSERT FRONT YOU INSERT END AND GET RID OF REVERSE -------
    def bfs(self):
        #create a set to keep track of visited nodes
        self.closed = set()
        #loop through list of nodes
        while self.open:
            #pop the first node off the list
            node = self.open.pop(0)

            #show the node that youre going to explore
            if self.verbose:
                #function print
                print(f"Exploring node: {node.label}")

            #if current node is goal node
            if node.label == self.goal:
                #create a list
                path = []
                current = node

                #while at node 
                while current:
                    #add the the node to the list
                    path.append(current.label)
                    #change to the parent
                    current = current.parent
                #reverse the list which puts it in order
                path.reverse()
                #print the path
                    #function print
                print(f"Success! Reached goal node {self.goal} with path: {path}")    
                #return the path
                return path
            
            #if the node is not in the closed list
            if node.label not in self.closed:
                #add to closed list 
                self.closed.add(node.label)

                #create the children
                #function successors
                children = self.successors(node.label)

                #filter out visited children
                open_children = [c for c in children if c.label not in self.closed]

                #write the new children that are not in the closed list
                if self.verbose and open_children:
                    #function print
                    print(f"Inserting new children: {[c.label for c in open_children]}")

                #create a list to hold all the children that arent duplicates
                allowed_children = []
                #for child in children
                for child in children:
                    #if child is not in the closed list
                    if child.label not in self.closed:
                        #add the child and characteristics if not duplicate
                        #function duplicate
                        if not self.duplicate(child.label):
                            child.parent = node
                            child.depth = node.depth + 1
                            child.g = node.g + child.pathcost
                            child.h = 0
                            child.f = child.g
                            allowed_children.append(child)

            #reverse the children when coming back
            for child in allowed_children:
                self.insert_end(child)

            #print the open list
            if self.verbose and open_children:
                #function print
                print(f"Open list: {[n.showverbose() for n in self.open]}")


#------------ GREEDY BEST FIRST ------------
    def greedy(self):
        #create a set to keep track of visited nodes
        self.closed = set()
        #loop through list of nodes
        while self.open:
            #pop the first node off the list
            node = self.open.pop(0)

            #show the node that youre going to explore
            if self.verbose:
                print(f"Exploring node: {node.label}")

            #if current node is goal node
            if node.label == self.goal:
                #create a list
                path = []
                current = node

                #while at node 
                while current:
                    #add the the node to the list
                    path.append(current.label)
                    #change to the parent
                    current = current.parent
                #reverse the list which puts it in order
                path.reverse()
                #print the path
                print(f"Success! Reached goal node {self.goal} with path: {path}")    
                #return path
                return path
            
            #if the node is not in the closed list
            if node.label not in self.closed:
                #add to closed list 
                self.closed.add(node.label)

                #create the children
                children = self.successors(node.label)

                #filter out visited children
                open_children = [c for c in children if c.label not in self.closed]

                #insert the new children that are not in the closed list
                if self.verbose and open_children:
                    #function print
                    print(f"Inserting new children: {[c.label for c in open_children]}")

                #create a list to hold all the children
                allowed_children = []
                #for child in children
                for child in children:
                    #if child is not in the closed list
                    if child.label not in self.closed:
                        #add the child and characteristics if not duplicate
                        #function duplicate
                        if not self.duplicate(child.label):
                            child.parent = node
                            child.depth = node.depth + 1
                            child.g = node.g + child.pathcost
                            #set h to the heuristic
                            child.h = hSLD(child.label, self)
                            #set f to h
                            child.f = child.h
                            allowed_children.append(child)

            #order the children
            for child in allowed_children:
                self.insert_ordered(child)

            #print the open list
            if self.verbose and open_children:
                #function print
                print(f"Open list: {[n.showverbose() for n in self.open]}")

#------------ A* BEST FIRST ------------
    def astar(self):
        #create a set to keep track of visited nodes
        self.closed = set()
        #loop through list of nodes
        while self.open:
            #pop the first node off the list
            node = self.open.pop(0)

            #show the node that youre going to explore
            if self.verbose:
                #function print
                print(f"Exploring node: {node.label}")

            #if current node is goal node
            if node.label == self.goal:
                #create a list
                path = []
                current = node

                #while at node 
                while current:
                    #add the the node to the list
                    path.append(current.label)
                    #change to the parent
                    current = current.parent
                #reverse the list which puts it in order
                path.reverse()
                #print the path
                print(f"Success! Reached goal node {self.goal} with path: {path}")    
                #return
                return path
            
            #if the node is not in the closed list
            if node.label not in self.closed:
                #add to closed list 
                self.closed.add(node.label)

                #create the children
                children = self.successors(node.label)

                #filter out visited children
                open_children = [c for c in children if c.label not in self.closed]

                #insert the new children that are not in the closed list
                if self.verbose and open_children:
                    print(f"Inserting new children: {[c.label for c in open_children]}")

                #create a list to hold all the children
                allowed_children = []
                for child in children:
                    #if child is not in the closed list
                    if child.label not in self.closed:
                        #add the child and characteristics if not duplicate
                        if not self.duplicate(child.label):
                            child.parent = node
                            child.depth = node.depth + 1
                            child.g = node.g + child.pathcost
                            #set h to the heuristic
                            child.h = hSLD(child.label, self)
                            #set f to g + h
                            child.f = child.g + child.h
                            allowed_children.append(child)

            #order the children
            for child in allowed_children:
                self.insert_ordered(child)

            #print the open list
            if self.verbose and open_children:
                #function print
                print(f"Open list: {[n.showverbose() for n in self.open]}")
            


                
                
           
            
        

        

# 10test.txt map
x=Searcher("10test.txt", searchType="DEPTH", verbose=True)
x.setStartGoal('h','k')
x.search()

x=Searcher("10test.txt", searchType="BREADTH", verbose=True)
x.setStartGoal('h','k')
x.search()

x=Searcher("10test.txt", searchType="BEST", verbose=True)
x.setStartGoal('h','k')
x.search()

x=Searcher("10test.txt", searchType="A*", verbose=True)
x.setStartGoal('h','k')
x.search()

# 50test.txt map
x=Searcher("50test.txt", searchType="DEPTH", verbose=False)
x.setStartGoal('s','c')
x.search()

x=Searcher("50test.txt", searchType="BREADTH", verbose=False)
x.setStartGoal('s','c')
x.search()

x=Searcher("50test.txt", searchType="BEST", verbose=False)
x.setStartGoal('s','c')
x.search()

x=Searcher("50test.txt", searchType="A*", verbose=False)
x.setStartGoal('s','c')
x.search()

