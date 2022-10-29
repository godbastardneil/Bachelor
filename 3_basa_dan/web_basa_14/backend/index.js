// подключаем нужные модули (библиотеки)
const express = require('express');
const app = express();
const http = require('http').Server(app);
const io = require('socket.io')(http, {
    'pingInterval': 10000,
    'pingTimeout': 1000
});
const path = require('path');
const port = 8000;

const db = require('./database.js');

let dbHandle = new db();


// сокеты
io.on('connection', (socket) => {
    console.log(`${socket.id} user connected`);
    socket.on('disconnect', () => {
        console.log(`${socket.id} user disconnected`);
    });



    socket.on('get_zakaz_by_sum', (sum) => {
        dbHandle.select_zakaz_by_sum(sum).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });
    socket.on('get_zakaz_by_date', (d1, d2) => {
        dbHandle.select_zakaz_by_date(d1, d2).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });
    socket.on('get_zakaz_by_agent', (ida) => {
        dbHandle.select_zakaz_by_agent(ida).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });
    socket.on('get_zakaz_by_zakazchik', (idz) => {
        dbHandle.select_zakaz_by_zakazchik(idz).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });



    socket.on('get_agent', () => {
        dbHandle.select_agent().then(values => {
            values.forEach(el =>
                socket.emit('addAgent', el));
        });
    });
    socket.on('get_zakazchic', () => {
        dbHandle.select_zakazchic().then(values => {
            values.forEach(el =>
                socket.emit('addZakazchic', el));
        });
    });
});



// открываем доступ к статике, т.е к папке public (css, js, картинки)
app.use(express.static("../frontend/public/"));
// страница авторизации
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, '../frontend/pages', 'main.html'));
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
});

rl.on('SIGINT', () => {
    process.exit();
});