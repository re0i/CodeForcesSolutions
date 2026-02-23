fun main() {
    val t = readLine()!!.toInt()

    repeat(t) {
        val arr = readLine()!!.split(" ")
        val a1 = arr[0].toLong()
        val a2 = arr[1].toLong()
        val a4 = arr[2].toLong()
        val a5 = arr[3].toLong()

        val c1 = a1 + a2
        val c2 = a4 - a2
        val c3 = a5 - a4

        var res = 0

        fun count(a3: Long): Int {
            var cnt = 0
            if (a1 + a2 == a3) cnt++
            if (a2 + a3 == a4) cnt++
            if (a3 + a4 == a5) cnt++
            return cnt
        }

        res = maxOf(res, count(c1))
        res = maxOf(res, count(c2))
        res = maxOf(res, count(c3))

        println(res)
    }
}