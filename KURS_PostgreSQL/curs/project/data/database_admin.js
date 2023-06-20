let pg = require('pg');
const util = require('util');

String.prototype.replaceAll = function(search, replace) {
    return this.split(search).join(replace);
}

module.exports = class database_admin {

    constructor() {
        this.client = new pg.Client({
            host: 'localhost',
            user: 'ses_admin',
            password: 'admin',
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
                console.error(`database_admin: connection error: ${err.stack}`);
            } else {
                console.log(`database_admin: successful connection for id ${this.threadId}`);
            }
        });
    };


    async check(user, pas) {
        try {
            return (this.client.user == user && this.client.password == pas);
        } catch (error) {
            console.error(`database_admin-'remove_discipline' exception: ${error}`);
            throw error;
        }
    }


    // данные для админа
    async remove_discipline(id) {
        try {
            const results = await this.query(`call remove_discipline($1::integer);`, [id]);

        } catch (error) {
            console.error(`database_admin-'remove_discipline' exception: ${error}`);
            throw error;
        }
    }
    async remove_teacher(id) {
        try {
            const results = await this.query(`call remove_teacher($1::integer);`, [id]);

        } catch (error) {
            console.error(`database_admin-'remove_teacher' exception: ${error}`);
            throw error;
        }
    }
    async remove_group(id) {
        try {
            const results = await this.query(`call remove_group($1::integer);`, [id]);

        } catch (error) {
            console.error(`database_admin-'remove_group' exception: ${error}`);
            throw error;
        }
    }
    async remove_student(id) {
        try {
            const results = await this.query(`select * from remove_student($1::integer);`, [id]);

            return results.rows[0];
        } catch (error) {
            console.error(`database_admin-'remove_student' exception: ${error}`);
            throw error;
        }
    }
    async remove_plan(id) {
        try {
            const results = await this.query(`call remove_plan($1::integer);`, [id]);

        } catch (error) {
            console.error(`database_admin-'remove_plan' exception: ${error}`);
            throw error;
        }
    }
    async change_discipline(id, name, inst, kaf) {
        try {
            const results = await this.query(`select * from change_discipline($1::integer, $2::text, $3::text, $4::text);`, [id, name, inst, kaf]);

            return results.rows[0];
        } catch (error) {
            console.error(`database_admin-'change_discipline' exception: ${error}`);
            throw error;
        }
    }
    async change_teacher(id, new_id, fio, pas, inst, kaf) {
        try {
            const results = await this.query(`select * from change_teacher($1::integer, $2::integer, $3::text, $4::text, $5::text, $6::text);`, [id, new_id, fio, pas, inst, kaf]);

            return results.rows[0];
        } catch (error) {
            console.error(`database_admin-'change_teacher' exception: ${error}`);
            throw error;
        }
    }
    async change_group(id, name, inst, kaf) {
        try {
            const results = await this.query(`select * from change_group($1::integer, $2::text, $3::text, $4::text);`, [id, name, inst, kaf]);

            return results.rows[0];
        } catch (error) {
            console.error(`database_admin-'change_group' exception: ${error}`);
            throw error;
        }
    }
    async change_student(id, new_id, fio, pas, id_gr) {
        try {
            const results = await this.query(`select * from change_student($1::integer, $2::integer, $3::text, $4::text, $5::integer);`, [id, new_id, fio, pas, id_gr]);

            return results.rows[0];
        } catch (error) {
            console.error(`database_admin-'change_student' exception: ${error}`);
            throw error;
        }
    }
    async change_plan(id, id_dis, id_prep, id_gr, date) {
        try {
            const results = await this.query(`select * from change_plan($1::integer, $2::integer, $3::integer, $4::integer, $5::date);`, [id, id_dis, id_prep, id_gr, date]);

            return results.rows[0];
        } catch (error) {
            console.error(`database_admin-'change_plan' exception: ${error}`);
            throw error;
        }
    }

    async get_discipline() {
        try {
            const results = await this.query(`select * from get_discipline()`);

            return results.rows;
        } catch (error) {
            console.error(`database_admin-'get_discipline' exception: ${error}`);
        }
    }
    async get_teacher() {
        try {
            const results = await this.query(`select * from get_teacher()`);

            return results.rows;
        } catch (error) {
            console.error(`database_admin-'get_teacher' exception: ${error}`);
        }
    }
    async get_group() {
        try {
            const results = await this.query(`select * from get_group()`);

            return results.rows;
        } catch (error) {
            console.error(`database_admin-'get_group' exception: ${error}`);
        }
    }
    async get_student() {
        try {
            const results = await this.query(`select * from get_student()`);

            return results.rows;
        } catch (error) {
            console.error(`database_admin-'get_student' exception: ${error}`);
        }
    }
    async get_plan() {
        try {
            const results = await this.query(`select * from get_plan()`);

            return results.rows;
        } catch (error) {
            console.error(`database_admin-'get_plan' exception: ${error}`);
        }
    }
};