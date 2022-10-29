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
const db = require('./data/database.js');
const db_lab = require('./data/database_lab.js');

let mutex_user = new mutex();
let dbHandle = new db();
let dblHandle = new db_lab();


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
    //init
    socket.on('check_for_init', (user, type) => {
        if (mutex_user.is_busy_by_name(`${type}_${user}`)) {
            console.log(`${user} already in system`);
            socket.emit('user_alreaby_in_system');
        } else {
            socket.emit('passSuccess');
        }
    });
    // проверка данных на вход в программу (логин и пароль)
    socket.on('check_user', (log, pas) => {
        dbHandle.check_user(Number(log), pas).then(value => {
            if (!value) {
                console.log(`value: ${value}`);
                console.log(`${log} don't exist`);
                socket.emit('user_do_not_exist');

            } else { socket.emit('can_to_init'); }
        });
    });
    // сокет занимает юзера
    socket.on('take_user', (userlog) => {
        mutex_user.add(userlog, socket.id);
    });



    // сокеты статистики пользователя
    //main
    socket.on('get_kontr_stat', (userlog) => {
        dbHandle.get_kontr_stat(userlog).then(values => {
            socket.emit('addKontr', values);
        });
    });
    socket.on('get_test_stat', (userlog) => {
        dbHandle.get_test_stat(userlog).then(values => {
            socket.emit('addTest', values);
        });
    });
    socket.on('get_lab_stat', (userlog) => {
        dbHandle.get_lab_stat(userlog).then(values => {
            socket.emit('addLab', values);
        });
    });

    //theory
    socket.on('get_kontr', () => {
        dbHandle.get_kontr().then(values => {
            socket.emit('set_kontr', values);
        });
    });
    socket.on('init_kontr_stat', (userlog, anss) => {
        dbHandle.init_kontr_stat(userlog, anss);
    });

    //test
    socket.on('get_test', () => {
        dbHandle.get_test().then(values => {
            socket.emit('set_test', values);
        });
    });
    socket.on('create_test', (userlog) => {
        dbHandle.create_test(userlog).then(value => {
            socket.emit('set_do_test', value);
        });
    });
    socket.on('init_test_stat', (id, id_of_ex, anss) => {
        dbHandle.init_test_stat(id, id_of_ex, anss);
    });

    //lab
    socket.on('get_first_lab_table', () => {
        dblHandle.get_first_lab_table().then(values => {
            socket.emit('set_table', values);
        });
    });
    socket.on('get_lab_table', () => {
        dblHandle.get_lab_table().then(values => {
            socket.emit('set_table', values);
        });
    });
    socket.on('get_lab_query', () => {
        dblHandle.get_lab_query().then(values => {
            socket.emit('set_lab_query', values);
        });
    });
    socket.on('check_query', (que, r_que) => {
        dblHandle.check_query(que, r_que).then(value => {
            socket.emit('set_rat', value);
        });
    });
    socket.on('do_right_query', (r_que) => {
        dblHandle.do_right_query(r_que).then(value => {
            socket.emit('set_rat', value);
        });
    });

    socket.on('init_lab_stat', (userlog, rat, anss) => {
        dblHandle.init_lab_stat(userlog, rat, anss);
    });
});



// открываем доступ к статике, т.е к папке public (css, js, картинки)
app.use(express.static("./frontend/public/"));
// страница авторизации
app.get('/init', (req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'init.html'));
});
// страница статистики ученика
app.get('/apprentice_main/:log', async(req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'apprentice_main.html'));
});
// страница теории
app.get('/apprentice_theory/:log', async(req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'apprentice_theory.html'));
});
// страница создания теста
app.get('/apprentice_lab/:log', async(req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'apprentice_lab.html'));
});
// страница создания теста
app.get('/apprentice_test/:log', async(req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'apprentice_test.html'));
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