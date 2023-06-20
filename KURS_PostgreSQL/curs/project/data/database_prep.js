let pg = require('pg');
const util = require('util');

String.prototype.replaceAll = function(search, replace) {
    return this.split(search).join(replace);
}

module.exports = class database_prep {

    constructor() {
        this.client = new pg.Client({
            host: 'localhost',
            user: 'ses_prep',
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
                console.error(`database_prep: connection error: ${err.stack}`);
            } else {
                console.log(`database_prep: successful connection for id ${this.threadId}`);
            }
        });
    };

    // получения списка оценок
    async get_rating() {
        try {
            const results = await this.query(`select * from оценка`);
            return results.rows;
        } catch (error) {
            console.error(`database_prep-'get_rating' exception: ${error}`);
        }
    }

    async get_plan_stud(id_plan) {
        try {
            const results = await this.query(`select * from get_plan_stud($1::integer);`, [id_plan]);

            return results.rows;
        } catch (error) {
            console.error(`database_prep-'get_plan_stud' exception: ${error}`);
        }
    }
    async get_teacher_plan(user_id) {
        try {
            const results = await this.query(`select * from get_teacher_plan($1::integer);`, [user_id]);

            return results.rows;
        } catch (error) {
            console.error(`database_prep-'get_teacher_plan' exception: ${error}`);
        }
    }

    async save_change_exam(id, id_plan, id_rat) {
        try {
            const results = await this.query(`select save_change_exam($1::integer, $2::integer, $3::integer);`, [id, id_plan, id_rat]);

            return results.rows[0];
        } catch (error) {
            console.error(`database_prep-'save_change_exam' exception: ${error}`);
            throw error;
        }
    }
};