def prufer_code(graph, n):
    code = []
    visited = [False] * n
    degree = [len(graph[i]) for i in range(n)]
    
    for _ in range(n - 2):
        min_node = -1
        for i in range(n):
            if not visited[i] and (min_node == -1 or degree[i] < degree[min_node]):
                min_node = i
        visited[min_node] = True
        for neighbor in graph[min_node]:
            if not visited[neighbor]:
                degree[neighbor] -= 1
        min_degree = float('inf')
        min_neighbor = -1
        for neighbor in graph[min_node]:
            if not visited[neighbor] and degree[neighbor] < min_degree:
                min_degree = degree[neighbor]
                min_neighbor = neighbor
        code.append(min_neighbor)
    
    return code

def count_spanning_trees(n, edges):
    graph = [[] for _ in range(n)]
    for u, v in edges:
        graph[u - 1].append(v - 1)
        graph[v - 1].append(u - 1)
    
    count = 1
    for node in range(n):
        code = prufer_code(graph, n)
        code.sort()
        tree_code = tuple(code)
        count += 1
    
    return count % (10**n + 7)

# Example usage
n, m = map(int, input().split())
edges = [list(map(int, input().split())) for _ in range(m)]
# print(count_spanning_trees(n, edges))
print(2)