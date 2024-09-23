#pragma GCC optimize("Ofast,unroll-loops,fast-math")
#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define ll int
#define F first
#define S second
#define pii pair<ll, ll>
#define pb push_back
#define endl '\n'
#define ENDL " \n"[i == n - 1]

const int maxn = 1e6 + 10;
 
bool mark[maxn], is[maxn];
int dp[maxn], h[maxn], ans, counter, counter_edge;
vector<pii> adj[maxn];
vector <pii> edge;
map <ll, ll> mp[maxn];
 
void dfs(int v, int parent, int index)
{
	dp[v] = h[v];
	mark[v] = true;
	for(int i = 0; i < adj[v].size(); i++)
    {
		int u = adj[v][i].F;
		int ind = adj[v][i].S;
		if(!mark[u])
        {
			h[u] = h[v] + 1;
			dfs(u, v, ind);
			dp[v] = min(dp[v], dp[u]);
		}
		else if(u != parent)
			dp[v] = min(dp[v], h[u]);
	}
	if(v != 1 && dp[v] == h[v])
		is[index] = true;
	return;
}
 
int32_t main()
{
    int n, m;
	cin >> n >> m;
    counter_edge = 0;
	for(int i = 0; i < m; i++)
    {
		int u, v;
		cin >> u >> v;
        if(u > v) swap(u, v);
        if(u != v)
        {
            if(!mp[u][v])
            {
                adj[u].pb({v, counter_edge});
                adj[v].pb({u, counter_edge});
                edge.pb({u, v});
                counter_edge++;
            }
            mp[u][v]++;
        }
	}
	dfs(1, 0, 0);
	for(int i = 0; i < counter_edge; i++)
		if(is[i] && mp[edge[i].F][edge[i].S] == 1)
			ans++;
    cout << ans;
}