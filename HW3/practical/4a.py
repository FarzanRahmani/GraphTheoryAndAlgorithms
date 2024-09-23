import sys
from collections import defaultdict

MOD = 10**9 + 7
n, m = map(int, sys.stdin.readline().split())
edges = [list(map(int, sys.stdin.readline().split())) for _ in range(m)]
G = defaultdict(list)
for u, v in edges:
    G[u].append(v)
    G[v].append(u)

low = [0] * (n + 1)
num = [0] * (n + 1)
parent = [0] * (n + 1)
child = [0] * (n + 1)
bridge = [0] * (n + 1)
dp = [0] * (n + 1)
dp2 = [0] * (n + 1)
cnt = 0

def dfs(u):
    global cnt
    cnt += 1
    num[u] = cnt
    low[u] = num[u]
    dp[u] = 1
    dp2[u] = 1
    for v in G[u]:
        if v == parent[u]:
            continue
        if num[v] > 0:
            low[u] = min(low[u], num[v])
        else:
            child[u] += 1
            parent[v] = u
            dfs(v)
            low[u] = min(low[u], low[v])
            dp[u] = dp[u] * (dp[v] + 1) % MOD
            dp2[u] = dp2[u] * dp[v] % MOD
        if low[v] >= num[u]:
            bridge[u] = 1

def solve():
    dfs(1)
    bridge[1] = child[1] > 1
    ans = pow(2, n, MOD)
    for u in range(1, n + 1):
        if bridge[u]:
            ans = (ans - pow(2, n - child[u], MOD) * dp[u] % MOD + MOD) % MOD
        else:
            ans = (ans - pow(2, n - child[u] - 1, MOD) * dp2[u] % MOD + MOD) % MOD
    print(ans)

solve()