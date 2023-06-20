// подключаем нужные модули (библиотеки)
const express = require('express');
const app = express();
const http = require('http').Server(app);
const io = require('socket.io')(http, {
    'pingInterval': 10000,
    'pingTimeout': 1000
});
const path = require('path');
const port = 8800;

const mutex = require('./data/mutex.js');
const dbu = require('./data/database_user.js');
const dbs = require('./data/database_stud.js');
const dbp = require('./data/database_prep.js');
const dba = require('./data/database_admin.js');

let mutex_user = new mutex();
let dbu_Handle = new dbu();
let dbs_Handle = new dbs();
let dbp_Handle = new dbp();
let dba_Handle = new dba();


// сокеты
io.on('connection', (socket) => {
    console.log(`${socket.id} user connected`);
    socket.on('disconnect', () => {
        console.log(`${socket.id} user disconnected`);
        if (mutex_user.is_busy_by_id(socket.id)) {
            mutex_user.delete_by_id(socket.id);
        }
    });
    // сокеты входа в программу
    // сокет порверки занятости логина других пользователем
    socket.on('check_for_init', (user, type) => {
        if (mutex_user.is_busy_by_name(`${type}_${user}`)) {
            console.log(`${user} already in system`);
            socket.emit('user_alreaby_in_system');
        } else {
            console.log(`${socket.id} now is ${user} - ${type}`);
            if (type == 'student') {
                socket.emit('passSuccess_for_student');
            } else if (type == 'teacher') {
                socket.emit('passSuccess_for_teacher');
            } else {
                socket.emit('passSuccess_for_admin');
            }
        }
    });
    // проверка данных на вход в программу (логин и пароль)
    socket.on('check_student', (user, pas) => {

        dbu_Handle.check_student(Number(user), pas).then(value => {
            if (!value) {
                console.log(`value: ${value}`);
                console.log(`${user} don't exist`);
                socket.emit('user_do_not_exist');

            } else { socket.emit('can_to_init'); }
        });
    });
    socket.on('check_teacher', (user, pas) => {

        dbu_Handle.check_teacher(Number(user), pas).then(value => {
            if (!value) {
                console.log(`${user} don't exist`);
                socket.emit('user_do_not_exist');

            } else { socket.emit('can_to_init'); }
        });
    });
    socket.on('check_admin', (user, pas) => {

        dba_Handle.check(user, pas).then(value => {
            if (!value) {
                console.log(`${user} is not admin`);
                socket.emit('user_do_not_exist');

            } else { socket.emit('can_to_init'); }
        });
    });
    // сокет занимает юзера
    socket.on('take_user', (type, user) => {
        mutex_user.add(`${type}_${user}`, socket.id);
    });


    // студент
    socket.on('get_stat', (user_id) => {
        dbs_Handle.get_ex_stat(user_id).then(values => {
            socket.emit('addStat', values);
        });
    });

    // преподаватель
    socket.on('get_rating', () => {
        dbp_Handle.get_rating().then(values => {
            socket.emit('addRaiting', values);
        });
    });

    socket.on('get_plan_stud', (id_plan) => {
        dbp_Handle.get_plan_stud(id_plan).then(values => {
            socket.emit('addStudents', values, id_plan);
        });
    });
    socket.on('get_teacher_plan', (user_id) => {
        dbp_Handle.get_teacher_plan(user_id).then(values => {
            socket.emit('addDisGroups', values);
        });
    });

    socket.on('save_change_exam', (id, id_plan, id_rat) => {
        try {
            dbp_Handle.save_change_exam(id, id_plan, id_rat).then(values => {
                socket.emit('change_rat', id, id_plan, values);
            });
        } catch (error) {
            socket.emit('can_not_do_this', error);
        }
    });

    // админ
    // удаление
    socket.on('remove_discipline', (id) => {
        dba_Handle.remove_discipline(id).then(() =>
            socket.emit('clean_discipline', id)
        ).catch(error => {
            socket.emit('alert_error', error.message);
        });
    });
    socket.on('remove_teacher', (id) => {
        dba_Handle.remove_teacher(id).then(() =>
            socket.emit('clean_teacher', id)
        ).catch(error => {
            socket.emit('alert_error', error.message);
        });
    });
    socket.on('remove_group', (id) => {
        dba_Handle.remove_group(id).then(() =>
            socket.emit('clean_group', id)
        ).catch(error => {
            socket.emit('alert_error', error.message);
        });
    });
    socket.on('remove_student', (id) => {
        dba_Handle.remove_student(id).then(values => {
            socket.emit('clean_student', id, values);
        });
    });
    socket.on('remove_plan', (id) => {
        dba_Handle.remove_plan(id).then(() =>
            socket.emit('clean_plan', id)
        ).catch(error => {
            socket.emit('alert_error', error.message);
        });
    });

    // изменение
    socket.on('change_discipline', (id, name, inst, kaf) => {
        dba_Handle.change_discipline(id, name, inst, kaf).then(values =>
            socket.emit('set_change_discipline', id, values)
        ).catch(error => {
            socket.emit('alert_error', error.message);
        });
    });
    socket.on('change_teacher', (id, new_id, fio, pas, inst, kaf) => {
        dba_Handle.change_teacher(id, new_id, fio, pas, inst, kaf).then(values =>
            socket.emit('set_change_teacher', id, values)
        ).catch(error => {
            socket.emit('alert_error', error.message);
        });
    });
    socket.on('change_group', (id, name, inst, kaf) => {
        dba_Handle.change_group(id, name, inst, kaf).then(values =>
            socket.emit('set_change_group', id, values)
        ).catch(error => {
            socket.emit('alert_error', error.message);
        });
    });
    socket.on('change_student', (id, new_id, fio, pas, id_gr) => {
        dba_Handle.change_student(id, new_id, fio, pas, id_gr).then(values =>
            socket.emit('set_change_student', id, values)
        ).catch(error => {
            socket.emit('alert_error', error.message);
        });
    });
    socket.on('change_plan', (id, id_dis, id_prep, id_gr, date) => {
        dba_Handle.change_plan(id, id_dis, id_prep, id_gr, date).then(values =>
            socket.emit('set_change_plan', id, values)
        ).catch(error => {
            socket.emit('alert_error', error.message);
        });
    });

    // получение информации
    socket.on('get_discipline', () => {
        dba_Handle.get_discipline().then(values => {
            socket.emit('set_discipline', values);
        });
    });
    socket.on('get_teacher', () => {
        dba_Handle.get_teacher().then(values => {
            socket.emit('set_teacher', values);
        });
    });
    socket.on('get_group', () => {
        dba_Handle.get_group().then(values => {
            socket.emit('set_group', values);
        });
    });
    socket.on('get_student', () => {
        dba_Handle.get_student().then(values => {
            socket.emit('set_student', values);
        });
    });
    socket.on('get_plan', () => {
        dba_Handle.get_plan().then(values => {
            socket.emit('set_plan', values);
        });
    });
});




app.use(express.static("./frontend/public"));
// страница авторизации
app.get('/init', (req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'init.html'));
});
// страница статистики ученика
app.get('/student/:log', async(req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'student.html'));
});
// 
app.get('/teacher/:log', async(req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'teacher.html'));
});
// 
app.get('/admin/:log', async(req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'admin.html'));
});


http.listen(port, () => {
    console.log(`Server running on port: ${port}`);
});




// для ввода в консоль сервера
const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.on('line', (input_str) => {
    let i = input_str.search(":");
    let command = input_str.substr(0, i);
    let arg = input_str.substr(i + 2);
    if (command == "newRow") {
        let s = arg.split(',');
        io.emit(command, {
            orderID: s[0],
            orderName: s[1]
        });
    }
    if (command = "reset") mutex_user.reset()
    else {
        console.log("Wrong input");
    }
});

rl.on('SIGINT', () => {
    process.exit();
});