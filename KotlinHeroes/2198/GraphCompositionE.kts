class DSU(n: Int) {
    val parent = IntArray(n) { it }
    val size = IntArray(n) { 1 }

    fun find(x: Int): Int {
        if (parent[x] != x)
            parent[x] = find(parent[x])
        return parent[x]
    }

    fun union(a: Int, b: Int): Boolean {
        var x = find(a)
        var y = find(b)
        if (x == y) return false
        if (size[x] < size[y]) {
            parent[x] = y
            size[y] += size[x]
        } else {
            parent[y] = x
            size[x] += size[y]
        }
        return true
    }
}

fun main() {
    val t = readln().toInt()
    repeat(t) {
        val (n, m1, m2) = readln().split(" ").map(String::toInt)

        val edgesF = Array(m1) {
            val (u, v) = readln().split(" ").map(String::toInt)
            Pair(u - 1, v - 1)
        }

        val dsuG = DSU(n)
        repeat(m2) {
            val (u, v) = readln().split(" ").map(String::toInt)
            dsuG.union(u - 1, v - 1)
        }

        val dsuF = DSU(n)
        var remove = 0
        var usedInside = 0

        for ((u, v) in edgesF) {
            if (dsuG.find(u) != dsuG.find(v)) {
                remove++
            } else {
                if (dsuF.union(u, v)) {
                    usedInside++
                }
            }
        }

        val compSize = IntArray(n)
        for (i in 0 until n) {
            compSize[dsuG.find(i)]++
        }

        var add = 0
        for (i in 0 until n) {
            if (compSize[i] > 0) {
                add += compSize[i] - 1
            }
        }

        println(remove + add - usedInside)
    }
}