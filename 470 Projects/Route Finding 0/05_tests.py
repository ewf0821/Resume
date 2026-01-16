# Define Searcher, hSLD, SearchNode.
import warnings
warnings.filterwarnings('ignore', category=UserWarning, module='matplotlib')
from DRDViz import DRDViz
import math



class SearchNode:
    def __init__(self, label, value=None, pathcost=None):
        self.label = label
        self.value = value

    def showBasic(self):        
        return (self.label, self.value)
    
    def __lt__(self, other):
        return self.label < other.label


# Alias for convenience
SNode = SearchNode

# 2. Searcher Class    
class Searcher:
    def __init__(self, file_name):
        self.myViz = DRDViz()
        self.myViz.loadGraphFromFile(file_name)
        self.start = None
        self.goal = None
        self.open = []
        print(f"Loaded search type A* with map in file: {file_name}")

    def setStartGoal(self, start, goal):
        self.start = start
        self.goal = goal
        self.open.append(SearchNode(start, 0))

    def successors(self, node_label):
        children = []
        for edge in self.myViz.edges:
            if edge.endlabel1 == node_label:
                children.append(SearchNode(edge.endlabel2, int(edge.label)))
            elif edge.endlabel2 == node_label:
                children.append(SearchNode(edge.endlabel1, int(edge.label)))
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
            if node.value < existing.value:
                self.open.insert(i, node)
                return
        self.open.append(node)

    def reset(self):
        self.open = []
        if self.start:
            self.open.append(SearchNode(self.start, 0))

# 3. Heuristic Function
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

# (b) Show your program loading in the 30-node sample file. 
s=Searcher("30node.txt")
# (c) Show you program setting start node=U and end node=T. 
s.setStartGoal('U','T')
# myViz should be a DRDViz instance -> save map to file on disk.
s.myViz.plot()  # Need to plot the graph first
s.myViz.markStart('U')  # Mark start node in cyan
s.myViz.markGoal('T')   # Mark goal node in red
s.myViz.save("30node.png")
# (d) Show the one open node.
#print([n.showBasic() for n in s.open])
# (e) Show successors of only open node.
initial_children = s.successors(s.open.pop(0).label)
#print([n.showBasic() for n in initial_children])

# (f) Show three inserts: at the front, and the end, and "in order"
def reset_insert(where):
    s.reset()
    initial_children = s.successors(s.open.pop(0))
    insert_method = getattr(s, "insert_"+where)
    insert_method(initial_children)
    return [n.showBasic() for n in s.open]

print(reset_insert("front"))
print(reset_insert("end"))
print(reset_insert("ordered"))

# (g) INSERT (K,500), (C,91) and (J,10) and show no duplicates.
newdata = (("K",500), ("C",91), ("J",10))
newlist = [SearchNode(label=label, value=pathcost) for label, pathcost in newdata]
ignored = s.insert_end(newlist)
#print([n.showBasic() for n in s.open])

# 3. hSLD heuritic function being called on three nodes.
#print([hSLD(x, s) for x in ("V", "AC", "J")])

# Keep the plot window open
import matplotlib.pyplot as plt
plt.show()

