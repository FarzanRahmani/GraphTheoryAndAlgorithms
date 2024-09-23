require 'set'

def parse_input(input_str)
  graph = Hash.new { |h, k| h[k] = Set.new } # Use Hash to avoid key errors
  vertices = Set.new # Use Set to avoid duplicates
  edges = Set.new # Use Set to avoid duplicates

  i = 0 # Index of the current character
  sequence = input_str
  while i < sequence.length
    if sequence[i] == ' ' # Skip spaces
      i += 1
      next
    elsif (i == sequence.length - 1) || sequence[i + 1] == ' ' # Isolated vertex if the next character is a space or the last character
      isolated_vertex = sequence[i]
      vertices.add(isolated_vertex)
      graph[isolated_vertex] = Set.new unless graph.key?(isolated_vertex) # Add the isolated vertex to the graph with an empty set of neighbors
      i += 1
      next
    end
    vertex1 = sequence[i]
    vertex2 = sequence[i + 1]
    edge = [vertex1, vertex2].sort.join # Sort the characters to avoid duplicates
    vertices.add(vertex1)
    vertices.add(vertex2)
    edges.add(edge)
    graph[vertex1].add(vertex2)
    graph[vertex2].add(vertex1)
    i += 2
  end
  [graph, vertices, edges]
end

def is_bipartite(graph, vertices)
  colors = {} # Use a hash to store the color of each vertex
  queue = [] # Use an array to perform BFS

  vertices.each do |vertex| # Check each connected component
    next if colors.key?(vertex) # Skip vertices that have been visited
    queue.push(vertex)
    colors[vertex] = 0 # Assign color 0 to the first vertex

    until queue.empty? # Perform BFS
      current = queue.shift
      graph[current].each do |neighbor|
        next if colors.key?(neighbor) # Skip vertices that have been visited
        colors[neighbor] = 1 - colors[current] # Assign the opposite color
        queue.push(neighbor)
      end
    end
  end

  colors.each do |vertex, color|
    graph[vertex].each do |neighbor|
      return false if colors[neighbor] == colors[vertex] # Check if the graph is bipartite
    end
  end

  true
end

def calculate_complement_edges(vertices, edges)
  num_vertices = vertices.length
  num_edges = edges.length
  complement_edges = (num_vertices * (num_vertices - 1)) / 2 - num_edges
  complement_edges
end

def remove_edges_to_bipartite(graph, vertices, edges)
  num_removed_edges = 0

  # Use BFS to find connected components and remove edges to make it bipartite
  vertices.each do |vertex|
    queue = [vertex]
    colors = { vertex => 0 } # Assign color 0 to the first vertex
    until queue.empty?
      current = queue.shift
      graph[current].each do |neighbor|
        if !colors.key?(neighbor)
          colors[neighbor] = 1 - colors[current] # Assign the opposite color
          queue.push(neighbor)
        elsif colors[neighbor] == colors[current]
          # Remove an edge between current and neighbor
          edge = [current, neighbor].sort.join
          if edges.include?(edge)
            edges.delete(edge)
            graph[current].delete(neighbor)
            graph[neighbor].delete(current) if edge[0] != edge[1]
            num_removed_edges += 1
            queue.unshift(current)
            break
          end
        end
      end
    end
  end

  num_removed_edges
end

def main(input_str)
  graph, vertices, edges = parse_input(input_str) # Parse the input string

  if is_bipartite(graph, vertices) # Check if the graph is bipartite
    complement_edges = calculate_complement_edges(vertices, edges) # Calculate the number of edges in the complement graph
    puts complement_edges # Print the number of edges in the complement graph
  else # Remove edges to make the graph bipartite
    num_total_edges = edges.length # Store the number of edges before removing
    num_removed_edges = remove_edges_to_bipartite(graph, vertices, edges) # Remove edges to make the graph bipartite
    puts num_total_edges - num_removed_edges # Calculate the number of edges in the complement graph
  end
end

# Example usage:
# input_str1 = "abacdedfsopwkslskc"
# main(input_str1)  # Output: 57

# input_str2 = "kjhgfyfhjklkohufyykpjhgyfhjkphitdyjkpjogyfjkjhgfdfghkljhhgfg"
# main(input_str2)  # Output: 14

# input_str3 = "abc d"
# main(input_str3)  # Output: 5

main(gets.chomp)




# require 'set'

# def parse_input(input_str)
#   '''
#   Parse the input string to create a graph, vertices, and edges.
#   The input string is a sequence of characters, where each pair of characters represents an edge.
#   If a character is isolated, it is considered a vertex.
  
#   Args:
#       input_str: A string of characters.
  
#   Returns:
#       graph: A dictionary where the keys are vertices and the values are sets of neighbors.
#       vertices: A set of vertices.
#       edges: A set of edges.
#   '''
#   graph = Hash.new { |hash, key| hash[key] = Set.new } # Use Hash.new with a block to avoid key errors
#   vertices = Set.new # Use set to avoid duplicates
#   edges = Set.new # Use set to avoid duplicates
  
#   i = 0 # Index of the current character
#   sequence = input_str
#   while i < sequence.length
#     if sequence[i] == ' ' # Skip spaces
#       i += 1
#       next
#     elsif (i == sequence.length - 1) || sequence[i + 1] == ' ' # Isolated vertex if the next character is a space or the last character
#       isolated_vertex = sequence[i]
#       vertices.add(isolated_vertex)
#       graph[isolated_vertex] = Set.new unless graph.key?(isolated_vertex) # Add the isolated vertex to the graph with an empty set of neighbors
#       i += 1
#       next
#     end
#     vertex1 = sequence[i]
#     vertex2 = sequence[i + 1]
#     edge = [vertex1, vertex2].sort.join # Sort the characters to avoid duplicates
#     vertices.add(vertex1)
#     vertices.add(vertex2)
#     edges.add(edge)
#     graph[vertex1].add(vertex2)
#     graph[vertex2].add(vertex1)
#     i += 2
#   end
#   [graph, vertices, edges]
# end

# def is_bipartite(graph, vertices)
#   '''
#   Check if the graph is bipartite using BFS.
  
#   Args:
#       graph: A dictionary where the keys are vertices and the values are sets of neighbors.
#       vertices: A set of vertices.
  
#   Returns:
#       True if the graph is bipartite, False otherwise.
#   '''
#   colors = {} # Use a hash to store the color of each vertex
#   queue = [] # Use an array to perform BFS
  
#   vertices.each do |vertex| # Check each connected component
#     next if colors.key?(vertex) # Skip vertices that have been visited
#     queue << vertex
#     colors[vertex] = 0 # Assign color 0 to the first vertex
    
#     until queue.empty? # Perform BFS
#       current = queue.shift
#       graph[current].each do |neighbor|
#         next if colors.key?(neighbor) # Skip vertices that have been visited
#         colors[neighbor] = 1 - colors[current] # Assign the opposite color
#         queue << neighbor
#       end
#     end
#   end
  
#   colors.each do |vertex, color|
#     graph[vertex].each do |neighbor|
#       return false if colors[neighbor] == color # Check if the graph is bipartite
#     end
#   end
  
#   true
# end

# def calculate_complement_edges(vertices, edges)
#   '''
#   Calculate the number of edges in the complement graph.
  
#   Args:
#       vertices: A set of vertices.
#       edges: A set of edges.
  
#   Returns:
#       The number of edges in the complement graph.
#   '''
#   num_vertices = vertices.size
#   num_edges = edges.size
#   complement_edges = (num_vertices * (num_vertices - 1)) / 2 - num_edges
#   complement_edges
# end

# def remove_edges_to_bipartite(graph, vertices, edges)
#   '''
#   Remove edges to make the graph bipartite using BFS.
  
#   Args:
#       graph: A dictionary where the keys are vertices and the values are sets of neighbors.
#       vertices: A set of vertices.
#       edges: A set of edges.
  
#   Returns:
#       The number of removed edges.
#   '''
#   num_removed_edges = 0
  
#   # Use BFS to find connected components and remove edges to make it bipartite
#   vertices.each do |vertex|
#     queue = [vertex]
#     colors = { vertex => 0 } # Assign color 0 to the first vertex
#     until queue.empty?
#       current = queue.shift
#       graph[current].each do |neighbor|
#         next if colors.key?(neighbor)
        
#         colors[neighbor] = 1 - colors[current] # Assign the opposite color
#         queue << neighbor
#       end
#     end
    
#     graph.each do |v, neighbors|
#       neighbors.each do |neighbor|
#         next unless colors[neighbor] == colors[v]
        
#         # Remove an edge between current and neighbor
#         edge = [v, neighbor].sort.join
#         if edges.include?(edge)
#           edges.delete(edge)
#           graph[v].delete(neighbor)
#           graph[neighbor].delete(v) if v != neighbor
#           num_removed_edges += 1
#           queue.unshift(v)
#           break
#         end
#       end
#     end
#   end
  
#   num_removed_edges
# end

# def main(input_str)
#   '''
#   Main function to parse the input string, calculate the output, and print it.
  
#   Args:
#       input_str: A string of characters.
  
#   Returns:
#       None.
#   '''
#   graph, vertices, edges = parse_input(input_str) # Parse the input string
  
#   if is_bipartite(graph, vertices) # Check if the graph is bipartite
#     complement_edges = calculate_complement_edges(vertices, edges) # Calculate the number of edges in the complement graph
#     puts complement_edges # Print the number of edges in the complement graph
#   else # Remove edges to make the graph bipartite
#     num_total_edges = edges.size # Store the number of edges before removing
#     num_removed_edges = remove_edges_to_bipartite(graph, vertices, edges) # Remove edges to make the graph bipartite
#     puts num_total_edges - num_removed_edges # Calculate the number of edges in the complement graph
#   end
# end

# # Example usage:
# # input_str1 = "abacdedfsopwkslskc"
# # main(input_str1)  # Output: 57

# # input_str2 = "kjhgfyfhjklkohufyykpjhgyfhjkphitdyjkpjogyfjkjhgfdfghkljhhgfg"
# # main(input_str2)  # Output: 14

# # input_str3 = "abc d"
# # main(input_str3)  # Output: 5

# main(gets.chomp)


