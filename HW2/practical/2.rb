require 'set'

class HopcroftKarp
  # Implementation of the Hopcroft-Karp algorithm for finding the maximum cardinality matching in a bipartite graph.

  attr_reader :graph, :pair_u, :pair_v, :dist, :max_matching

  # Initialize the Hopcroft-Karp algorithm with the given bipartite graph.
  def initialize(graph)
    @graph = graph # A dictionary where the keys are vertices in the first part and the values are sets of neighbors in the second part
    @pair_u = Hash.new # A dictionary where the keys are vertices in the first part and the values are their corresponding matched vertices in the second part
    @pair_v = Hash.new # A dictionary where the keys are vertices in the second part and the values are their corresponding matched vertices in the first part
    @dist = Hash.new # A dictionary to store the distance of each vertex from the source
    @max_matching = 0 # An integer to store the size of the maximum matching
  end

  # Breadth-first search to find the shortest augmenting path.
  def bfs
    queue = [] # Use a queue to perform BFS
    @graph.keys.each do |u| # Initialize the distance of each vertex from the source
      if @pair_u[u].nil? # Add unmatched vertices to the queue
        @dist[u] = 0
        queue << u
      else # Add matched vertices to the queue
        @dist[u] = Float::INFINITY
      end
    end
    @dist[nil] = Float::INFINITY # Initialize the distance of the source

    while !queue.empty? # Perform BFS
      u = queue.shift # Dequeue a vertex
      next unless u # Check each neighbor of the vertex

      @graph[u].each do |v| # Check if the neighbor is matched
        if @dist[@pair_v[v]] == Float::INFINITY # Check if the neighbor is unmatched
          @dist[@pair_v[v]] = @dist[u] + 1
          queue << @pair_v[v]
        end
      end
    end

    @dist[nil] != Float::INFINITY # Check if an augmenting path is found
  end

  # Depth-first search to recursively find augmenting paths.
  def dfs(u)
    return true unless u # Check each neighbor of the vertex
    return true if @pair_u[u].nil?

    @graph[u].each do |v| # Check if the neighbor is matched
      if @dist[@pair_v[v]] == @dist[u] + 1 # Check if the neighbor is unmatched
        if dfs(@pair_v[v]) # Recursively find augmenting paths
          @pair_v[v] = u
          @pair_u[u] = v
          return true
        end
      end
    end
    @dist[u] = Float::INFINITY # Update the distance of the vertex
    false
  end

  # Find the maximum cardinality matching in the bipartite graph.
  def max_matching_size
    while bfs # Find augmenting paths using BFS
      @graph.keys.each do |u| # Check each vertex in the first part
        if @pair_u[u].nil? && dfs(u) # Recursively find augmenting paths using DFS
          @max_matching += 1
        end
      end
    end

    @max_matching / 2 # Return the size of the maximum matching
  end
end

def parse_input(input_str)
  # Parse the input string to construct the graph.
  graph = Hash.new { |hash, key| hash[key] = Set.new } # A dictionary where the keys are vertices and the values are sets of neighbors
  vertices = Set.new # A set of vertices
  edges = Set.new # A set of edges

  i = 0 # Index of the current character in the input string
  sequence = input_str
  while i < sequence.length # Parse the input string
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
    i += 2 # Move to the next pair of characters
  end

  [graph, vertices, edges]
end

def maximum_matching(input_string)
  # Find the maximum cardinality matching in the bipartite graph.
  graph, _vertices, _edges = parse_input(input_string) # Parse the input string
  hk = HopcroftKarp.new(graph) # Initialize the Hopcroft-Karp algorithm
  hk.max_matching_size # Return the size of the maximum matching
end

puts maximum_matching(gets.chomp)


# require 'set'

# class HopcroftKarp
#   # Implementation of the Hopcroft-Karp algorithm for finding the maximum cardinality matching in a bipartite graph.

#   attr_reader :graph, :pair_u, :pair_v, :dist, :max_matching

#   # Initialize the Hopcroft-Karp algorithm with the given bipartite graph.
#   def initialize(graph)
#     @graph = graph # A dictionary where the keys are vertices in the first part and the values are sets of neighbors in the second part
#     @pair_u = Hash.new # A dictionary where the keys are vertices in the first part and the values are their corresponding matched vertices in the second part
#     @pair_v = Hash.new # A dictionary where the keys are vertices in the second part and the values are their corresponding matched vertices in the first part
#     @dist = Hash.new # A dictionary to store the distance of each vertex from the source
#     @max_matching = 0 # An integer to store the size of the maximum matching
#   end

#   # Breadth-first search to find the shortest augmenting path.
#   def bfs
#     queue = [] # Use a queue to perform BFS
#     @graph.keys.each do |u| # Initialize the distance of each vertex from the source
#       if @pair_u[u].nil? # Add unmatched vertices to the queue
#         @dist[u] = 0
#         queue << u
#       else # Add matched vertices to the queue
#         @dist[u] = Float::INFINITY
#       end
#     end
#     @dist[nil] = Float::INFINITY # Initialize the distance of the source

#     while !queue.empty? # Perform BFS
#       u = queue.shift # Dequeue a vertex
#       next unless u # Check each neighbor of the vertex

#       @graph[u].each do |v| # Check if the neighbor is matched
#         if @dist[@pair_v[v]] == Float::INFINITY # Check if the neighbor is unmatched
#           @dist[@pair_v[v]] = @dist[u] + 1
#           queue << @pair_v[v]
#         end
#       end
#     end

#     @dist[nil] != Float::INFINITY # Check if an augmenting path is found
#   end

#   # Depth-first search to recursively find augmenting paths.
#   def dfs(u)
#     return true unless u # Check each neighbor of the vertex
#     return true if @pair_u[u].nil?

#     @graph[u].each do |v| # Check if the neighbor is matched
#       if @dist[@pair_v[v]] == @dist[u] + 1 # Check if the neighbor is unmatched
#         if dfs(@pair_v[v]) # Recursively find augmenting paths
#           @pair_v[v] = u
#           @pair_u[u] = v
#           return true
#         end
#       end
#     end
#     @dist[u] = Float::INFINITY # Update the distance of the vertex
#     false
#   end

#   # Find the maximum cardinality matching in the bipartite graph.
#   def max_matching_size
#     while bfs # Find augmenting paths using BFS
#       @graph.keys.each do |u| # Check each vertex in the first part
#         if @pair_u[u].nil? && dfs(u) # Recursively find augmenting paths using DFS
#           @max_matching += 1
#         end
#       end
#     end

#     @max_matching / 2 # Return the size of the maximum matching
#   end
# end

# def parse_input(input_str)
#   # Parse the input string to construct the graph.
#   graph = Hash.new { |hash, key| hash[key] = Set.new } # A dictionary where the keys are vertices and the values are sets of neighbors
#   vertices = Set.new # A set of vertices
#   edges = Set.new # A set of edges

#   i = 0 # Index of the current character in the input string
#   sequence = input_str
#   while i < sequence.length # Parse the input string
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
#     i += 2 # Move to the next pair of characters
#   end

#   [graph, vertices, edges]
# end

# def maximum_matching(input_string)
#   # Find the maximum cardinality matching in the bipartite graph.
#   graph, _vertices, _edges = parse_input(input_string) # Parse the input string
#   hk = HopcroftKarp.new(graph) # Initialize the Hopcroft-Karp algorithm
#   hk.max_matching_size # Return the size of the maximum matching
# end

# puts maximum_matching(gets.chomp)
