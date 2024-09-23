package main

import (
	"fmt"
	"sort"
)

func parseInput(inputStr string) (map[rune]map[rune]bool, map[rune]bool, map[string]bool) {
	graph := make(map[rune]map[rune]bool)
	vertices := make(map[rune]bool)
	edges := make(map[string]bool)

	i := 0
	sequence := []rune(inputStr)
	for i < len(sequence) {
		if sequence[i] == ' ' {
			i++
			continue
		} else if (i == len(sequence)-1) || sequence[i+1] == ' ' {
			isolatedVertex := sequence[i]
			vertices[isolatedVertex] = true
			if _, ok := graph[isolatedVertex]; !ok {
				graph[isolatedVertex] = make(map[rune]bool)
			}
			i++
			continue
		}
		vertex1 := sequence[i]
		vertex2 := sequence[i+1]
		edge := string(sortRunes([]rune{vertex1, vertex2}))
		vertices[vertex1] = true
		vertices[vertex2] = true
		edges[edge] = true
		if _, ok := graph[vertex1]; !ok {
			graph[vertex1] = make(map[rune]bool)
		}
		if _, ok := graph[vertex2]; !ok {
			graph[vertex2] = make(map[rune]bool)
		}
		graph[vertex1][vertex2] = true
		graph[vertex2][vertex1] = true
		i += 2
	}
	return graph, vertices, edges
}

func isBipartite(graph map[rune]map[rune]bool, vertices map[rune]bool) bool {
	colors := make(map[rune]int)
	for vertex := range vertices {
		if _, ok := colors[vertex]; !ok {
			queue := []rune{vertex}
			colors[vertex] = 0

			for len(queue) > 0 {
				current := queue[0]
				queue = queue[1:]
				for neighbor := range graph[current] {
					if _, ok := colors[neighbor]; !ok {
						colors[neighbor] = 1 - colors[current]
						queue = append(queue, neighbor)
					} else if colors[neighbor] == colors[current] {
						return false
					}
				}
			}
		}
	}
	return true
}

func calculateComplementEdges(vertices map[rune]bool, edges map[string]bool) int {
	numVertices := len(vertices)
	numEdges := len(edges)
	complementEdges := (numVertices * (numVertices - 1)) / 2 - numEdges
	return complementEdges
}

func removeEdgesToBipartite(graph map[rune]map[rune]bool, vertices map[rune]bool, edges map[string]bool) int {
	numRemovedEdges := 0

	for vertex := range vertices {
		queue := []rune{vertex}
		colors := map[rune]int{vertex: 0}
		for len(queue) > 0 {
			current := queue[0]
			queue = queue[1:]
			for neighbor := range graph[current] {
				if _, ok := colors[neighbor]; !ok {
					colors[neighbor] = 1 - colors[current]
					queue = append(queue, neighbor)
				} else if colors[neighbor] == colors[current] {
					edge := string(sortRunes([]rune{current, neighbor}))
					if edges[edge] {
						delete(edges, edge)
						delete(graph[current], neighbor)
						if current != neighbor {
							delete(graph[neighbor], current)
						}
						numRemovedEdges++
						queue = append([]rune{current}, queue...)
						break
					}
				}
			}
		}
	}
	return numRemovedEdges
}

func main() {
	inputStr := "abacdedfsopwkslskc"
	graph, vertices, edges := parseInput(inputStr)

	if isBipartite(graph, vertices) {
		complementEdges := calculateComplementEdges(vertices, edges)
		fmt.Println(complementEdges)
	} else {
		numTotalEdges := len(edges)
		numRemovedEdges := removeEdgesToBipartite(graph, vertices, edges)
		fmt.Println(numTotalEdges - numRemovedEdges)
	}
}

func sortRunes(runes []rune) []rune {
	sort.Slice(runes, func(i, j int) bool { return runes[i] < runes[j] })
	return runes
}
