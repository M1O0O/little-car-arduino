const express = require('express'),
    bodyParser = require('body-parser'),
    gpiop = require('rpi-gpio').promise,
    path = require('path'),
    app = express();

app.use(bodyParser.json());

gpiop.setup(3, gpiop.DIR_OUT);
gpiop.setup(5, gpiop.DIR_OUT);
gpiop.setup(7, gpiop.DIR_OUT);
gpiop.setup(11, gpiop.DIR_OUT);

app.get('/', function (req, res) {
    res.sendFile(path.join(__dirname + '/index.html'));
}).post('/actions', function (req, res) {
    var keyPressed = req.body.pressed,
        speed = req.body.speed;

    console.log(keyPressed)

    if (keyPressed.includes(38) && keyPressed.includes(37)) { // Avancer gauche
        arduinoSerialPort.write("a");
        arduinoSerialPort.write(`${speed}`);
        return res.send(true);
    } else if (keyPressed.includes(38) && keyPressed.includes(39)) { // Avancer droite
        arduinoSerialPort.write("e");
        arduinoSerialPort.write(`${speed}`);
        return res.send(true);
    } else if (keyPressed.includes(38)) arduinoSerialPort.write("z"); // Avancer
    else if (keyPressed.includes(40)) arduinoSerialPort.write("s"); // Reculer
    else if (keyPressed.includes(37)) arduinoSerialPort.write("q"); // Gauche
    else if (keyPressed.includes(39)) arduinoSerialPort.write("d"); // Droite
    else arduinoSerialPort.write("$");

    arduinoSerialPort.write(`${speed}`);
    return res.send(true);
});

var SerialPort = require("serialport"),
    arduinoSerialPort = null;

(async function () {
    await SerialPort.list().then(ports => {
        ports.forEach(port => {
            if (port.manufacturer && port.manufacturer.includes('arduino')) {
                console.log(port.path)
                arduinoSerialPort = new SerialPort(port.path, {
                    baudRate: 9600
                });
            } else arduinoSerialPort = undefined;
        });
    });

    if (arduinoSerialPort == undefined) return;

    await arduinoSerialPort.on('open', function () {
        console.log('Serial Port is opened.');
        app.listen(80, function () {
            console.log('[WebServer] started !');
        });
    });
})()