import matplotlib.pyplot as plt
import networkx as nx

def getCardGraph(filename):
    """ Take a .gr file and return the number of vertices """
    k = 0; node0 = False
    with open(filename, 'r') as f:
        for ligne in f:
            l = ligne.split()
            if l[0] == 'p':
                return l[2]


def createGraph(filename):
    """ Take a .gr file and return the associated graph as in the networkx class """
    G = nx.Graph()
    for i in range(1, getCardGraph(filename)):
        G.add_node(i)

    with open(filename, 'r') as f:
        for ligne in f:
            l = ligne.split()
            if l[0] != 'c' or l[0] != 'p':
                G.add_edge(int(l[0]), int(l[1]))
    return G


########################### Datafiles ###########################
filename = '002.graph'
sol = 'sol.solution'
#################################################################
G = createGraph(filename)

# Generate position to place nodes
pos = nx.kamada_kawai_layout(G)

# Draw nodes
nx.draw_networkx_nodes(G, pos, node_size=50)
# Default edges
nx.draw_networkx_edges(G, pos, edge_color='blue')

# Getting dominating set
dominatingSet, domEdges = [], []
with open(sol, 'r') as f:
    for lign in f:
        if lign != '\n':
            dominatingSet.append(int(lign))

# Coloring the dominated nodes and edges in red
nx.draw_networkx_nodes(G, pos, nodelist=dominatingSet, node_color='red', node_size=50)

for edge in G.edges():
    if (edge[0] in dominatingSet) or (edge[1] in dominatingSet):
        nx.draw_networkx_edges(G, pos, edgelist=[edge], edge_color='red')

plt.tight_layout()

# Saving the image as a .png file
plt.savefig(filename.split('.')[0] + '.png')

# uncomment next line if requires to show at execution
#plt.show()
