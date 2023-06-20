let mysql = require('mysql');
const util = require('util');

String.prototype.replaceAll = function (search, replace) {
    return this.split(search).join(replace);
}

module.exports = class database {

    constructor() {
        // конфигурация подключения к базе данных
        this.config = {
            host: 'localhost',
            user: 'user',
            password: 'UserUser1!',
            database: 'database_lab_11',
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



    async select_deal_by_date(date)
    {
        try {
            const results = await this.query(`call select_deal_by_date('${date}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_deal' exception: ${error}`);
        }
    }
    async select_deal_by_fio(fio)
    {
        try {
            const results = await this.query(`call select_deal_by_fio('${fio}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_deal_by_fio' exception: ${error}`);
        }
    }
    async select_deal_by_title(tit)
    {
        try {
            const results = await this.query(`call select_deal_by_title('${tit}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_deal_by_title' exception: ${error}`);
        }
    }



    async select_product(log)
    {
        try {
            const results = await this.query(`call select_product()`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_product' exception: ${error}`);
        }
    }
    async select_customer(log)
    {
        try {
            const results = await this.query(`call select_customer()`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_customer' exception: ${error}`);
        }
    }
    async select_deal(log)
    {
        try {
            const results = await this.query(`call select_deal()`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_deal' exception: ${error}`);
        }
    }


    async update_deal(id, date, idc, idp, kol)
    {
        try {
            await this.query(`call update_deal('${id}', '${date}', '${idc}', '${idp}', '${kol}')`);

        } catch (error) {
            console.error(`BD-'update_deal' exception: ${error}`);
        }

    }

    async include_deal(date, idc, idp, kol)
    {
        try {
            await this.query(`call include_deal('${date}', '${idc}', '${idp}', '${kol}')`);

        } catch (error) {
            console.error(`BD-'include_deal' exception: ${error}`);
        }

    }

    async delete_deal(id)
    {
        try {
            await this.query(`call delete_deal('${id}')`);

        } catch (error) {
            console.error(`BD-'delete_deal' exception: ${error}`);
        }

    }
};


