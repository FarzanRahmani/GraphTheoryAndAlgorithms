#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

class HopcroftKarp {
    /*
    Implementation of the Hopcroft-Karp algorithm for finding the maximum cardinality matching in a bipartite graph.

    Attributes:
        graph: A dictionary where the keys are vertices in the first part and the values are sets of neighbors in the second part.
        pair_u: A dictionary where the keys are vertices in the first part and the values are their corresponding matched vertices in the second part.
        pair_v: A dictionary where the keys are vertices in the second part and the values are their corresponding matched vertices in the first part.
        dist: A dictionary to store the distance of each vertex from the source.
        max_matching: An integer to store the size of the maximum matching.

    Methods:
        bfs: Breadth-first search to find the shortest augmenting path.
        dfs: Depth-first search to recursively find augmenting paths.
        max_matching_size: Find the maximum cardinality matching in the bipartite graph.
    */

public:
    unordered_map<char, unordered_set<char>> graph;
    unordered_map<char, char> pair_u;
    unordered_map<char, char> pair_v;
    unordered_map<char, int> dist;
    int max_matching;

    HopcroftKarp(unordered_map<char, unordered_set<char>>& graph) {
        /*
        Initialize the Hopcroft-Karp algorithm with the given bipartite graph.

        Args:
            graph: A dictionary where the keys are vertices in the first part and the values are sets of neighbors in the second part.

        Returns:
            None
        */
        this->graph = graph;
        for (const auto& entry : graph) {
            pair_u[entry.first] = '\0';
        }
        max_matching = 0;
    }

    bool bfs() {
        /*
        Breadth-first search to find the shortest augmenting path.

        Args:
            None

        Returns:
            True if an augmenting path is found, False otherwise.
        */
        queue<char> q;
        for (const auto& entry : graph) {
            if (pair_u[entry.first] == '\0') {
                dist[entry.first] = 0;
                q.push(entry.first);
            } else {
                dist[entry.first] = numeric_limits<int>::max();
            }
        }
        dist['\0'] = numeric_limits<int>::max();

        while (!q.empty()) {
            char u = q.front();
            q.pop();
            if (u != '\0') {
                for (char v : graph[u]) {
                    if (dist[pair_v[v]] == numeric_limits<int>::max()) {
                        dist[pair_v[v]] = dist[u] + 1;
                        q.push(pair_v[v]);
                    }
                }
            }
        }
        return dist['\0'] != numeric_limits<int>::max();
    }

    bool dfs(char u) {
        /*
        Depth-first search to recursively find augmenting paths.

        Args:
            u: A vertex in the first part.

        Returns:
            True if an augmenting path is found, False otherwise.
        */
        if (u != '\0') {
            for (char v : graph[u]) {
                if (dist[pair_v[v]] == dist[u] + 1) {
                    if (dfs(pair_v[v])) {
                        pair_v[v] = u;
                        pair_u[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = numeric_limits<int>::max();
            return false;
        }
        return true;
    }

    int max_matching_size() {
        /*
        Find the maximum cardinality matching in the bipartite graph.

        Args:
            None

        Returns:
            The size of the maximum matching.
        */
        while (bfs()) {
            for (const auto& entry : graph) {
                if (pair_u[entry.first] == '\0' && dfs(entry.first)) {
                    max_matching++;
                }
            }
        }
        return max_matching / 2;
    }
};

pair<unordered_map<char, unordered_set<char>>, pair<unordered_set<char>, unordered_set<string>>> parse_input(const string& input_str) {
    /*
    Parse the input string to construct the graph.

    Args:
        input_str: A string of characters.

    Returns:
        A tuple of three elements:
        - A dictionary where the keys are vertices and the values are sets of neighbors.
        - A set of vertices.
        - A set of edges.
    */
    unordered_map<char, unordered_set<char>> graph;
    unordered_set<char> vertices;
    unordered_set<string> edges;

    int i = 0;
    while (i < input_str.length()) {
        if (input_str[i] == ' ') {
            i++;
            continue;
        } else if ((i == input_str.length() - 1) || input_str[i + 1] == ' ') {
            char isolated_vertex = input_str[i];
            vertices.insert(isolated_vertex);
            if (graph.find(isolated_vertex) == graph.end()) {
                graph[isolated_vertex] = unordered_set<char>();
            }
            i++;
            continue;
        }
        char vertex1 = input_str[i];
        char vertex2 = input_str[i+1];
        string edge = string(1, min(vertex1, vertex2)) + string(1, max(vertex1, vertex2));
        vertices.insert(vertex1);
        vertices.insert(vertex2);
        edges.insert(edge);
        if (graph.find(vertex1) == graph.end()) {
            graph[vertex1] = unordered_set<char>();
        }
        if (graph.find(vertex2) == graph.end()) {
            graph[vertex2] = unordered_set<char>();
        }
        graph[vertex1].insert(vertex2);
        graph[vertex2].insert(vertex1);
        i += 2;
    }

    return {graph, {vertices, edges}};
}

int maximum_matching(const string& input_string) {
    /*
    Find the maximum cardinality matching in the bipartite graph.

    Args:
        input_string: A string of characters.

    Returns:
        The size of the maximum matching.
    */
    auto parsed_input = parse_input(input_string);
    HopcroftKarp hk(parsed_input.first);
    return hk.max_matching_size();
}

int main() {
    /*
    Main function to take user input and call the maximum_matching function.

    Args:
        None.

    Returns:
        0.
    */
    string input_str;
    getline(cin, input_str);
    cout << maximum_matching(input_str) << endl;
    return 0;
}
