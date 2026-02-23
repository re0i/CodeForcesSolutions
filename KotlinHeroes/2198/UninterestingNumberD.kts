fun main() {
    val t = readln().toInt()
    repeat(t) {
        val n = readln()
        val dig = n.map { it.digitToInt() }

        val sum = dig.sum()
        val count2 = dig.count { it == 2 }
        val count3 = dig.count { it == 3 }

        var possible = false
        for (a in 0..minOf(count2, 8)) {
            for (b in 0..minOf(count3, 8)) {
                val total = sum + 2 * a + 6 * b
                if (total % 9 == 0) {
                    possible = true
                    break
                }
            }
            if (possible) break
        }
        println(if (possible) "Yes" else "No")
    }

}
