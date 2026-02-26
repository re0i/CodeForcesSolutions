fun main() {
    val br = System.`in`.bufferedReader()
    val t = br.readLine().trim().toInt()
    val sb = StringBuilder()

    val TABLE_SIZE = 1 shl 19
    val MASK = TABLE_SIZE - 1
    val keys = LongArray(TABLE_SIZE)
    val vals = LongArray(TABLE_SIZE)
    val stamps = IntArray(TABLE_SIZE) { -1 }
    var epoch = 0

    fun hash(key: Long): Int {
        var h = key * -7046029254386353131L
        h = h xor (h ushr 32)
        return (h and MASK.toLong()).toInt()
    }

    fun tableAdd(key: Long, delta: Long) {
        var i = hash(key)
        while (stamps[i] == epoch && keys[i] != key) i = (i + 1) and MASK
        if (stamps[i] != epoch) { stamps[i] = epoch; keys[i] = key; vals[i] = 0L }
        vals[i] += delta
    }

    fun tableGet(key: Long): Long {
        var i = hash(key)
        while (stamps[i] == epoch && keys[i] != key) i = (i + 1) and MASK
        return if (stamps[i] != epoch) 0L else vals[i]
    }

    fun countSubsegments(arr: LongArray, n: Int, s: Long, maxAllowed: Long): Long {
        var result = 0L
        var prefixSum = 0L
        epoch++
        tableAdd(0L, 1L)
        for (j in 0 until n) {
            val v = arr[j]
            if (v > maxAllowed) {
                epoch++
                prefixSum = 0L
                tableAdd(0L, 1L)
            } else {
                prefixSum += v
                result += tableGet(prefixSum - s)
                tableAdd(prefixSum, 1L)
            }
        }
        return result
    }

    repeat(t) {
        var st = java.util.StringTokenizer(br.readLine())
        val n = st.nextToken().toInt()
        val s = st.nextToken().toLong()
        val x = st.nextToken().toLong()
        st = java.util.StringTokenizer(br.readLine())
        val arr = LongArray(n) { st.nextToken().toLong() }
        sb.appendLine(countSubsegments(arr, n, s, x) - countSubsegments(arr, n, s, x - 1))
    }
    print(sb)

}
