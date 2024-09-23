# compute the diameter of a tree 

def dfs(node, dist, visited, distances): 
    '''
    node: int
    dist: int
    visited: list
    distances: list

    return: None

    description:
    1. mark the node as visited
    2. set the distance of the node
    3. recursively call the function for the adjacent nodes
    '''
    visited[node] = True
    distances[node] = dist
    for i in range(len(v[node])): 
        if not visited[v[node][i]]: 
            dfs(v[node][i], dist + 1, visited, distances)

def diameter():
    '''
    return: int
    
    description:
    1. find the farthest node from the first node
    2. find the farthest node from the farthest node from the first node
    3. return the distance between the two farthest nodes
    '''
    visited = [False] * (n + 1)
    dist_array = [0] * (n + 1)
    dfs(node=1, dist=0, visited=visited, distances=dist_array)
    max_dist = -1
    max_node = -1
    for i in range(1, n + 1): 
        if max_dist < dist_array[i]: 
            max_dist = dist_array[i]
            max_node = i
    
    visited = [False] * (n + 1)
    dist_array = [0] * (n + 1)
    dfs(max_node, 0, visited, dist_array)
    max_dist = -1
    max_node = -1
    for i in range(1, n + 1): 
        if max_dist < dist_array[i]: 
            max_dist = dist_array[i]
            max_node = i
    
    return max_dist


if __name__ == "__main__":
    # take the tree from input
    maxn = 100000
    v = [[] for _ in range(maxn + 1)] 
    n = int(input())
    m = n - 1
    for _ in range(m): 
        x, y = map(int, input().split())  
        v[x].append(y) 
        v[y].append(x)
    
    # print the diameter of the tree
    print(diameter())