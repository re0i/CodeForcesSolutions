fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val n = readLine()!!.toInt()
        val arr = readLine()!!.split(" ").map { it.toInt() }
        var count = 0
        val used = BooleanArray(n)

        for (i in 0 until n) {
            if (used[i]) continue

            for (j in i + 1 until n) {
                if (!used[j] && arr[i] == arr[j]) {
                    used[i] = true
                    used[j] = true
                    count++
                    break
                }
            }
        }
        println(count)
    }
}