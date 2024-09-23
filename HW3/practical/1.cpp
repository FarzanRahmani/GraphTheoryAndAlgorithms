#include <iostream>
#include <vector>
#include <set>

using namespace std;

// #define int long long

const int MAX_NUMERIC = 100005;

vector<int> adjacencyList[MAX_NUMERIC];
int visited[MAX_NUMERIC];

void addEdge(int x, int y) {
    adjacencyList[x].push_back(y);
    adjacencyList[y].push_back(x);
}

void dfs(int node) {
    visited[node] = 1;
    for (auto neighbor : adjacencyList[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
}

int main()
{

    int n, m, u, v, res = 0;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        u--; v--;
        addEdge(u, v);
    }

    set<int> father;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (!adjacencyList[i].empty()) {
                father.insert(i);
            }
            dfs(i);
        }
    }

    for (int i = 0; i < n; i++) {
        if (adjacencyList[i].size() % 2 != 0) {
            res++;
        }
    }

    if (res <= 2 && father.size() < 2) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
