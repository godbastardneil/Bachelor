//let mysql = require('mysql');
let pg = require('pg');
const util = require('util');

String.prototype.replaceAll = function(search, replace) {
    return this.split(search).join(replace);
}

module.exports = class database_lab {

    constructor() {

        this.client = new pg.Pool({
            host: 'localhost',
            user: 'lab_work',
            password: 'postgres1!',
            database: 'training_base',
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

    //lab
    async get_first_lab_table() {
        try {
            const results = await this.query(`select * from get_first_lab_table();`);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_first_lab_table' exception: ${error}`);
        }
    }
    async get_lab_table() {
        try {
            const results = await this.query(`select * from user_table order by col_1;`);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_lab_table' exception: ${error}`);
        }
    }
    async get_lab_query() {
        try {
            const results = await this.query(`select * from get_lab_query();`);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_lab_query' exception: ${error}`);
        }
    }
    async check_query(que, r_que) {
        try {
            const results = await this.query(`select * from check_query('${que}'::text, '${r_que}'::text)`);
            if (!results.rows[0]['check_query']) {
                console.log(`refrash_table`);
                await this.query(`call refrash_table();`);
            }
            return results.rows[0]['check_query'];
        } catch (error) {
            console.error(`BD-'check_query' exception: ${error}`);
            return false;
        }
    }
    async do_right_query(r_que) {
        try {
            const results = await this.query(`call do_right_query('${r_que}'::text)`);
            return false;
        } catch (error) {
            console.error(`BD-'check_query' exception: ${error}`);
            return false;
        }
    }

    async init_lab_stat(userlog, rat, anss) {
        try {
            await this.query(`call init_lab_stat('${userlog}', '{${rat}}'::boolean[], '{${anss}}'::text[])`);
        } catch (error) {
            console.error(`BD-'init_lab_stat' exception: ${error}`);
        }
    }
};