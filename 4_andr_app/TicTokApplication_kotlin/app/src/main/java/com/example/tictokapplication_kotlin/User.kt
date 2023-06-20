package com.example.tictokapplication_kotlin

class User {
    var id: String? = null
    var firstDate: String = ""
    var lastDate: String = ""

    constructor() {}
    constructor(id: String, Date: String) {
        this.id = id
        this.firstDate = Date
        this.lastDate = Date
    }
}