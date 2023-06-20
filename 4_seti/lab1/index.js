const https = require('https');
const dns = require('dns');
const fs = require("fs");
const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});


var url;
readline.question("INIT URL: ", (url) => {

    https.get(url, (res)=>{
        console.log('https - STATUS: ' + res.statusCode);
        console.log('https - HEADERS: ' + JSON.stringify(res.headers));
    }).on('error', (err) => {
        console.log('https - ERROR: ' + err.message);
    });

    dns.lookup(url.split('/')[2], (err, address, family) => {
        if (err) { console.log(err.stack); throw err; }
        console.log('dns - ADDRESS: ' + address);
        console.log('dns - FAMILY: ' + family);
        dns.reverse(address, (err, hostnames) => {
            if (err) { console.log('dns - ERROR: ' + err.stack); }
            console.log('dns - HOST: ' +  JSON.stringify(hostnames));
        });
    });


    fs.readFile("txt.txt", "utf8", (err, data) => {
        if (err) { console.log(err.stack); throw err; }
        console.log("file - TEXT: " + data);
    });


    readline.close();
});