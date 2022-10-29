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



    socket.on('get_product_for_deal', (userlog) => {
        dbHandle.select_product_for_deal(userlog).then(values => {
            values.forEach(el =>
                socket.emit('addProduct', el));
        });
    });
    socket.on('get_customer_for_deal', (userlog) => {
        dbHandle.select_customer_for_deal(userlog).then(values => {
            values.forEach(el =>
                socket.emit('addCustomer', el));
        });
    });
    socket.on('get_deals', () => {
        dbHandle.select_deal().then(values => {
            values.forEach(el =>
                socket.emit('addDeal', el));
        });
    });

    socket.on('up_deal', (id, date, idc, idp, kol, i) => {

        dbHandle.update_deal(id, date, idc, idp, kol, i);
    });

    socket.on('init_deal', (date, idc, idp, kol, i) => {

        dbHandle.include_deal(date, idc, idp, kol, i);
    });

    socket.on('del_deal', (id) => {

        dbHandle.delete_deal(id);
    });





    socket.on('get_products_by_title', (tit) => {
        dbHandle.select_products_by_title(tit).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });
    socket.on('get_products_by_opt', (opt) => {
        dbHandle.select_products_by_opt(opt).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });
    socket.on('get_products_by_roz', (roz) => {
        dbHandle.select_products_by_roz(roz).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });

    socket.on('get_products', () => {
        dbHandle.select_products().then(values => {
            values.forEach(el =>
                socket.emit('addProduct', el));
        });
    });

    socket.on('up_product', (id, t, o, r) => {

        dbHandle.update_product(id, t, o, r);
    });

    socket.on('init_product', (t, o, r) => {

        dbHandle.include_product(t, o, r);
    });

    socket.on('del_product', (id) => {

        dbHandle.delete_product(id);
    });





    socket.on('get_customers_by_name', (name) => {
        dbHandle.select_customers_by_name(name).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });
    socket.on('get_customers_by_phone', (pho) => {
        dbHandle.select_customers_by_phone(pho).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });
    socket.on('get_customers_by_address', (addr) => {
        dbHandle.select_customers_by_address(addr).then(values => {
            values.forEach(el =>
                socket.emit('addSearсh', el));
        });
    });

    socket.on('get_customers', () => {
        dbHandle.select_customers().then(values => {
            values.forEach(el =>
                socket.emit('addCustomers', el));
        });
    });

    socket.on('up_customer', (id, n, p, a) => {

        dbHandle.update_customer(id, n, p, a);
    });

    socket.on('init_customer', (n, p, a) => {

        dbHandle.include_customer(n, p, a);
    });

    socket.on('del_customer', (id) => {

        dbHandle.delete_customer(id);
    });


});



// открываем доступ к статике, т.е к папке public (css, js, картинки)
app.use(express.static("../frontend/public/"));
// страница сделки
app.get('/deal', (req, res) => {
    res.sendFile(path.join(__dirname, '../frontend/pages', 'main.html'));
});
// страница клиентов
app.get('/cust', async (req, res) => {
        res.sendFile(path.join(__dirname, '../frontend/pages', 'cust.html'));
});
// страница клиентов
app.get('/prod', async (req, res) => {
        res.sendFile(path.join(__dirname, '../frontend/pages', 'prod.html'));
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