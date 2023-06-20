//let mysql = require('mysql');
let pg = require('pg');
const util = require('util');

String.prototype.replaceAll = function(search, replace) {
    return this.split(search).join(replace);
}

module.exports = class database {

    constructor() {

        this.client = new pg.Client({
            host: 'localhost',
            user: 'postgres',
            password: 'postgres1!',
            database: 'lab_17',
            port: 5432
        });
        this.set_connection();
        // обертка для connection.query, чтобы можно было использовать query в async-await связках
        this.query = util.promisify(this.client.query).bind(this.client);
    };

    set_connection() {
        this.client.connect(err => {
            if (err) {
                console.error(`DB: connection error: ${err.stack}`);
            } else {
                console.log(`DB: successful connection for id ${this.threadId}`);
            }
        });
    };


    async get_buyers_by_par(id, tel, kont, adr, opis) {
        try {
            let que = `select * from покупатель`;
            let where = ``;
            if (id) {
                where += `idпокупатель = ${id} and `;
            }
            if (tel) {
                where += `телефон = '${tel}' and `;
            }
            if (kont) {
                where += `конт_лицо = '${kont}' and `;
            }
            if (adr) {
                where += `адрес = '${adr}' and `;
            }
            if (opis) {
                where += `описание = '${opis}' and `;
            }

            if (where) {
                where = where.substr(0, where.lastIndexOf("and"));
                que += ` where ` + where;
            }

            const results = await this.query(que);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_buyers_by_par' exception: ${error}`);
        }
    }
    async get_buyers() {
        try {
            const results = await this.query(`select * from покупатель`);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_buyers' exception: ${error}`);
        }
    }
    async save_buyer(id, tel, kont, adr, opis) {
        try {
            const results = await this.query(`select * from save_buyer(${id}, '${tel}'::character(11), '${kont}'::character(11), '${adr}'::text, '${opis}'::text);`);
            return results.rows[0]['save_buyer'];
        } catch (error) {
            console.error(`BD-'save_buyer' exception: ${error}`);
        }
    }
    async remove_buyer(id) {
        try {
            const results = await this.query(`delete from "покупатель" where "idпокупатель" = ${id};`);
        } catch (error) {
            console.error(`BD-'remove_buyer' exception: ${error}`);
        }
    }


    async get_products_by_par(id, name, opt, roz, opis) {
        try {
            let que = `select * from товар `;
            let where = ``;
            if (id) {
                where += `idтовар = ${id} and`;
            }
            if (name) {
                where += `наименование = '${name}' and `;
            }
            if (opt) {
                where += `опт_цена = ${opt} and `;
            }
            if (roz) {
                where += `роз_цена = ${roz} and `;
            }
            if (opis) {
                where += `описание = '${opis}' and `;
            }

            if (where) {
                where = where.substr(0, where.lastIndexOf("and"));
                que += ` where ` + where;
            }

            const results = await this.query(que);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_products_by_par' exception: ${error}`);
        }
    }
    async get_products() {
        try {
            const results = await this.query(`select * from товар`);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_products' exception: ${error}`);
        }
    }
    async save_product(id, name, opt, roz, opis) {
        try {
            const results = await this.query(`select * from save_product(${id}, '${name}'::character(50), ${opt}, ${roz}, '${opis}'::text);`);
            return results.rows[0]['save_product'];
        } catch (error) {
            console.error(`BD-'save_product' exception: ${error}`);
        }
    }
    async remove_product(id) {
        try {
            const results = await this.query(`delete from "товар" where "idтовар" = ${id};`);
        } catch (error) {
            console.error(`BD-'remove_products' exception: ${error}`);
        }
    }


    async get_deals_by_par(id, date, idpr, kol, idbuy, isopt) {
        try {
            let que = `select idсделка, to_char(дата_сделки, 'yyyy-mm-dd') as дата_сделки, idтовар, кол, idпокупатель, признак_опт_прод from сделка `;
            let where = ``;
            if (id) {
                where += `idсделка = ${id} and `;
            }
            if (date) {
                where += `дата_сделки = '${date}' and `;
            }
            if (idpr) {
                where += `idтовар = ${idpr} and `;
            }
            if (kol) {
                where += `кол = ${kol} and `;
            }
            if (idbuy) {
                where += `idпокупатель = ${idbuy} and `;
            }
                where += `признак_опт_прод = ${isopt}`;

                que += ` where ` + where;

            const results = await this.query(que);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_deals_by_par' exception: ${error}`);
        }
    }
    async get_deals() {
        try {
            const results = await this.query(`select idсделка, to_char(дата_сделки, 'yyyy-mm-dd') as дата_сделки, idтовар, кол, idпокупатель, признак_опт_прод from сделка`);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_deals' exception: ${error}`);
        }
    }
    async save_deal(id, date, idpr, kol, idbuy, isopt) {
        try {
            const results = await this.query(`select * from save_deal(${id}, '${date}'::date, ${idpr}, ${kol}, ${idbuy}, ${isopt}::boolean);`);
            return results.rows[0]['save_deal'];
        } catch (error) {
            console.error(`BD-'save_deals' exception: ${error}`);
        }
    }
    async remove_deal(id) {
        try {
            const results = await this.query(`delete from "сделка" where "idсделка" = ${id};`);
        } catch (error) {
            console.error(`BD-'remove_deal' exception: ${error}`);
        }
    }
};