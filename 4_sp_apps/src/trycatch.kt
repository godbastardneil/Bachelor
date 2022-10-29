fun main() {
    val a = readLine()!!
    var b: Int
    // можно сразу сделать b:Int = try { ...
    // тогда не нужно писать b в трай кетче
    try {
        b = a.toInt() + 10
    } // если была введено не число, то toInt() выбаст ошибку, и она обработается исключением
    catch (e: Exception) {
        println(e)
        b = 10
    }
    println("b = $b")

    val d = readLine()!!
    val f = readLine()!!
    val c: Int

    try {
        c = d.toInt() / f.toInt()
        println(c)
    } // имеет смысл писать опеределенные ошибки перед неопределленной, потому что
        // до определенных не дойдет при обратном порядке, искюченеи сразу залетит в e: Exception
    catch (e: NumberFormatException) {
        println("Надо вводить только числа")
    }
    catch (e: Exception) { // здесь может выйти ошибка java.lang.ArithmeticException: / by zero
                            // если f будет равна 0
        println(e)
    }
    finally { // всегда исполняется вне зависимости от того было исключение или нет
        println("Конец программы")
    } // finally не обязателен, когда есть хотя бы один catch, но если их нет, то он нужен
}