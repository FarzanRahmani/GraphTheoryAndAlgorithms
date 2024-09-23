using System;
using System.Collections.Generic;

namespace HopcroftKarpAlgorithm
{
    public class HopcroftKarp
    {
        private Dictionary<char, HashSet<char>> graph;
        private Dictionary<char, char> pair_u;
        private Dictionary<char, char> pair_v;
        private Dictionary<char, int> dist;
        private int max_matching;

        public HopcroftKarp(Dictionary<char, HashSet<char>> graph)
        {
            this.graph = graph;
            this.pair_u = new Dictionary<char, char>();
            this.pair_v = new Dictionary<char, char>();
            this.dist = new Dictionary<char, int>();
            this.max_matching = 0;
        }

        public bool BFS()
        {
            Queue<char> queue = new Queue<char>();
            foreach (char u in graph.Keys)
            {
                if (!pair_u.ContainsKey(u))
                {
                    dist[u] = 0;
                    queue.Enqueue(u);
                }
                else
                {
                    dist[u] = int.MaxValue;
                }
            }

            dist[default(char)] = int.MaxValue;
            while (queue.Count > 0)
            {
                char u = queue.Dequeue();
                if (u != default(char))
                {
                    foreach (char v in graph[u])
                    {
                        if (dist[pair_v[v]] == int.MaxValue)
                        {
                            dist[pair_v[v]] = dist[u] + 1;
                            queue.Enqueue(pair_v[v]);
                        }
                    }
                }
            }

            return dist[default(char)] != int.MaxValue;
        }

        public bool DFS(char u)
        {
            if (u != default(char))
            {
                foreach (char v in graph[u])
                {
                    if (dist[pair_v[v]] == dist[u] + 1)
                    {
                        if (DFS(pair_v[v]))
                        {
                            pair_v[v] = u;
                            pair_u[u] = v;
                            return true;
                        }
                    }
                }

                dist[u] = int.MaxValue;
                return false;
            }

            return true;
        }

        public int MaxMatchingSize()
        {
            while (BFS())
            {
                foreach (char u in graph.Keys)
                {
                    if (!pair_u.ContainsKey(u) && DFS(u))
                    {
                        max_matching++;
                    }
                }
            }

            return max_matching / 2;
        }
    }

    public class Program
    {
        public static Dictionary<char, HashSet<char>> ParseInput(string inputStr)
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

            return graph;
        }

        public static int MaximumMatching(string inputString)
        {
            Dictionary<char, HashSet<char>> graph = ParseInput(inputString);
            HopcroftKarp hk = new HopcroftKarp(graph);
            return hk.MaxMatchingSize();
        }

        public static void Main(string[] args)
        {
            string inputString = Console.ReadLine();
            Console.WriteLine(MaximumMatching(inputString));
        }
    }
}
