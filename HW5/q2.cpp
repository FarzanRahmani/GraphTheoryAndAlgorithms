#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
using namespace std;
#define ll long long
vector<ll> find_center_node(const unordered_map<ll, vector<ll>>& adj_list)
{
    ll n = adj_list.size();
    vector<ll> degree(n, 0);
    deque<ll> leaves;
    for (const auto& entry : adj_list) 
    {
        ll i = entry.first;
        degree[i] = entry.second.size();
        if (degree[i] == 1) 
        {
            leaves.push_back(i);
        }
    }
    while (n > 2) 
    {
        ll leaves_count = leaves.size();
        n -= leaves_count;
        for (ll i = 0; i < leaves_count; ++i) 
        {
            ll leaf = leaves.front();
            leaves.pop_front();
            for (ll neighbor : adj_list.at(leaf)) 
            {
                degree[neighbor] -= 1;
                if (degree[neighbor] == 1) 
                {
                    leaves.push_back(neighbor);
                }
            }
        }
    }
    vector<ll> result(leaves.begin(), leaves.end());
    return result;
}

int main() 
{
    ll num_vertices;
    cin >> num_vertices;
    unordered_map<ll, vector<ll>> adj_list;
    for (ll i = 0; i < num_vertices - 1; ++i) 
    {
        ll u, v;
        cin >> u >> v;
        adj_list[u - 1].push_back(v - 1);
        adj_list[v - 1].push_back(u - 1);
    }
    vector<ll> center_nodes = find_center_node(adj_list);
    if (center_nodes.size() == 1) 
    {
        cout << center_nodes[0] + 1 << endl;
    } else 
    {
        cout << max(center_nodes[0], center_nodes[1]) + 1 << endl;
    }
    return 0;
}