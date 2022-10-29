import kotlin.random.Random

fun main() {
    val nums: Array<Int> = Array(10) { it+1 } // it - заполняется индексами самого массива
                                                    // +1, увеличивает все значения
    printArray(nums)
    fillArray(nums, 0, 3)
    printArray(nums)
    fillArray(nums, 0, 3)
    printArray(nums)

    var a = 10
    println(a == changeInt(a))
    println(printArray(nums))

    println(avr(1, 2))
    println(abNumber(1, 2))

    val hi = hello() // hi
    println(hi) // kotlin.Unit

    repeatStr1("Hi", 3) // HiHiHi
    println()
    repeatStr1("Hello") // HelloHello
    repeatStr2(3, "Hi") // HiHiHi
    println()
    repeatStr2(s = "Hello") // HelloHello

    println(avr_(0, 1, 8)) // 3.0
    println(avr_(-5, 1)) // -2.0

    val arr: IntArray = intArrayOf(0, 1, 8)
    println(avr_(*arr)) // 3.0
}

fun hello() { println("hi") } // hi
fun avr(n1: Int, n2: Int) = (n1 + n2).toFloat() / 2
fun abNumber(n1: Int, n2: Int) =
                                if (n1 > n2) {
                                    n1 / n2
                                } else { n2 / n1 }

fun avr_(vararg nums: Int): Float { // vararg - произвольное количество аргументов
    val sum = nums.sum()
    val l = nums.size
    return sum.toFloat() / l
}

fun repeatStr1(s: String, n: Int = 2) {
    for(i in 1..n)
        print(s)
}
fun repeatStr2(n: Int = 2, s: String) {
    for(i in 1..n)
        print(s)
}
// все функции что-то возвращают, но если return нету, то функция возвращает Unit
fun changeInt(b: Int): Int { // :Int - возврщаемое значение
    //b += 5 // ошибка, потому что параменты - это val переменные,
                // то есть им неотзя присваивать новое значение
    val i = b+5
    return i
}

fun printArray(a: Array<Int>) {
    for (i in a)
        print(" $i ")
    println()
}

fun fillArray(a: Array<Int>, low: Int, high: Int) {
    for (i in a.indices)
        a[i] = Random.nextInt(low, high)
}