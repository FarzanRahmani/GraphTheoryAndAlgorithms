import java.util.*

fun parseInput(inputStr: String): Triple<Map<Char, Set<Char>>, Set<Char>, Set<String>> {
    val graph = mutableMapOf<Char, MutableSet<Char>>().withDefault { mutableSetOf() }
    val vertices = mutableSetOf<Char>()
    val edges = mutableSetOf<String>()

    var i = 0
    val sequence = inputStr
    while (i < sequence.length) {
        if (sequence[i] == ' ') {
            i++
            continue
        } else if (i == sequence.length - 1 || sequence[i + 1] == ' ') {
            val isolatedVertex = sequence[i]
            vertices.add(isolatedVertex)
            if (!graph.containsKey(isolatedVertex)) {
                graph[isolatedVertex] = mutableSetOf()
            }
            i++
            continue
        }
        val vertex1 = sequence[i]
        val vertex2 = sequence[i + 1]
        val edge = sequence.substring(i, i + 2).toList().sorted().joinToString("")
        vertices.add(vertex1)
        vertices.add(vertex2)
        edges.add(edge)
        graph[vertex1]?.add(vertex2)
        graph[vertex2]?.add(vertex1)
        i += 2
    }
    return Triple(graph, vertices, edges)
}

fun isBipartite(graph: Map<Char, Set<Char>>, vertices: Set<Char>): Boolean {
    val colors = mutableMapOf<Char, Int>()
    val queue = LinkedList<Char>()

    for (vertex in vertices) {
        if (!colors.containsKey(vertex)) {
            queue.add(vertex)
            colors[vertex] = 0
            
            while (queue.isNotEmpty()) {
                val current = queue.poll()
                for (neighbor in graph[current] ?: emptySet()) {
                    if (!colors.containsKey(neighbor)) {
                        colors[neighbor] = 1 - (colors[current] ?: error("Color not found"))
                        queue.add(neighbor)
                    } else if (colors[neighbor] == colors[current]) {
                        return false
                    }
                }
            }
        }
    }
    return true
}

fun calculateComplementEdges(vertices: Set<Char>, edges: Set<String>): Int {
    val numVertices = vertices.size
    val numEdges = edges.size
    val complementEdges = (numVertices * (numVertices - 1)) / 2 - numEdges
    return complementEdges
}

fun removeEdgesToBipartite(graph: MutableMap<Char, MutableSet<Char>>, vertices: Set<Char>, edges: MutableSet<String>): Int {
    var numRemovedEdges = 0
    
    for (vertex in vertices) {
        val queue = LinkedList<Char>().apply { add(vertex) }
        val colors = mutableMapOf(vertex to 0)

        while (queue.isNotEmpty()) {
            val current = queue.poll()
            val neighbors = graph[current] ?: emptySet()
            for (neighbor in neighbors) {
                if (!colors.containsKey(neighbor)) {
                    colors[neighbor] = 1 - (colors[current] ?: error("Color not found"))
                    queue.add(neighbor)
                } else if (colors[neighbor] == colors[current]) {
                    val edge = listOf(current, neighbor).sorted().joinToString("")
                    if (edges.contains(edge)) {
                        edges.remove(edge)
                        graph[current]?.remove(neighbor)
                        graph[neighbor]?.remove(current)
                        numRemovedEdges++
                        queue.add(0, current)
                        break
                    }
                }
            }
        }
    }
    return numRemovedEdges
}

fun main() {
    val inputStr = readLine() ?: ""
    val (graph, vertices, edges) = parseInput(inputStr)

    if (isBipartite(graph, vertices)) {
        val complementEdges = calculateComplementEdges(vertices, edges)
        println(complementEdges)
    } else {
        val numTotalEdges = edges.size
        val numRemovedEdges = removeEdgesToBipartite(graph, vertices, edges)
        println(numTotalEdges - numRemovedEdges)
    }
}
