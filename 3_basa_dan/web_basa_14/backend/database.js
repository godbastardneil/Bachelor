let mysql = require('mysql');
const util = require('util');

String.prototype.replaceAll = function (search, replace) {
    return this.split(search).join(replace);
}

module.exports = class database {

    constructor() {

        this.config = {
            host: 'localhost',
            user: 'user',
            password: 'UserUser1!',
            database: 'database_lab_13',
            multipleStatements: true
        }
        this.connection = mysql.createConnection(this.config);
        // обертка для connection.query, чтобы можно было использовать query в async-await связках
        this.query = util.promisify(this.connection.query).bind(this.connection);
        this.setConnection();
    };

    setConnection() {
        this.connection.connect(err => {
            if (err) {
                console.error(`DB: connection error: ${err.stack}`);
            } else {
                console.log(`DB: successful connection for id ${this.connection.threadId}`);
            }
        });
    };



    async select_zakaz_by_sum(date)
    {
        try {
            const results = await this.query(`call select_zakaz_by_sum('${date}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_zakaz_by_sum' exception: ${error}`);
        }
    }
    async select_zakaz_by_date(d1, d2)
    {
        try {
            const results = await this.query(`call select_zakaz_by_date('${d1}', '${d2}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_zakaz_by_date' exception: ${error}`);
        }
    }
    async select_zakaz_by_agent(ida)
    {
        try {
            const results = await this.query(`call select_zakaz_by_agent('${ida}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_zakaz_by_agent' exception: ${error}`);
        }
    }
    async select_zakaz_by_zakazchik(ida)
    {
        try {
            const results = await this.query(`call select_zakaz_by_zakazchik('${ida}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_zakaz_by_zakazchik' exception: ${error}`);
        }
    }



    async select_agent()
    {
        try {
            const results = await this.query(`call SP1()`);
            return results[0];
        } catch (error) {
            console.error(`BD-'SP1' exception: ${error}`);
        }
    }
    async select_zakazchic()
    {
        try {
            const results = await this.query(`call SP2()`);
            return results[0];
        } catch (error) {
            console.error(`BD-'SP2' exception: ${error}`);
        }
    }
};


