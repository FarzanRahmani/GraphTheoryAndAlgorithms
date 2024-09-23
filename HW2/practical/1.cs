using System;
using System.Collections.Generic;

public class Program
{
    public static void Main(string[] args)
    {
        string inputStr = Console.ReadLine();
        Tuple<Dictionary<char, HashSet<char>>, HashSet<char>, HashSet<string>> result = ParseInput(inputStr);
        Dictionary<char, HashSet<char>> graph = result.Item1;
        HashSet<char> vertices = result.Item2;
        HashSet<string> edges = result.Item3;

        if (IsBipartite(graph, vertices))
        {
            int complementEdges = CalculateComplementEdges(vertices, edges);
            Console.WriteLine(complementEdges);
        }
        else
        {
            int numTotalEdges = edges.Count;
            int numRemovedEdges = RemoveEdgesToBipartite(graph, vertices, edges);
            Console.WriteLine(numTotalEdges - numRemovedEdges);
        }
    }

    public static Tuple<Dictionary<char, HashSet<char>>, HashSet<char>, HashSet<string>> ParseInput(string inputStr)
    {
        Dictionary<char, HashSet<char>> graph = new Dictionary<char, HashSet<char>>();
        HashSet<char> vertices = new HashSet<char>();
        HashSet<string> edges = new HashSet<string>();

        int i = 0;
        string sequence = inputStr;
        while (i < sequence.Length)
        {
            if (sequence[i] == ' ')
            {
                i++;
                continue;
            }
            else if (i == sequence.Length - 1 || sequence[i + 1] == ' ')
            {
                char isolatedVertex = sequence[i];
                vertices.Add(isolatedVertex);
                if (!graph.ContainsKey(isolatedVertex))
                {
                    graph[isolatedVertex] = new HashSet<char>();
                }
                i++;
                continue;
            }
            char vertex1 = sequence[i];
            char vertex2 = sequence[i + 1];
            string edge = new string(new char[] { vertex1, vertex2 });
            vertices.Add(vertex1);
            vertices.Add(vertex2);
            edges.Add(edge);
            if (!graph.ContainsKey(vertex1))
            {
                graph[vertex1] = new HashSet<char>();
            }
            if (!graph.ContainsKey(vertex2))
            {
                graph[vertex2] = new HashSet<char>();
            }
            graph[vertex1].Add(vertex2);
            graph[vertex2].Add(vertex1);
            i += 2;
        }

        return Tuple.Create(graph, vertices, edges);
    }

    public static bool IsBipartite(Dictionary<char, HashSet<char>> graph, HashSet<char> vertices)
    {
        Dictionary<char, int> colors = new Dictionary<char, int>();
        Queue<char> queue = new Queue<char>();

        foreach (char vertex in vertices)
        {
            if (!colors.ContainsKey(vertex))
            {
                queue.Enqueue(vertex);
                colors[vertex] = 0;

                while (queue.Count > 0)
                {
                    char current = queue.Dequeue();
                    foreach (char neighbor in graph[current])
                    {
                        if (!colors.ContainsKey(neighbor))
                        {
                            colors[neighbor] = 1 - colors[current];
                            queue.Enqueue(neighbor);
                        }
                        else if (colors[neighbor] == colors[current])
                        {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }

    public static int CalculateComplementEdges(HashSet<char> vertices, HashSet<string> edges)
    {
        int numVertices = vertices.Count;
        int numEdges = edges.Count;
        int complementEdges = (numVertices * (numVertices - 1)) / 2 - numEdges;
        return complementEdges;
    }

    public static int RemoveEdgesToBipartite(Dictionary<char, HashSet<char>> graph, HashSet<char> vertices, HashSet<string> edges)
    {
        int numRemovedEdges = 0;

        foreach (char vertex in vertices)
        {
            Queue<char> queue = new Queue<char>();
            Dictionary<char, int> colors = new Dictionary<char, int>();
            queue.Enqueue(vertex);
            colors[vertex] = 0;

            while (queue.Count > 0)
            {
                char current = queue.Dequeue();
                HashSet<char> neighbors = new HashSet<char>(graph[current]);
                foreach (char neighbor in neighbors)
                {
                    if (!colors.ContainsKey(neighbor))
                    {
                        colors[neighbor] = 1 - colors[current];
                        queue.Enqueue(neighbor);
                    }
                    else if (colors[neighbor] == colors[current])
                    {
                        string edge = new string(new char[] { current, neighbor });
                        if (edges.Contains(edge))
                        {
                            edges.Remove(edge);
                            graph[current].Remove(neighbor);
                            if (edge[0] != edge[1])
                            {
                                graph[neighbor].Remove(current);
                            }
                            numRemovedEdges++;
                            queue.Enqueue(current);
                            break;
                        }
                    }
                }
            }
        }

        return numRemovedEdges;
    }
}
