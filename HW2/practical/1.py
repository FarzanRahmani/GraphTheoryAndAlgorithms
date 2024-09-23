from collections import defaultdict

def parse_input(input_str):
    '''
    Parse the input string to create a graph, vertices, and edges.
    The input string is a sequence of characters, where each pair of characters represents an edge.
    If a character is isolated, it is considered a vertex.

    Args:
        input_str: A string of characters.

    Returns:
        graph: A dictionary where the keys are vertices and the values are sets of neighbors.
        vertices: A set of vertices.
        edges: A set of edges.
    '''
    graph = defaultdict(set) # Use defaultdict to avoid key errors
    vertices = set() # Use set to avoid duplicates
    edges = set() # Use set to avoid duplicates

    i = 0 # Index of the current character
    sequence = input_str
    while i < len(sequence):
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
        if vertex1 not in graph:
            graph[vertex1] = set()
        if vertex2 not in graph:
            graph[vertex2] = set()
        graph[vertex1].add(vertex2)
        graph[vertex2].add(vertex1)
        i += 2
    return graph, vertices, edges

def is_bipartite(graph, vertices):
    '''
    Check if the graph is bipartite using BFS.

    Args:
        graph: A dictionary where the keys are vertices and the values are sets of neighbors.
        vertices: A set of vertices.

    Returns:
        True if the graph is bipartite, False otherwise.
    '''
    colors = {} # Use a dictionary to store the color of each vertex
    queue = [] # Use a queue to perform BFS

    for vertex in vertices: # Check each connected component
        if vertex not in colors: # Skip vertices that have been visited
            queue.append(vertex) 
            colors[vertex] = 0  # Assign color 0 to the first vertex
            
            while queue: # Perform BFS
                current = queue.pop(0)
                for neighbor in graph[current]:
                    if neighbor not in colors: # Skip vertices that have been visited
                        colors[neighbor] = 1 - colors[current]  # Assign the opposite color
                        queue.append(neighbor)
                    elif colors[neighbor] == colors[current]: # Check if the graph is bipartite
                        return False  # Not bipartite
    
    return True

def calculate_complement_edges(vertices, edges):
    '''
    Calculate the number of edges in the complement graph.

    Args:
        vertices: A set of vertices.
        edges: A set of edges.

    Returns:
        The number of edges in the complement graph.
    '''
    num_vertices = len(vertices)
    num_edges = len(edges)
    complement_edges = (num_vertices * (num_vertices - 1)) // 2 - num_edges
    return complement_edges

def remove_edges_to_bipartite(graph, vertices, edges):
    '''
    Remove edges to make the graph bipartite using BFS.

    Args:
        graph: A dictionary where the keys are vertices and the values are sets of neighbors.
        vertices: A set of vertices.
        edges: A set of edges.

    Returns:
        The number of removed edges.
    '''
    num_removed_edges = 0
    
    # Use BFS to find connected components and remove edges to make it bipartite
    for vertex in vertices:
        queue = [vertex]
        colors = {vertex: 0}  # Assign color 0 to the first vertex
        while queue:
            current = queue.pop(0)
            neighbors = set(graph[current])
            for neighbor in neighbors:
                if neighbor not in colors:
                    colors[neighbor] = 1 - colors[current]  # Assign the opposite color
                    queue.append(neighbor)
                elif colors[neighbor] == colors[current]:
                    # Remove an edge between current and neighbor
                    edge = ''.join(sorted([current, neighbor]))
                    if edge in edges:
                        edges.remove(edge)
                        graph[current].remove(neighbor)
                        if edge[0] != edge[1]:
                            graph[neighbor].remove(current)
                        num_removed_edges += 1
                        queue.insert(0, current)
                        break
    
    return num_removed_edges

def main(input_str):
    '''
    Main function to parse the input string, calculate the output, and print it.

    Args:
        input_str: A string of characters.

    Returns:
        None.
    '''
    graph, vertices, edges = parse_input(input_str) # Parse the input string
    
    if is_bipartite(graph, vertices): # Check if the graph is bipartite
        complement_edges = calculate_complement_edges(vertices, edges) # Calculate the number of edges in the complement graph
        print(complement_edges) # Print the number of edges in the complement graph
    else: # Remove edges to make the graph bipartite
        num_total_edges = len(edges) # Store the number of edges before removing
        num_removed_edges = remove_edges_to_bipartite(graph, vertices, edges) # Remove edges to make the graph bipartite
        print(num_total_edges - num_removed_edges) # Calculate the number of edges in the complement graph

# # Example usage:
# input_str1 = "abacdedfsopwkslskc"
# main(input_str1)  # Output: 57

# input_str2 = "kjhgfyfhjklkohufyykpjhgyfhjkphitdyjkpjogyfjkjhgfdfghkljhhgfg"
# main(input_str2)  # Output: 14

# input_str3 = "abc d"
# main(input_str3)  # Output: 5

main(input())