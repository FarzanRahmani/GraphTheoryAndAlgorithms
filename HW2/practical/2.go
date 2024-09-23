package main

import (
	"fmt"
	"sort"
)

type HopcroftKarp struct {
	graph        map[rune]map[rune]bool
	pairU        map[rune]rune
	pairV        map[rune]rune
	dist         map[rune]int
	maxMatching  int
}

func NewHopcroftKarp(graph map[rune]map[rune]bool) *HopcroftKarp {
	return &HopcroftKarp{
		graph:       graph,
		pairU:       make(map[rune]rune),
		pairV:       make(map[rune]rune),
		dist:        make(map[rune]int),
		maxMatching: 0,
	}
}

func (hk *HopcroftKarp) bfs() bool {
	queue := make([]rune, 0)
	for u := range hk.graph {
		if hk.pairU[u] == 0 {
			hk.dist[u] = 0
			queue = append(queue, u)
		} else {
			hk.dist[u] = -1
		}
	}

	hk.dist[0] = -1
	for len(queue) > 0 {
		u := queue[0]
		queue = queue[1:]
		if u != 0 {
			for v := range hk.graph[u] {
				if hk.dist[hk.pairV[v]] == -1 {
					hk.dist[hk.pairV[v]] = hk.dist[u] + 1
					queue = append(queue, hk.pairV[v])
				}
			}
		}
	}
	return hk.dist[0] != -1
}

func (hk *HopcroftKarp) dfs(u rune) bool {
	if u != 0 {
		for v := range hk.graph[u] {
			if hk.dist[hk.pairV[v]] == hk.dist[u]+1 {
				if hk.dfs(hk.pairV[v]) {
					hk.pairV[v] = u
					hk.pairU[u] = v
					return true
				}
			}
		}
		hk.dist[u] = -1
		return false
	}
	return true
}

func (hk *HopcroftKarp) maxMatchingSize() int {
	for hk.bfs() {
		for u := range hk.graph {
			if hk.pairU[u] == 0 && hk.dfs(u) {
				hk.maxMatching++
			}
		}
	}
	return hk.maxMatching
}

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

func maximumMatching(inputString string) int {
	graph, _, _ := parseInput(inputString)
	hk := NewHopcroftKarp(graph)
	return hk.maxMatchingSize()
}

func sortRunes(runes []rune) []rune {
	sort.Slice(runes, func(i, j int) bool { return runes[i] < runes[j] })
	return runes
}

func main() {
	fmt.Println(maximumMatching("abacdedfsopwkslskc")) // Output: 5
	fmt.Println(maximumMatching("abacbcbebddeegeffgghhigiijkjkljllnlmmnnpnopororqoqqtsqstsuuvuwvwwxwyxyzx")) // Output: 13
}
