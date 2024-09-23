#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

unordered_map<char, unordered_set<char>> parse_input(const string& input_str) {
    /*
    Parse the input string to create a graph, vertices, and edges.
    The input string is a sequence of characters, where each pair of characters represents an edge.
    If a character is isolated, it is considered a vertex.

    Args:
        input_str: A string of characters.

    Returns:
        graph: A dictionary where the keys are vertices and the values are sets of neighbors.
        vertices: A set of vertices.
        edges: A set of edges.
    */
    unordered_map<char, unordered_set<char>> graph; // Use unordered_map to avoid key errors
    unordered_set<char> vertices; // Use unordered_set to avoid duplicates
    unordered_set<string> edges; // Use unordered_set to avoid duplicates

    int i = 0; // Index of the current character
    while (i < input_str.length()) {
        if (input_str[i] == ' ') { // Skip spaces
            i++;
            continue;
        } else if ((i == input_str.length() - 1) || input_str[i + 1] == ' ') { // Isolated vertex if the next character is a space or the last character
            char isolated_vertex = input_str[i];
            vertices.insert(isolated_vertex);
            if (graph.find(isolated_vertex) == graph.end()) { // Add the isolated vertex to the graph with an empty set of neighbors
                graph[isolated_vertex] = unordered_set<char>();
            }
            i++;
            continue;
        }
        char vertex1 = input_str[i];
        char vertex2 = input_str[i+1];
        string edge = string(1, min(vertex1, vertex2)) + string(1, max(vertex1, vertex2)); // Sort the characters to avoid duplicates
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
    return graph;
}

bool is_bipartite(unordered_map<char, unordered_set<char>>& graph, unordered_set<char>& vertices) {
    /*
    Check if the graph is bipartite using BFS.

    Args:
        graph: A dictionary where the keys are vertices and the values are sets of neighbors.
        vertices: A set of vertices.

    Returns:
        True if the graph is bipartite, False otherwise.
    */
    unordered_map<char, int> colors; // Use a dictionary to store the color of each vertex
    queue<char> q; // Use a queue to perform BFS

    for (char vertex : vertices) { // Check each connected component
        if (colors.find(vertex) == colors.end()) { // Skip vertices that have been visited
            q.push(vertex);
            colors[vertex] = 0; // Assign color 0 to the first vertex

            while (!q.empty()) { // Perform BFS
                char current = q.front();
                q.pop();
                for (char neighbor : graph[current]) {
                    if (colors.find(neighbor) == colors.end()) { // Skip vertices that have been visited
                        colors[neighbor] = 1 - colors[current]; // Assign the opposite color
                        q.push(neighbor);
                    } else if (colors[neighbor] == colors[current]) { // Check if the graph is bipartite
                        return false; // Not bipartite
                    }
                }
            }
        }
    }
    return true;
}

int calculate_complement_edges(const unordered_set<char>& vertices, const unordered_set<string>& edges) {
    /*
    Calculate the number of edges in the complement graph.

    Args:
        vertices: A set of vertices.
        edges: A set of edges.

    Returns:
        The number of edges in the complement graph.
    */
    int num_vertices = vertices.size();
    int num_edges = edges.size();
    int complement_edges = (num_vertices * (num_vertices - 1)) / 2 - num_edges;
    return complement_edges;
}

int remove_edges_to_bipartite(unordered_map<char, unordered_set<char>>& graph, unordered_set<char>& vertices, unordered_set<string>& edges) {
    /*
    Remove edges to make the graph bipartite using BFS.

    Args:
        graph: A dictionary where the keys are vertices and the values are sets of neighbors.
        vertices: A set of vertices.
        edges: A set of edges.

    Returns:
        The number of removed edges.
    */
    int num_removed_edges = 0;

    // Use BFS to find connected components and remove edges to make it bipartite
    for (char vertex : vertices) {
        queue<char> q;
        unordered_map<char, int> colors = {{vertex, 0}}; // Assign color 0 to the first vertex
        q.push(vertex);
        while (!q.empty()) {
            char current = q.front();
            q.pop();
            for (char neighbor : graph[current]) {
                if (colors.find(neighbor) == colors.end()) {
                    colors[neighbor] = 1 - colors[current]; // Assign the opposite color
                    q.push(neighbor);
                } else if (colors[neighbor] == colors[current]) {
                    // Remove an edge between current and neighbor
                    string edge = string(1, min(current, neighbor)) + string(1, max(current, neighbor));
                    if (edges.find(edge) != edges.end()) {
                        edges.erase(edge);
                        graph[current].erase(neighbor);
                        if (current != neighbor) {
                            graph[neighbor].erase(current);
                        }
                        num_removed_edges++;
                        q.push(current);
                        break;
                    }
                }
            }
        }
    }
    return num_removed_edges;
}

void main_function(const string& input_str) {
    /*
    Main function to parse the input string, calculate the output, and print it.

    Args:
        input_str: A string of characters.

    Returns:
        None.
    */
    unordered_map<char, unordered_set<char>> graph = parse_input(input_str); // Parse the input string
    unordered_set<char> vertices;
    unordered_set<string> edges;
    for (const auto& entry : graph) {
        vertices.insert(entry.first);
        for (char neighbor : entry.second) {
            edges.insert(string(1, min(entry.first, neighbor)) + string(1, max(entry.first, neighbor)));
        }
    }

    if (is_bipartite(graph, vertices)) { // Check if the graph is bipartite
        int complement_edges = calculate_complement_edges(vertices, edges); // Calculate the number of edges in the complement graph
        cout << complement_edges << endl; // Print the number of edges in the complement graph
    } else { // Remove edges to make the graph bipartite
        int num_total_edges = edges.size(); // Store the number of edges before removing
        int num_removed_edges = remove_edges_to_bipartite(graph, vertices, edges); // Remove edges to make the graph bipartite
        cout << num_total_edges - num_removed_edges << endl; // Calculate the number of edges in the complement graph
    }
}

int main() {
    /*
    Main function to take user input and call the main_function.

    Args:
        None.

    Returns:
        0.
    */
    string input_str;
    getline(cin, input_str);
    main_function(input_str);
    return 0;
}
