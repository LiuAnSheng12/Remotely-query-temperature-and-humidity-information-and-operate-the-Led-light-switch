const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://localhost')

const MongoClient = require('mongodb').MongoClient;
const url = "mongodb://localhost:27017/";

var topics = '';
var msg = '';

client.on('connect', function() {
        client.subscribe('sw/client')
        client.subscribe('sw/device')
        client.subscribe('th/client')
        client.subscribe('th/device')

        MqttPub()
})

client.on('message', function(topic, message) {
        topics = topic;
        msg = message.toString();
        console.log('client.on message %s %s', topics, msg);
        if (topics == 'sw/client') {
                switch (msg) {
                        case 'clientConfirm':
                                topics = 'sw/device';
                                console.log('change message1 %s %s', topics, msg);
                                MqttPub(topics, msg);
                                break
                        case 'clientCmdOn':
                                topics = 'sw/device';
                                console.log('change message2 %s %s', topics, msg);
                                MqttPub(topics, msg);
                                break
                        case 'clientCmdOff':
                                topics = 'sw/device';
                                console.log('change message3 %s %s', topics, msg);
                                MqttPub(topics, msg);
                                break
                }
        } else if (topics == 'sw/device') {
                switch (msg) {
                        case 'deviceStateOn':
                                topics = 'sw/client';
                                console.log('change message4 %s %s', topics, msg);
                                MqttPub(topics, msg);
                                break
                        case 'deviceStateOff':
                                topics = 'sw/client';
                                console.log('change message5 %s %s', topics, msg);
                                MqttPub(topics, msg);
                                break
                }
        } else if (topics == 'th/client') {
				if (msg == 'clientConfirm') {
						topics = 'th/device';
                        console.log('change message6 %s %s', topics, msg);
                        MqttPub(topics, msg);
				}
		} else if (topics == 'th/device') {
                if ( msg.substring(0, 1) == 't' ) {
						//console.log('change message7 %s %s', topics, msg);
						MongoClient.connect(url, function(err, db) {
								if (err) throw err;
								dbo = db.db("iot");
								tt = msg.substr(1, 2);
								hh = msg.substr(4, 2);
								iotth = { temp: tt, humi: hh, when: new Date() };
								dbo.collection("th").insertOne(iotth, function(err, res) {
										if (err) throw err;
										console.log("t=" + tt + "h=" + hh);
								});
						});
						topics = 'th/client';
                        console.log('change message8 %s %s', topics, msg);
                        MqttPub(topics, msg);
				}
        }
})

function MqttPub(topics, msg) {
        console.log('Message Update: %s %s',topics, msg)
        client.publish(topics, msg);
}