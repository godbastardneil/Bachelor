

fun main(args: Array<String>) {
    val a = 1..4 // [1, 4] - 1, 2, 3, 4
    val b = 1 until 4 // [1, 4) - 1, 2, 3

    for (i in a) print(i) // 1234
    println()
    for (i in b) print(i) // 123
    println()

    val a1 = "String"

    var b1 = // k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
        if (a1[3] in 'k'..'z') "Yes"
        else a1[3].toString()

    println(b1) // i

    b1 =
        when (a1[3]) {
            in 'k'..'z' -> "Yes"
            else -> a1[3].toString()
        }

    println(b1) // i

    val a2 = 1..3
    val b2 = 1

    println(b2 !in a2) // false




    val a_ = 1..9 step 3
    val b_ = 1 until 10 step 2
    val c_ = 0 downTo -4
    val d_ = 'z' downTo 'a' step 5

    for (i in a_) print(i) // 147
    println()
    for (i in b_) print(i) // 13579
    println()
    for (i in c_) print(" $i") // 0 -1 -2 -3 -4
    println()
    for (i in d_) print(i) // zupkfa
    println()

    val _a = 1..3
    val _b = 1 until 3
    val _c = 3 downTo 1

    println(_a.toList()) // [1, 2, 3]
    println(_b.toList()) // [1, 2]
    println(_c.toList()) // [3, 2, 1]
}