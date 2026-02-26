fun lowerBound(arr: LongArray, target: Long): Int {
    var l = 0
    var r = arr.size
    while (l < r) {
        val mid = (l + r) / 2
        if (arr[mid] < target) {
            l = mid + 1
        } else {
            r = mid
        }
    }
    return l
}

fun main() {
    val t = readln().toInt()
    repeat(t) {
        val parts = readln().split(" ")
        val n = parts[0].toInt()
        val k = parts[1].toInt()

        val aInput = readln().split(" ")
        val bInput = readln().split(" ")

        val a = LongArray(n)
        val b = LongArray(n)

        for (i in 0 until n) {
            a[i] = aInput[i].toLong()
            b[i] = bInput[i].toLong()
        }

        a.sort()
        b.sort()

        val prices = LongArray(2 * n)
        for (i in 0 until n) {
            prices[i] = a[i]
            prices[i + n] = b[i]
        }
        prices.sort()

        var ans = 0L
        for (i in prices.indices) {
            val p = prices[i]

            val buyers = n - lowerBound(b, p)
            if (buyers == 0) continue

            val positives = n - lowerBound(a, p)
            val negatives = buyers - positives

            if (negatives <= k) {
                val revenue = p * buyers
                if (revenue > ans) {
                    ans = revenue
                }
            }
        }
        println(ans)
    }
}