import java.lang.Math.sqrt


fun main(args: Array<String>) {
    var n = 1

    while (n <= 10) {
        print(n)
        print(" ")
        n += 1
    }

    var s: String?

    do {
        s = readLine()
    } while (s != "Hello")

    println("$s World!")


    var i = 0
    while (i < 5) {
        val n = readLine()!!.toDouble()
        if (n < 0)
            continue // не вычисляем корень, если введенное число отрицательное, и переходим сразу на while, без i++
        println(kotlin.math.sqrt(n))
        i++
    }

    val a = arrayOf(2, -4, 10, 7, 4)

    for (i in a)
        print(i)

    val si = a.size - 1
    for (i in 0..si) {
        a[i] /= 2
        print("${a[i]} ")
    }

    val indices = a.indices // диапазн как выше - 0..si, a.indices можно сразу в цикл засунуть
    for (i in indices) {
        a[i] /= 2
        println(a[i])
    }

    val str = readLine()!!
    for (char in str)
        print("$char ")
    println()
    /*for (char in s.indices.reversed().toString()) { // reversed() - переворачиваем диапазон тем самым выводим буквы в обратном порядке
        print("$char ")
    }
    println()*/ // хз как это все работает
    /*
        если не хочется так писать, а хочется так - 0..5,
        то если перевернутый надо писать - 5 downTo 0
    */
    val c = listOf(3, 5, 7)
    c.forEach { print(it) }
    println()
    repeat(3) {
        print(c[it])
    }
    println()
}