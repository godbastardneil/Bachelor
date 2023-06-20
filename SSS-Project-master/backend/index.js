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

const mutex = require('./mutex.js');
const db = require('./database.js');
let mutexHandle = new mutex();
let dbHandle = new db();

// сокеты
io.on('connection', (socket) => {
    console.log(`${socket.id} user connected`);
    socket.on('disconnect', () => {
        console.log(`${socket.id} user disconnected`);
        if (mutexHandle.isBusyBySocketID(socket.id)) {
            mutexHandle.deleteOrderBySocketID(socket.id);
        }
    });
    // получаем все заявки и добавляем их через событие addRow
    socket.on('getStartRows', (date) => {
        dbHandle.getOrderList(date).then(values => {
            values.forEach(element =>
                socket.emit('addRow', {
                    Статус: element['Статус'],
                    ID: element['№ заявки'],
                    Места: element['Место работы'],
                    Описание: element['Описание работ'],
                    Время: element['Время подачи'],
                    Приоритет: element['Приоритет'],
                    Цех: element['Цех']
                }));
        });
    });
    // перед переходом на заявку (при нажатии на строку) проверяем, не занято ли
    socket.on('passToOrder', (ID) => {
        if (!mutexHandle.isBusyByOrderID(ID)) {
            socket.emit('passSuccess', ({
                "ID": ID,
                "successBool": true
            }));
        } else {
            socket.emit('passSuccess', ({
                "ID": ID,
                "successBool": false
            }));
        }
    });
    // клиент занимает страницу с заявкой
    socket.on('takeOrderMutex', (ID) => {
        mutexHandle.addOrder(ID, socket.id);
    });
    // получить всю информацию по заявке для второй страницы
    socket.on('getOrderInfo', (ID) => {
        let orderStatus;
        // отправляем информацию - заголовок заявки
        dbHandle.getOrderHeaderInfo(ID).then(orderHeaderInfo => {
            orderStatus = orderHeaderInfo['Статус'];

            socket.emit('setOrderHeaderInfo', {
                Статус: orderHeaderInfo['Статус'],
                ID: orderHeaderInfo['ID'],
                Места: orderHeaderInfo['Место работы'],
                Цех: orderHeaderInfo['Цех'],
                ВремяДата: orderHeaderInfo['Время и дата выполнения'],
                Ответственный: orderHeaderInfo['Ответственный'],
                Описание: orderHeaderInfo['Описание работы']
            });

            if (orderStatus == "Новый") {
                // инфа по длительности операций (общая, все подзадачи) для конкретной очередности вирт. техники
                dbHandle.getOrderStartEndDurationOfApp(ID).then(values => {
                    socket.emit('setOrderStartEndDuration', values);
                })
                // отправляем информацию - виртуальная техника с таймлайном
                dbHandle.getVirtVehiclesInfo(ID).then(virtVehiclesInfo => {
                    virtVehiclesInfo.forEach((virtVehicle, index) => {
                        socket.emit('setVirtVehicleInfo', {
                            index,
                            virtVehicle
                        });
                        dbHandle.getRealCarList(ID, virtVehicle['ID_КлассТехники'], index + 1).then(realVehicles => {
                            socket.emit('setRealVehiclesInfo', {
                                index,
                                realVehicles
                            });
                        });
                    });
                });
            } else {
                // отправляем информацию о готовой странице
                dbHandle.getDoneVehiclesInfo(ID).then(doneVehiclesInfo => {
                    doneVehiclesInfo.forEach((doneVehicle, index) => {
                        socket.emit('setDoneVehicleInfo', {
                            index,
                            doneVehicle
                        });
                    });
                });
            }
        });
    });

    socket.on('getFreeDriverList', (ID, ord) => {
        dbHandle.getFreeDriversList(ID, ord).then(values => {
            socket.emit('setAppOrderFreeDrivers', {
                ord,
                values
            });
        })
    });

    socket.on('updateRow', (orderID, result) => {
        dbHandle.updateRow(orderID,result);
    });
});

// открываем доступ к статике, т.е к папке public (css, js, картинки)
app.use(express.static("../frontend/public/"));
// главная страница
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, '../frontend/pages', 'main_page.html'));
});
// обработка перехода на вторую страницу
app.get('/order/:id', async (req, res) => {
    // берем ID из адресной строки
    let ID = req.params.id;
    // проверяем, существует ли заявка с таким ID
    let orderExist = await dbHandle.isOrderExist(ID);
    // если заявка существует и не занят мьютекс, то переходим на вторую страницу
    if (orderExist && !mutexHandle.isBusyByOrderID(ID)) {
        res.sendFile(path.join(__dirname, '../frontend/pages', 'second_page.html'));
    } else // иначе перенаправляем на главную и выдаем ошибку (путем добавления в конец адреса ?error + ID заявки)
    {
        res.redirect(`/?error?${ID}`);
    }
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
    if (command = "reset") mutexHandle.testReset()
    else {
        console.log("Wrong input");
    }
});

rl.on('SIGINT', () => {
    process.exit();
});