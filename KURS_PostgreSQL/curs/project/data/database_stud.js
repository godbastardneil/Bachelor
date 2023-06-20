let pg = require('pg');
const util = require('util');

String.prototype.replaceAll = function(search, replace) {
    return this.split(search).join(replace);
}

module.exports = class database_stud {

    constructor() {
        this.client = new pg.Client({
            host: 'localhost',
            user: 'ses_stud',
            password: 'UserUser1!',
            database: 'session',
            port: 5432
        });
        this.set_connection();
        // обертка для connection.query, чтобы можно было использовать query в async-await связках
        this.query = util.promisify(this.client.query).bind(this.client);
    };

    set_connection() {
        this.client.connect(err => {
            if (err) {
                console.error(`database_stud: connection error: ${err.stack}`);
            } else {
                console.log(`database_stud: successful connection for id ${this.threadId}`);
            }
        });
    };


    // получение статистики для главной страницы ученика
    async get_ex_stat(user_id) {
        try {
            const results = await this.query(`select * from get_stud_ex($1::integer);`, [user_id]);

            return results.rows;
        } catch (error) {
            console.error(`database_stud-'get_ex_stat' exception: ${error}`);
        }
    }
};