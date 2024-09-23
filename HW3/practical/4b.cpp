#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

class DSU {
public:
  DSU(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  void merge(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) {
      return;
    }
    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
    } else {
      parent[rootY] = rootX;
      if (rank[rootX] == rank[rootY]) {
        rank[rootX]++;
      }
    }
  }

private:
  std::vector<int> parent;
  std::vector<int> rank;
};

int main() {
  int n, m;
  std::cin >> n >> m;

  DSU dsu(n);
  // All cities are connected initially, so count total cases (2^n)
  long long total_cases = 1LL << n;

  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    // Decrement total cases if merging doesn't happen (means removing a road leads to disconnection)
    if (dsu.find(u) != dsu.find(v)) {
      total_cases = (total_cases - 1 + MOD) % MOD;
    }
    dsu.merge(u, v);
  }

  std::cout << total_cases % MOD << std::endl;
  return 0;
}