var os = require('os');
var net = require('net');


var networkInterfaces = os.networkInterfaces();

//var host = "127.0.0.1"; //networkInterfaces['wlp2s0'][0]['address']; //Local area network to scan (this is rough)
//console.log(host);

function checkConnection(host, port) {
    return new Promise(function(resolve, reject) {
        var timeout = 10000;
        var timer = setTimeout(function() {
            reject("timeout");
            socket.end();
        }, timeout);
        var socket = net.createConnection(port, host, function() {
            clearTimeout(timer);
            resolve(port);
            socket.end();
        });
        socket.on('error', function(err) {
            clearTimeout(timer);
            reject(err);
        });
    });
}

let adr = [];
for(let addresses of Object.values(networkInterfaces)) {
    for(let add of addresses) {
        console.log(add.address);
        adr.push(add.address);
    }
}

for(let a of adr) {
    for (var i=0; i<65536; ++i)
    {
        checkConnection(a, i).then(function(port) {
            // successful
            console.log(a + ' ' + port + ' successful');
        }, function(err) {
            // error
            // console.log(err);
        });
    }
}