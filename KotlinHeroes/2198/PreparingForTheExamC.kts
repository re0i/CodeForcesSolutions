fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val (n, m, k) = readln().split(" ").map { it.toInt() }
        val a = readln().split(" ").map { it.toInt() }
        val q = readln().split(" ").map { it.toInt() }.toSet()

        val unknown = n - k
        when {
            unknown >= 2 -> println("0".repeat(m))
            unknown == 0 -> println("1".repeat(m))
            else -> {
                val unknown = (1..n).first { it !in q }
                println(a.joinToString("") {
                    if (it == unknown) "1" else "0"
                })
            }
        }
    }
}