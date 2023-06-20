const net = require('net');

const client = new net.Socket();

const port = 7070;
const host = '127.0.0.1';

client.connect(port, host, function() {
	console.log('Connected');
	client.write("Привет от Клиента " + client.address().address);
});

client.on('data', function(data) {
	console.log('Сервер передаёт : ' + data);
});

client.on('close', function() {
	console.log('Соединение разорвано');
});