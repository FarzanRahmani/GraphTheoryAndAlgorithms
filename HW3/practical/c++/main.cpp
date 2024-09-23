#pragma GCC optimize("Ofast,unroll-loops,fast-math")
#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define ll int
#define X first
#define Y second
#define pii pair<ll, ll>
#define pb push_back
#define endl '\n'
#define ENDL " \n"[i == n - 1]
#define migmig ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define file_io freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)

const ll maxn = 3e5 + 10, mod = 1e9 + 7;
ll n , m , mark[maxn] , h[maxn] , dp[maxn] , d[maxn] , cnt , par[maxn] , col[maxn] , sz[maxn] , pt[maxn] ; 
map<int , int> ise[maxn] , cut[maxn]; 
vector<pair<int , int>> E  , CE; 
vector<int> adj[maxn] , g[maxn] ; 
void sfd(int v){ // rang kardan har moalefe and shomordan size ha
    col[v] = cnt;
    sz[cnt] ++ ;  
    for(auto u : g[v]){
        if(col[u] == 0){
            sfd(u) ; 
        }
    }
}
void dfs(int v){
    mark[v] = 1 ; 
    for(auto u : adj[v]){
        if(!mark[u]){ // children that already computed
            h[u] = h[v] + 1 ;
            par[u] = v ;  
            dfs(u) ; 
            dp[v] = min(dp[v] , dp[u]) ; 
        }else{ // base
            if(u != par[v]){
                dp[v] = min(dp[v] , h[u]) ; // height[u] = height[hamsaye]
            }
        }
    }
    if(dp[v] >= h[v]){ // tooye dfs be ras haye bala tar rah nadare (faghat yek yal dare ke be payyen residim)
        // dp[v] --> bala tarin ras to dfs (min heaight) ke ras v be oon rah dare  
        cut[v][par[v]] = 1 ; 
        cut[par[v]][v] = 1 ; 
        // CE.pb({v , par[v]}); 
    }
}
int32_t main()
{    
    migmig;
    
    cin >> n >> m;
    if(n == 1){
        cout<<1 ; 
        return 0 ; 
    }
    for(int i = 1 ; i <= m ; i ++ ){
        int u , v ;
        cin>>u>>v ; 
        adj[u].push_back(v) ; 
        adj[v].push_back(u) ; 
        E.pb({u , v}) ;  
    }
    pt[0] = 1 ; 
    for(int i= 1 ; i <= n ; i ++ ){
        dp[i] = maxn ; 
        pt[i] = pt[i-1] * 2ll % mod ; 
    }
    dfs(1) ; 
    for(auto ec : E){ // E: edges
        int u = ec.X , v = ec.Y ; 
        if(cut[u][v] == 0){
            g[u].pb(v) ; 
            g[v].pb(u) ;  // g -> new graph without cut edges
        }else{
            CE.pb({u , v});  // CE --> cut edges
        }
    }
    for(int i = 1 ; i <= n ; i ++ ){
        if(col[i] == 0){
            cnt++ ; 
            sfd(i) ; 
        }
    }
    for(auto bor : CE){ // fahmidan daraje har ras dar derakht geraph
        int u = bor.X , v = bor.Y ; 
        u = col[u] ; // u -< color[u]
        v = col[v] ; // v -< color[v]
        d[u]++ ; // d = degree of any component
        d[v]++ ; 
    }
    ll ans = 1 ; 
    for(int i = 1 ; i <= cnt ; i ++ ){ // cnt = color
        if(d[i] <= 1){ // barg d[i] == 1 or d[i] == 0
            ans = ans * (pt[sz[i]] - 1 + mod) % mod ; 
        }else{
            ans = ans * pt[sz[i]] % mod ;  // pt[sz[i]] = 2^sz[i]
        }
    }
    cout<<ans ;   
}