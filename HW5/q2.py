# find the center of a tree

def find_eccentricity(s, n, adj_list):
    distances = [n] * (n + 1)
    visited = [False] * (n + 1)
    distances[0] = -1
    distances[s] = 0
    queue = [s]
    while len(queue) > 0:
        current_node = queue.pop(0)
        visited[current_node] = True
        for n in adj_list[current_node]:
            if not visited[n]:
                queue.append(n)
                distances[n] = distances[current_node] + 1
    return max(distances)

def find_center_of_tree(n, adj_list):
    eccentricities = [n] * (n + 1)
    for i in range(1, n + 1):
        eccentricities[i] = find_eccentricity(i, n, adj_list)
    center = 0
    eccentricity_center = n
    for i in range(1, len(eccentricities)):
        if eccentricities[i] <= eccentricity_center:
            eccentricity_center = eccentricities[i]
            center = i
    return center

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
    print(find_center_of_tree(n, v))