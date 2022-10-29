const val N: Int = 10


fun main(args: Array<String>) {
    var str:String
    str="Welcome to Kotlin"

    // val - read only (константа кароче говоря,
    // один раз присваиваем значение и потом не можем поменять
    // Единственное отличие в том, что не обязательно сразу присваивать значение
    //
    // Однако есть и реальные константы const val ... их объявление и определение происходит за пределами функции
    // Потому что код внутри функций выполняется при исполнении программы, а сигнатуры функций и полей должны быть известны на момент компиляции)


    /*НОВОЕ ОБЪЯСНЕНИЕ: val - это не константное значение, а переменная, которой нельзя присвоить новое значние
    * по этому с обычными переменными нельзя ничего сделать, а изменяемые контейнеры можно изменять, потому что
    * контейнер тот же самый, но значение внутри него - это не он, другой контейнер этому не получится приравнять
    * */

    val name = "Nail"
    val age = 21
    val GPA = 3.8

    println("===== User info ===== ")
    println("Name: $name")
    println("Age: $age"   )
    println("GPA: $GPA" )
    println("N: $N" )


    var count = 1
    println("Count: $count")
    count = 10
    println("Count: $count")


    var department:String?
    department = null // так можно делать только благодаря ?
    department = "Software Engineering"
    print("Department ${department!!}")

    val s1: String? = readLine()

    //val lenS1 = s1.length // ошибка
    val lenS1 = s1!!.length // нет ошибки, так как есть !!, который указывает, что это точно не null
    println(lenS1)

    val a = true
    val b = false
    var c: Boolean
    c = a > b
    println(c) // true
    c = a <= b
    println(c) // false

    val s = "Hello"
    val s2: String
    val c1 = 'W'
    val c2: Char
    s2 = s + c1
    c2 = s[0]
    println(s2) // HelloW
    println(c2) // H
}