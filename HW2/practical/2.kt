import java.util.*

class HopcroftKarp(private val graph: Map<Char, Set<Char>>) {
    private val pairU = mutableMapOf<Char, Char?>().withDefault { null }
    private val pairV = mutableMapOf<Char, Char?>().withDefault { null }
    private val dist = mutableMapOf<Char?, Int>()
    private var maxMatching = 0

    init {
        graph.keys.forEach { u ->
            if (pairU[u] == null) {
                dist[u] = 0
            } else {
                dist[u] = Int.MAX_VALUE
            }
        }
        dist[null] = Int.MAX_VALUE
    }

    fun bfs(): Boolean {
        val queue = LinkedList<Char>()
        graph.keys.forEach { u ->
            if (pairU[u] == null) {
                queue.offer(u)
            }
        }

        while (queue.isNotEmpty()) {
            val u = queue.poll()
            if (u != null) {
                graph[u]?.forEach { v ->
                    if (dist[pairV[v]] == Int.MAX_VALUE) {
                        dist[pairV[v]] = dist[u]!! + 1
                        queue.offer(pairV[v])
                    }
                }
            }
        }
        return dist[null] != Int.MAX_VALUE
    }

    fun dfs(u: Char?): Boolean {
        if (u != null) {
            graph[u]?.forEach { v ->
                if (dist[pairV[v]] == dist[u]!! + 1) {
                    if (dfs(pairV[v])) {
                        pairV[v] = u
                        pairU[u] = v
                        return true
                    }
                }
            }
            dist[u] = Int.MAX_VALUE
            return false
        }
        return true
    }

    fun maxMatchingSize(): Int {
        while (bfs()) {
            graph.keys.forEach { u ->
                if (pairU[u] == null && dfs(u)) {
                    maxMatching++
                }
            }
        }
        return maxMatching / 2
    }
}

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

fun maximumMatching(inputString: String): Int {
    val (graph, _, _) = parseInput(inputString)
    val hk = HopcroftKarp(graph)
    return hk.maxMatchingSize()
}

fun main() {
    println(maximumMatching(readLine() ?: ""))
}
