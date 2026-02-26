import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

private lateinit var br: BufferedReader
private fun rl() = br.readLine()!!
private fun ri(): IntArray { val st = StringTokenizer(rl()); return IntArray(st.countTokens()) { st.nextToken().toInt() } }

private const val MAXN = 200005
private const val LOG = 18
private const val INF = Int.MAX_VALUE / 2

// DSU
private val par = IntArray(MAXN)
private val rnk = IntArray(MAXN)
private fun dsuInit(n: Int) { for (i in 1..n) { par[i] = i; rnk[i] = 0 } }
private fun find(x: Int): Int { var v = x; while (par[v] != v) { par[v] = par[par[v]]; v = par[v] }; return v }
private fun unite(a: Int, b: Int): Boolean {
    val pa = find(a); val pb = find(b); if (pa == pb) return false
    if (rnk[pa] >= rnk[pb]) { par[pb] = pa; if (rnk[pa] == rnk[pb]) rnk[pa]++ }
    else par[pa] = pb
    return true
}

// LCA + path-min with binary lifting
private val dep = IntArray(MAXN)
private val anc = Array(LOG) { IntArray(MAXN) }
private val minE = Array(LOG) { IntArray(MAXN) }

private val adj = Array(MAXN) { mutableListOf<IntArray>() }
private val visited = BooleanArray(MAXN)
private val bfsQ = IntArray(MAXN)

private fun bfs(root: Int) {
    var head = 0; var tail = 0
    bfsQ[tail++] = root; visited[root] = true
    dep[root] = 0; anc[0][root] = root; minE[0][root] = INF
    while (head < tail) {
        val v = bfsQ[head++]
        for (e in adj[v]) {
            val u = e[0]; val w = e[1]
            if (!visited[u]) {
                visited[u] = true; dep[u] = dep[v] + 1
                anc[0][u] = v; minE[0][u] = w
                bfsQ[tail++] = u
            }
        }
    }
    for (k in 1 until LOG) {
        for (i in 0 until tail) {
            val v = bfsQ[i]; val mid = anc[k-1][v]
            anc[k][v] = anc[k-1][mid]
            minE[k][v] = minOf(minE[k-1][v], minE[k-1][mid])
        }
    }
}

private fun lca(u0: Int, v0: Int): Int {
    var u = u0; var v = v0
    if (dep[u] < dep[v]) { val t = u; u = v; v = t }
    var d = dep[u] - dep[v]
    for (k in 0 until LOG) if ((d shr k) and 1 == 1) u = anc[k][u]
    if (u == v) return u
    for (k in LOG-1 downTo 0) if (anc[k][u] != anc[k][v]) { u = anc[k][u]; v = anc[k][v] }
    return anc[0][u]
}

private fun pathMin(u0: Int, v0: Int): Int {
    var u = u0; var v = v0; var res = INF
    if (dep[u] < dep[v]) { val t = u; u = v; v = t }
    var d = dep[u] - dep[v]
    for (k in 0 until LOG) if ((d shr k) and 1 == 1) { res = minOf(res, minE[k][u]); u = anc[k][u] }
    if (u == v) return res
    for (k in LOG-1 downTo 0) if (anc[k][u] != anc[k][v]) {
        res = minOf(res, minE[k][u], minE[k][v]); u = anc[k][u]; v = anc[k][v]
    }
    return minOf(res, minE[0][u], minE[0][v])
}

private fun traceToLca(u: Int, l: Int): MutableList<Int> {
    val path = mutableListOf<Int>(); var v = u
    while (v != l) { path.add(v); v = anc[0][v] }
    return path
}

fun main() {
    br = BufferedReader(InputStreamReader(System.`in`))
    val sb = StringBuilder()
    repeat(ri()[0]) {
        val line = ri(); val n = line[0]; val m = line[1]
        val edges = Array(m) { val a = ri(); intArrayOf(a[2], a[0], a[1]) }
        edges.sortBy { it[0] }

        dsuInit(n)
        for (i in 1..n) { adj[i].clear(); visited[i] = false }

        val backEdges = mutableListOf<IntArray>()
        for (e in edges) {
            val w = e[0]; val u = e[1]; val v = e[2]
            if (!unite(u, v)) backEdges.add(e)
            else { adj[u].add(intArrayOf(v, w)); adj[v].add(intArrayOf(u, w)) }
        }

        for (r in 1..n) if (!visited[r]) bfs(r)

        var bestMin = INF; var bestU = -1; var bestV = -1
        for (be in backEdges) {
            val pm = pathMin(be[1], be[2])
            if (pm < bestMin) { bestMin = pm; bestU = be[1]; bestV = be[2] }
        }

        val l = lca(bestU, bestV)
        val pu = traceToLca(bestU, l)
        val pv = traceToLca(bestV, l)
        pu.add(l)
        sb.append(bestMin).append(' ').append(pu.size + pv.size).append('\n')
        for (v2 in pu) sb.append(v2).append(' ')
        for (i in pv.indices.reversed()) sb.append(pv[i]).append(' ')
        sb.append('\n')
    }
    print(sb)
}