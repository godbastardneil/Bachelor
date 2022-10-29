import kotlin.random.Random

fun main() {
    val s: String = "number: "
    val i: Int = Random.nextInt(1,10)
    var f: Double

    val v = if (i > 5)
        f = i * 1.5
    else
        f = i * 2.0

    println(s + i)
    println(f)
    println(v) // вывеет специальную переменную пустышку для функций и всего прочего

    f = if (i > 5)
        i * 1.5
    else
        i * 2.0
    println(f) // выведет i*1.5 или i*2.0


    val a = Random.nextInt(-2, 3)

    // по сути switch в c++, в котором не надо писать break
    when {
        a > 0 -> println("+")
        a < 0 -> println("-")
        else -> println("0")
    }
    // когда равенство чему то можно вообще сократить прямо как в switch
    when (a) {
        -2 -> {
            println("+")
        }
        2 -> {
            println("-")
        }
        else -> println("Error")
    }


    val n = Random.nextInt(100)
    val point: Int
    /* можно сразу приравнять это к point и после знаков -> просто цифры */
    when (n) {
        in 0..30, in 71..100 -> point = 1
        in 31..47, in 52..70 -> point = 2
        48, 49, 50, 51, 52 -> point = 4
        else -> point = 0
    }
    println(point)

    when {
        n < 10 || n > 90 -> println("Bad")
        n in 51..59 -> println("Excellent")
        else -> println("Good")
    }
}