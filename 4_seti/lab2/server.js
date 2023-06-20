const net = require('net');
const port = 7070;
const host = '127.0.0.1';

const server = net.createServer();

server.listen(port, host, () => {
    console.log('TCP Сервер, порт - ' + port +'.');
});

let sockets = [];
server.on('connection', function(sock) {
    console.log('Соединение: ' + sock.remoteAddress + ':' + sock.remotePort);
    sockets.push(sock);
    sock.on('data', function(data) {
        console.log('Передаваемая информация ' + sock.remoteAddress + ': ' + data);
        
        // отправляем данные назад, ко всем подсоединившимся, клиет получит данные с сервера
        sockets.forEach(function(sock, index, array) {
            sock.write(sock.remoteAddress + ':' + sock.remotePort + " передаёт " + data + '\n');
        });
    });


    // при отключении клиента
    sock.on('close', function(data) {
        let index = sockets.findIndex(function(o) {
            return o.remoteAddress === sock.remoteAddress && o.remotePort === sock.remotePort;
        });
        if (index !== -1) { sockets.splice(index, 1); }
        console.log('Закрыт: ' + sock.remoteAddress + ' ' + sock.remotePort);
    });
});