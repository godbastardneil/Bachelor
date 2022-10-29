


fun main(args: Array<String>) {
    val a = listOf("one", "two", 3)
    val b = listOf(1.2, 4.5, 3.2, 1.8)
    val c: List<Double> // список только из вещественных, можно Any - для списка из переменных любых типов
    c = b + listOf(4.3, 2.5)
    println(a)
    println(b)
    println(c)

    // ни a, b, c не будут изменяться, потому что они все List<Double>
    // а d, e - будут изменяться, потому что они MutableList<Double>
    val d = mutableListOf(1.2, 4.5, 3.2, 1.8) // "mutable" --- изменяемый
    println(d[0])
    d[0] = 10.0
    println(d[0])
    for (i in d.indices) {
        d[i] += 0.3
    }
    println(d)


    val e = mutableListOf(1.2, 4.5, 3.2, 1.8)
    println(e.size)
    e.add(10.0) // засунуть в конец
    e.add(0, 12.5) // засунуть первым, потому что индекс - 0
    e.addAll(e.size / 2, listOf(-3.4, -8.9) ) // засунуть в центр, потому что e.size / 2
    println(e.size)
    for (i in e) {
        print("$i ")
    }
    print('\n')


    val am = mapOf(1 to "one",
        2 to "two", 3 to "three")
    val bm: Map<String, Int>

    bm = mapOf("apple" to 10, "banana" to 5)

    for (i in am) println(i)
    println(bm)

    println(am[1]) // вывод: one
    println(bm["banana"]) // вывод: 5

    val k = am.keys
    val v = am.values
    val ame = am.entries // Set<Map.Entry<Int, String>>

    println(k)
    println(v)
    println(ame)

    for ((i, j) in ame)
        println("The $i is $j!")

    println(am.containsKey(4))
    println(am.containsKey(2))
    println(am.containsValue("five"))
    println(am.containsValue("one"))

    if (1 in am)
        println("Yes")
    else
        println("No")

    for (i in am) println(i)

    // c am ничего бы не сработало, потому что он val и просто mapOf
    // а num - val, но из mutableMapOf
    val num = mutableMapOf( 1 to "one", 2 to "two", 3 to "three")
    num[1] = "first"
    num[4] = "four"
    num[5] = "five"
    num.remove(2)
    println(num)

    val itList = listOf(9, 5, 3)
    val it = itList.iterator()
    println(it)

    val s = setOf(3, 4, 5, 0)
    println(s)
}