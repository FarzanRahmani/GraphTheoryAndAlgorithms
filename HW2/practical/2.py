from collections import defaultdict

class HopcroftKarp:
    '''
    Implementation of the Hopcroft-Karp algorithm for finding the maximum cardinality matching in a bipartite graph.

    Attributes:
        graph: A dictionary where the keys are vertices in the first part and the values are sets of neighbors in the second part.
        pair_u: A dictionary where the keys are vertices in the first part and the values are their corresponding matched vertices in the second part.
        pair_v: A dictionary where the keys are vertices in the second part and the values are their corresponding matched vertices in the first part.
        dist: A dictionary to store the distance of each vertex from the source.
        max_matching: An integer to store the size of the maximum matching.

    Methods:
        bfs: Breadth-first search to find the shortest augmenting path.
        dfs: Depth-first search to recursively find augmenting paths.
        max_matching_size: Find the maximum cardinality matching in the bipartite graph.
    '''

    def __init__(self, graph):
        '''
        Initialize the Hopcroft-Karp algorithm with the given bipartite graph.

        Args:
            graph: A dictionary where the keys are vertices in the first part and the values are sets of neighbors in the second part.

        Returns:
            None
        '''
        self.graph = graph # A dictionary where the keys are vertices in the first part and the values are sets of neighbors in the second part
        self.pair_u = defaultdict(lambda: None) # A dictionary where the keys are vertices in the first part and the values are their corresponding matched vertices in the second part
        self.pair_v = defaultdict(lambda: None) # A dictionary where the keys are vertices in the second part and the values are their corresponding matched vertices in the first part
        self.dist = {} # A dictionary to store the distance of each vertex from the source
        self.max_matching = 0 # An integer to store the size of the maximum matching

    def bfs(self):
        '''
        Breadth-first search to find the shortest augmenting path.

        Args:
            None

        Returns:
            True if an augmenting path is found, False otherwise.
        '''
        queue = [] # Use a queue to perform BFS
        for u in self.graph: # Initialize the distance of each vertex from the source
            if self.pair_u[u] is None: # Add unmatched vertices to the queue
                self.dist[u] = 0
                queue.append(u)
            else: # Add matched vertices to the queue
                self.dist[u] = float('inf')

        self.dist[None] = float('inf') # Initialize the distance of the source
        while queue: # Perform BFS
            u = queue.pop(0) # Dequeue a vertex
            if u is not None: # Check each neighbor of the vertex
                for v in self.graph[u]: # Check if the neighbor is matched
                    if self.dist[self.pair_v[v]] == float('inf'): # Check if the neighbor is unmatched
                        self.dist[self.pair_v[v]] = self.dist[u] + 1
                        queue.append(self.pair_v[v])
        return self.dist[None] != float('inf') # Check if an augmenting path is found

    def dfs(self, u):
        '''
        Depth-first search to recursively find augmenting paths.

        Args:
            u: A vertex in the first part.

        Returns:
            True if an augmenting path is found, False otherwise.
        '''
        if u is not None: # Check each neighbor of the vertex
            for v in self.graph[u]: # Check if the neighbor is matched
                if self.dist[self.pair_v[v]] == self.dist[u] + 1: # Check if the neighbor is unmatched
                    if self.dfs(self.pair_v[v]): # Recursively find augmenting paths
                        self.pair_v[v] = u
                        self.pair_u[u] = v
                        return True
            self.dist[u] = float('inf') # Update the distance of the vertex
            return False
        return True

    def max_matching_size(self):
        '''
        Find the maximum cardinality matching in the bipartite graph.

        Args:
            None

        Returns:
            The size of the maximum matching.
        '''
        while self.bfs(): # Find augmenting paths using BFS
            for u in self.graph: # Check each vertex in the first part
                if self.pair_u[u] is None and self.dfs(u): # Recursively find augmenting paths using DFS
                    self.max_matching += 1
        return self.max_matching // 2 # Return the size of the maximum matching

def parse_input(input_str):
    '''
    Parse the input string to construct the graph.

    Args:
        input_str: A string of characters.

    Returns:
        A tuple of three elements:
        - A dictionary where the keys are vertices and the values are sets of neighbors.
        - A set of vertices.
        - A set of edges.
    '''
    graph = defaultdict(set) # A dictionary where the keys are vertices and the values are sets of neighbors
    vertices = set() # A set of vertices
    edges = set() # A set of edges

    i = 0 # Index of the current character in the input string
    sequence = input_str
    while i < len(sequence): # Parse the input string
        if sequence[i] == ' ': # Skip spaces
            i += 1
            continue
        elif (i == len(sequence) - 1) or sequence[i + 1] == ' ': # Isolated vertex if the next character is a space or the last character
            isolated_vertex = sequence[i]
            vertices.add(isolated_vertex)
            if isolated_vertex not in graph: # Add the isolated vertex to the graph with an empty set of neighbors
                graph[isolated_vertex] = set()
            i += 1
            continue
        vertex1 = sequence[i]
        vertex2 = sequence[i+1]
        edge = ''.join(sorted(sequence[i:i+2])) # Sort the characters to avoid duplicates
        vertices.add(vertex1)
        vertices.add(vertex2)
        edges.add(edge)
        if vertex1 not in graph: # Add the edge to the graph
            graph[vertex1] = set()
        if vertex2 not in graph: # Add the edge to the graph
            graph[vertex2] = set()
        graph[vertex1].add(vertex2)
        graph[vertex2].add(vertex1)
        i += 2 # Move to the next pair of characters

    return graph, vertices, edges

def maximum_matching(input_string):
    '''
    Find the maximum cardinality matching in the bipartite graph.

    Args:
        input_string: A string of characters.

    Returns:
        The size of the maximum matching.
    '''
    graph, vertices, edges = parse_input(input_string) # Parse the input string
    hk = HopcroftKarp(graph) # Initialize the Hopcroft-Karp algorithm
    return hk.max_matching_size() # Return the size of the maximum matching

# Sample inputs
# sample_input_1 = "abacdedfsopwkslskc"
# sample_input_2 = "abacbcbebddeegeffgghhigiijkjkljllnlmmnnpnopororqoqqtsqstsuuvuwvwwxwyxyzx"

# Sample outputs
# print(maximum_matching(sample_input_1))  # Output: 5
# print(maximum_matching(sample_input_2))  # Output: 13

print(maximum_matching(input()))