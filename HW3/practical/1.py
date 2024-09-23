# A graph is Eulerian if and only if all its vertices have even degrees and all of its
# edges belong to a single component.

import sys
from collections import deque

def dfs(node):
    visited[node - 1] = True

    for i in edges[node]:
        if visited[i - 1] == False:
            dfs(i)

def is_connected():
	for i in range(1, n + 1):
		if len(edges[i]) != 0:
			break
	if i == n:
		return True

	dfs(i)
	for i in range(n):
		if visited[i] == False and len(edges[i + 1]) > 0:
			return False
	return True

def is_eulerian(graph):
    r = []
    for i in graph:
        r.append(len(graph[i]) % 2)
    
    odds = r.count(1)
    if odds == 0 or odds == 2:
        return True

    return False

n, m = map(int, input().split())

edges = {}
for i in range(1, n + 1):
    edges[i] = []

for i in range(m):
    edge_info = input().split()

    src = int(edge_info[0])
    dst = int(edge_info[1])
    if src != dst and dst not in edges[src] and src >= 0 and dst >= 0 and src <= n and dst <= n:
        edges[src].append(dst)
        edges[dst].append(src)

sys.setrecursionlimit(10 ** 6)

visited = [False] * n

if not is_connected():
	print("NO")
else:
	result = is_eulerian(edges)

	if result:
		print("YES")
	else:
		print("NO")
