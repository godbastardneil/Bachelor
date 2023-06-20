


fun main(args: Array<String>) {
    var a: Array<Int> = arrayOf(1, 10, -3)
    val b: Array<String> = arrayOf("Hi", "Hello")
    val d: Array<Int> = arrayOf(4, 5, 6, 7);

    // a = b // ошибка
    a = d // все OK
    val s: Int = a.size

    println(a[0])
    println(s)

    val c: Array<Int?> = arrayOfNulls(5)
    println(c[2])

    val e: Array<Int> = Array(5) { 0 }
    for (i in e) print(i)

    // содержащих элементы примитивных типов – BooleanArray, ByteArray,
            // ShortArray, IntArray, LongArray, CharArray, FloatArray, DoubleArray.
    // Они несколько упрощают создание массивов. Обратим внимание, нет StringArray

    val bit: ByteArray = byteArrayOf(1, 0, 0)
    for (i in bit) println(i)

    // Для числовых типов также есть варианты беззнаковых массивов
                // – UByteArray, UShortArray, UIntArray, ULongArray

    val boo: BooleanArray = booleanArrayOf(
        true, false, false)
    val int: IntArray = intArrayOf(
        5, 3, 1, 2)
    println(true in boo) // true
    println(5 !in int) // false

    // матрицы
    val mat: Array<IntArray> = Array(3) {
        IntArray(4) {0} }
    val n = mat.size // количество строк
    val m = mat[0].size // количество элементов в строке
    for (i in 0 until n) {
        for (j in 0 until m) {
            mat[i][j] = (Math.random() * 10)
                .toInt()
            print(" ${mat[i][j]}")
        }
        println()
    }
    println()

    mat[0] = intArrayOf(1, 2, 3, 4)
    mat[1] = intArrayOf(5, 6, 7, 8)
    for (i in mat) {
        for (j in i) {
            print(" $j")
        }
        println()
    }
}