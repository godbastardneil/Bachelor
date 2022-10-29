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
            database: 'database_lab_12',
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



    async select_product_for_deal(log)
    {
        try {
            const results = await this.query(`call select_product_for_deal()`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_product_for_deal' exception: ${error}`);
        }
    }
    async select_customer_for_deal(log)
    {
        try {
            const results = await this.query(`call select_customer_for_deal()`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_customer_for_deal' exception: ${error}`);
        }
    }
    async select_deal()
    {
        try {
            const results = await this.query(`call select_deal()`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_deal' exception: ${error}`);
        }
    }


    async update_deal(id, date, idc, idp, kol, i)
    {
        try {
            await this.query(`call update_deal('${id}', '${date}', '${idc}', '${idp}', '${kol}', '${i}')`);
        } catch (error) {
            console.error(`BD-'update_deal' exception: ${error}`);
        }

    }

    async include_deal(date, idc, idp, kol, i)
    {
        try {
            await this.query(`call include_deal('${date}', '${idc}', '${idp}', '${kol}', '${i}')`);

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





    async select_products_by_title(tit)
    {
        try {
            const results = await this.query(`call select_products_by_title('${tit}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_products_by_title' exception: ${error}`);
        }
    }
    async select_products_by_opt(opt)
    {
        try {
            const results = await this.query(`call select_products_by_opt_price('${opt}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_products_by_opt' exception: ${error}`);
        }
    }
    async select_products_by_roz(roz)
    {
        try {
            const results = await this.query(`call select_products_by_roz_price('${roz}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_products_by_roz' exception: ${error}`);
        }
    }
    async select_products()
    {
        try {
            const results = await this.query(`call select_products()`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_products' exception: ${error}`);
        }
    }

    async update_product(id, t, o, r)
    {
        try {
            await this.query(`call update_product('${id}', '${t}', '${o}', '${r}')`);
        } catch (error) {
            console.error(`BD-'update_product' exception: ${error}`);
        }

    }

    async include_product(t, o, r)
    {
        try {
            await this.query(`call include_product('${t}', '${o}', '${r}')`);

        } catch (error) {
            console.error(`BD-'include_product' exception: ${error}`);
        }

    }

    async delete_product(id)
    {
        try {
            await this.query(`call delete_product('${id}')`);

        } catch (error) {
            console.error(`BD-'delete_product' exception: ${error}`);
        }

    }





    async select_customers_by_name(name)
    {
        try {
            const results = await this.query(`call select_customers_by_name('${name}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_customers_by_name' exception: ${error}`);
        }
    }
    async select_customers_by_phone(pho)
    {
        try {
            const results = await this.query(`call select_customers_by_phone('${pho}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_customers_by_phone' exception: ${error}`);
        }
    }
    async select_customers_by_address(addr)
    {
        try {
            const results = await this.query(`call select_customers_by_address('${addr}')`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_customers_by_address' exception: ${error}`);
        }
    }
    async select_customers()
    {
        try {
            const results = await this.query(`call select_customers()`);
            return results[0];
        } catch (error) {
            console.error(`BD-'select_customers' exception: ${error}`);
        }
    }

    async update_customer(id, n, p, a)
    {
        try {
            await this.query(`call update_customer('${id}', '${n}', '${p}', '${a}')`);
        } catch (error) {
            console.error(`BD-'update_customer' exception: ${error}`);
        }

    }

    async include_customer(n, p, a)
    {
        try {
            await this.query(`call include_customer('${n}', '${p}', '${a}')`);

        } catch (error) {
            console.error(`BD-'include_customer' exception: ${error}`);
        }

    }

    async delete_customer(id)
    {
        try {
            await this.query(`call delete_customer('${id}')`);

        } catch (error) {
            console.error(`BD-'delete_customer' exception: ${error}`);
        }

    }


};


