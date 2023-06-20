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


    // проверка логина и пароля
    //init
    async check_user(log, pas) {
        try {
            const results = await this.query(`select check_user($1::integer, $2::text);`, [log, pas]);

            return results.rows[0]['check_user'];
        } catch (error) {
            console.error(`database_user-'check_user' exception: ${error}`);
        }
    }


    // получение статистики для главной страницы ученика
    //main
    async get_kontr_stat(log) {
        try {
            const results = await this.query(`select * from get_kontr_stat('${log}')`);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_kontr_stat' exception: ${error}`);
        }
    }
    async get_test_stat(log) {
        try {
            const results = await this.query(`select * from get_test_stat('${log}')`);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_test_stat' exception: ${error}`);
        }
    }
    async get_lab_stat(log) {
        try {
            const results = await this.query(`select * from get_lab_stat('${log}')`);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_lab_stat' exception: ${error}`);
        }
    }

    //theory
    async get_kontr() {
        try {
            const results = await this.query(`select kq."idkontr_quest", kq."question" from "kontr_quest" kq order by kq."idkontr_quest"`);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_kontr' exception: ${error}`);
        }
    }
    async init_kontr_stat(userlog, anss) {
        try {
            await this.query(`call init_kontr_stat('${userlog}', '{${anss}}'::text[])`);
        } catch (error) {
            console.error(`BD-'init_kontr_stat' exception: ${error}`);
        }
    }

    //test
    async get_test() {
        try {
            const results = await this.query(`select te."idtest_ex", te."question", te."variants" from "test_ex" te order by te."idtest_ex"`);
            return results.rows;
        } catch (error) {
            console.error(`BD-'get_test' exception: ${error}`);
        }
    }
    async create_test(userlog) {
        try {
            const results = await this.query(`select * from create_test('${userlog}')`);
            return results.rows[0]['create_test'];
        } catch (error) {
            console.error(`BD-'create_test' exception: ${error}`);
        }
    }
    async init_test_stat(id, id_of_ex, anss) {
        try {
            await this.query(`call init_test_stat('${id}'::integer, '${id_of_ex}'::integer, '{${anss}}'::integer[])`);
        } catch (error) {
            console.error(`BD-'init_test_stat' exception: ${error}`);
        }
    }
};