#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int MOD = 1e9 + 7;
vector<int> adj[MAXN];
int tin[MAXN], low[MAXN], timer;
bool vis[MAXN];
int n, m, a, b;
long long fac[MAXN], ifac[MAXN], ans;

long long power(long long a, long long b) {
    long long res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long C(int n, int k) {
    if(k < 0 || k > n) return 0;
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

void dfs(int v, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    for(int to : adj[v]) {
        if(to == p) continue;
        if(vis[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if(low[to] > tin[v]) {
                int s = tin[to], e = timer;
                ans -= C(n, m);
                ans += C(s, m);
                ans += C(n - s, m);
                ans %= MOD;
                if(ans < 0) ans += MOD;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    fac[0] = ifac[0] = 1;
    for(int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        ifac[i] = power(fac[i], MOD - 2);
    }

    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    ans = power(2, n);
    dfs(0);

    cout << ans << "\n";

    return 0;
}
