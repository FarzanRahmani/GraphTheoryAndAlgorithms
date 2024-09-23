def find_path(current, target, parent, path):
    """
    Recursively finds the path from the current vertex to the target vertex in the tree.

    Parameters:
    - current: The current vertex being visited.
    - target: The target vertex to find.
    - parent: The parent vertex of the current vertex.
    - path: List to store the path from the current to the target vertex.

    Returns:
    - True if the target vertex is found, otherwise False.
    """
    if current == target:
        path.append(current)
        return True

    for neighbor in tree[current]:
        if neighbor == parent:
            continue
        if find_path(neighbor, target, current, path):
            path.append(current)
            return True
    return False

def find_farthest_node(vertex, parent, distance):
    """
    Recursively finds the farthest node from the given vertex and updates the global variables.

    Parameters:
    - vertex: The current vertex being visited.
    - parent: The parent vertex of the current vertex.
    - distance: The distance from the starting vertex to the current vertex.
    """
    global max_distance, farthest_node
    if distance > max_distance:
        max_distance = distance
        farthest_node = vertex
    if vertex in tree:
        for neighbor in tree[vertex]:
            if neighbor == parent:
                continue
            find_farthest_node(neighbor, vertex, distance + 1)

def find_tree_center(n, edges):
    """
    Finds the center of the tree by first finding the diameter and then locating the central node(s).

    Parameters:
    - n: The number of nodes in the tree.
    - edges: The adjacency list representing the tree.

    Returns:
    - The center node of the tree.
    """
    global farthest_node, max_distance
    path = []
    max_distance = -1
    farthest_node = -1

    # Find the farthest node from an arbitrary starting node (1)
    find_farthest_node(1, -1, 0)
    leaf1 = farthest_node

    # Find the farthest node from leaf1 to get the diameter's endpoints
    max_distance = -1
    find_farthest_node(leaf1, -1, 0)
    leaf2 = farthest_node

    # Find the path representing the diameter of the tree
    find_path(leaf1, leaf2, -1, path)
    path_length = len(path)

    # Determine the center of the path
    if path_length % 2 == 1:
        return path[path_length // 2]
    else:
        mid = path_length // 2
        return max(path[mid - 1], path[mid])

tree = {}
n = int(input())
for _ in range(n - 1):
    u, v = map(int, input().split())
    if u not in tree:
        tree[u] = []
    tree[u].append(v)
    if v not in tree:
        tree[v] = []
    tree[v].append(u)

center_node = find_tree_center(n, tree)
print(center_node)
