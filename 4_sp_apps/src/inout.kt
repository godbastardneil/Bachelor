/*
This App get user info then print them
 We did it as part from learning session
*/

fun main(){


    //Ask for user name
    print("Enter Name: ")
    val name = readLine()
    //Ask For Age
    print("Enter Age: ")
    val age:Int? = readLine()?.toInt()
    print("Enter GPA: ")
    val GPA:Double? =  readLine()?.toDouble()

    println("===== User info ===== ")
    println("Your Name: $name")
    println("Your Age: $age"   )
    println("Your GPA: $GPA" )


    val a = 10
    val b = 12
    println("$a + $b = ${a + b}")

    val plus = "$a + $b = ${a + b}"
    val minus = "$a - $b = ${a - b}"
    println(plus)
    println(minus)
    println("$plus and $minus")

    val act = "Go"
    //println("$acting") // ошибка
    println("${act}ing") // вывод: Going
}