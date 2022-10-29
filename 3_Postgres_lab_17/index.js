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

const db = require('./data/database.js');
let dbHandle = new db();


// сокеты
io.on('connection', (socket) => {
    console.log(`${socket.id} user connected`);
    socket.on('disconnect', () => {
        console.log(`${socket.id} user disconnected`);
    })

    // сокеты статистики пользователя

    socket.on('get_buyers_by_par', (id, tel, kont, adr, opis) => {
        dbHandle.get_buyers_by_par(id, tel, kont, adr, opis).then(values => {
            socket.emit('addBuyers', values);
        });
    });
    socket.on('get_buyers', () => {
        dbHandle.get_buyers().then(values => {
            socket.emit('addBuyers', values);
        });
    });
    socket.on('save_buyer', (id, tel, kont, adr, opis) => {
        dbHandle.save_buyer(id, tel, kont, adr, opis).then(value => {
            socket.emit('set_change_buyer', id, value);
        });
    });
    socket.on('remove_buyer', (id) => {
        dbHandle.remove_buyer(id);
    });


    socket.on('get_products_by_par', (id, name, opt, roz, opis) => {
        dbHandle.get_products_by_par(id, name, opt, roz, opis).then(values => {
            socket.emit('addProducts', values);
        });
    });
    socket.on('get_products', () => {
        dbHandle.get_products().then(values => {
            socket.emit('addProducts', values);
        });
    });
    socket.on('save_product', (id, name, opt, roz, opis) => {
        dbHandle.save_product(id, name, opt, roz, opis).then(value => {
            socket.emit('set_change_product', id, value);
        });
    });
    socket.on('remove_product', (id) => {
        dbHandle.remove_product(id);
    });


    socket.on('get_deals_by_par', (id, date, idpr, kol, idbuy, isopt) => {
        dbHandle.get_deals_by_par(id, date, idpr, kol, idbuy, isopt).then(values => {
            socket.emit('addDeals', values);
        });
    });
    socket.on('get_deals', () => {
        dbHandle.get_deals().then(values => {
            socket.emit('addDeals', values);
        });
    });
    socket.on('save_deal', (id, date, idpr, kol, idbuy, isopt) => {
        dbHandle.save_deal(id, date, idpr, kol, idbuy, isopt).then(value => {
            socket.emit('set_change_deal', id, value);
        });
    });
    socket.on('remove_deal', (id) => {
        dbHandle.remove_deal(id);
    });
});



// открываем доступ к статике, т.е к папке public (css, js, картинки)
app.use(express.static("./frontend/public/"));
// страница авторизации
app.get('/buyer', (req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'buyer.html'));
});
// страница статистики ученика
app.get('/product', async(req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'product.html'));
});
// страница теории
app.get('/deal', async(req, res) => {
    res.sendFile(path.join(__dirname, './frontend/pages', 'deal.html'));
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