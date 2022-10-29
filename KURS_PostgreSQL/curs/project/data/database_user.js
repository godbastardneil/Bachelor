let pg = require('pg');
const util = require('util');

String.prototype.replaceAll = function(search, replace) {
    return this.split(search).join(replace);
}

module.exports = class database_user {

    constructor() {
        this.client = new pg.Client({
            host: 'localhost',
            user: 'ses_user',
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
                console.error(`database_user: connection error: ${err.stack}`);
            } else {
                console.log(`database_user: successful connection for id ${this.threadId}`);
            }
        });
    };


    // проверка логина и пароля
    async check_student(user, pas) {
        try {
            const results = await this.query(`select check_student($1::integer, $2::text);`, [user, pas]);

            return results.rows[0]['check_student'];
        } catch (error) {
            console.error(`database_user-'check_student' exception: ${error}`);
        }

    }
    async check_teacher(user, pas) {
        try {
            const results = await this.query(`select check_teacher($1::integer, $2::text);`, [user, pas]);

            return results.rows[0]['check_teacher'];
        } catch (error) {
            console.error(`database_user-'check_teacher' exception: ${error}`);
        }
    }
};