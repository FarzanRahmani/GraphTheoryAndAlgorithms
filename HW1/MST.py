class Graph:
    def __init__(self, vertices):
        '''
        Constructor to initialize the graph with the number of vertices
        :param vertices: number of vertices in the graph
        '''
        self.V = vertices # Number of vertices
        self.graph = [] # List to store the edges

    def add_edge(self, u, v, w):
        '''
        Function to add an edge to the graph
        :param u: one side of the edge
        :param v: other side of the edge
        :param w: weight of the edge(cost to traverse the edge
        :return: None
        '''
        self.graph.append([u, v, w]) # Add the edge to the graph

    def find(self, parent, i): # disjoint set find operation
        '''
        Function to find the set of an element i (using path compression technique)
        :param parent: parent array to keep track of the parent of the set
        :param i: element whose set is to be found
        :return: parent of the set to which the element belongs
        '''
        if parent[i] == i: # If the element is the parent of itself
            return i
        return self.find(parent, parent[i]) # Recursively find the parent of the element

    def union(self, parent, rank, x, y): # disjoint set union operation
        '''
        Function to perform union of two sets x and y (x and y are the sets to which the elements belong)
        :param parent: parent array to keep track of the parent of the set
        :param rank: rank array to keep track of the rank of the set
        :param x: one of the sets
        :param y: other set
        :return: None
        '''
        xroot = self.find(parent, x) # Find the set to which x belongs
        yroot = self.find(parent, y) # Find the set to which y belongs

        if rank[xroot] < rank[yroot]: # If the rank of x is less than the rank of y
            parent[xroot] = yroot # Make y the parent of x
        elif rank[xroot] > rank[yroot]: # If the rank of x is greater than the rank of y
            parent[yroot] = xroot # Make x the parent of y
        else: # If the rank of x is equal to the rank of y
            parent[yroot] = xroot  # Make x the parent of y
            rank[xroot] += 1 # Increment the rank of x

    def kruskal_mst(self):
        '''
        Function to find the minimum spanning tree of the graph using Kruskal's algorithm
        :return: weight of the minimum spanning tree
        '''
        result = [] # List to store the edges of the minimum spanning tree
        i, e = 0, 0 # i = index of the edge, e = number of edges in the minimum spanning tree
        self.graph = sorted(self.graph, key=lambda item: item[2]) # Sort the edges based on their weights in non-decreasing order
        parent = [] # List to store the parent of the set to which the element belongs
        rank = [] # List to store the rank of the set to which the element belongs

        for node in range(self.V):
            parent.append(node) # Initially, the parent of each element is the element itself
            rank.append(0) # Initially, the rank of each set is 0

        while e < self.V - 1: # While the number of edges in the minimum spanning tree is less than the number of vertices - 1
            u, v, w = self.graph[i] # Get the edge with the minimum weight
            i = i + 1 # Move to the next edge
            x = self.find(parent, u) # Find the set to which u belongs
            y = self.find(parent, v) # Find the set to which v belongs

            if x != y: # If u and v belong to different sets (i.e., adding the edge does not form a cycle)
                e = e + 1 # Increment the number of edges in the minimum spanning tree
                result.append([u, v, w]) # Add the edge to the minimum spanning tree
                self.union(parent, rank, x, y) # Perform union of the sets to which u and v belong

        return sum(item[2] for item in result) # Return the weight(cost) of the minimum spanning tree


def main():
    '''
    Main function to take input and call the kruskal_mst function
    :return: None
    '''
    n, m = map(int, input().split()) # n = number of vertices, m = number of edges
    g = Graph(n) # Create a graph with n vertices
    for _ in range(m): # Add m edges to the graph
        u, v, w = map(int, input().split()) # u, v = vertices, w = weight
        g.add_edge(u - 1, v - 1, w) # Add edge to the graph
    print(g.kruskal_mst()) # Print the weight of the minimum spanning tree


if __name__ == "__main__": # If the script is run directly
    main() # Call the main function