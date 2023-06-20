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



    socket.on('get_deals_by_date', (date) => {
        dbHandle.select_deal_by_date(date).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });
    socket.on('get_deals_by_fio', (fio) => {
        dbHandle.select_deal_by_fio(fio).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });
    socket.on('get_deals_by_tit', (tit) => {
        dbHandle.select_deal_by_title(tit).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });



    socket.on('get_product', (userlog) => {
        dbHandle.select_product(userlog).then(values => {
            values.forEach(el =>
                socket.emit('addProduct', el));
        });
    });
    socket.on('get_customer', (userlog) => {
        dbHandle.select_customer(userlog).then(values => {
            values.forEach(el =>
                socket.emit('addCustomer', el));
        });
    });
    socket.on('get_deals', (userlog) => {
        dbHandle.select_deal(userlog).then(values => {
            values.forEach(el =>
                socket.emit('addDeal', el));
        });
    });

    socket.on('up_deal', (id, date, idc, idp, kol) => {

        dbHandle.update_deal(id, date, idc, idp, kol);
    });

    socket.on('init_deal', (date, idc, idp, kol) => {

        dbHandle.include_deal(date, idc, idp, kol);
    });

    socket.on('del_deal', (id) => {

        dbHandle.delete_deal(id);
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