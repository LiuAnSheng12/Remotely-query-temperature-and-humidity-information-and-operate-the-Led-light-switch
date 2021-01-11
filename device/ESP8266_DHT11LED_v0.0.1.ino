// Flag's Block 產生的草稿碼

#include <dht11.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

boolean toggle = false;
int lastTime = 0;

dht11 __flagDHT11;
unsigned long __lastDHT11Time = 0;
WiFiClient _MQTTWiFiClient;
PubSubClient _MQTTClient(u8"192.168.100.3", 1883, _MQTTWiFiClient);
String _MQTTTopic;
String _MQTTMsg;


int __getDHT11Temp(int dataPin) {
  if((millis() - __lastDHT11Time <= 150) && __lastDHT11Time > 0)
    return __flagDHT11.temperature;
  if(__flagDHT11.read(dataPin) == DHTLIB_OK) {
    __lastDHT11Time = millis();
    return __flagDHT11.temperature;
  } else
    return -1;
}

int __getDHT11Humi(int dataPin) {
  if((millis() - __lastDHT11Time <= 150) && __lastDHT11Time > 0)
    return __flagDHT11.humidity;
  if(__flagDHT11.read(dataPin) == DHTLIB_OK) {
    __lastDHT11Time = millis();
    return __flagDHT11.humidity;
  } else
    return -1;
}

void _MQTT_Callback(char* topic, byte* payload, unsigned int length) {
  _MQTTTopic = topic;
  _MQTTMsg = "";
  for(int i = 0;i < length;i++) {
    _MQTTMsg += (char) payload[i];
  }
  mqtt();
}

void mqtt() {
  if (_MQTTTopic == u8"sw/device") {
    Serial.println((String(u8"Message:") + String(_MQTTMsg)));
    if (_MQTTMsg == u8"clientCmdOn") {
      digitalWrite(D1, HIGH);
      toggle = true;
      Serial.println(u8"deviceStateOn");
      _MQTTClient.publish(u8"sw/device", String(u8"deviceStateOn").c_str());
    } else if (_MQTTMsg == u8"clientCmdOff") {
      digitalWrite(D1, LOW);
      toggle = false;
      Serial.println(u8"deviceStateOff");
      _MQTTClient.publish(u8"sw/device", String(u8"deviceStateOff").c_str());
    } else if (_MQTTMsg == u8"clientConfirm") {
      if (toggle == true) {
        Serial.println(u8"deviceStateOn");
        _MQTTClient.publish(u8"sw/device", String(u8"deviceStateOn").c_str());
      } else {
        Serial.println(u8"deviceStateOff");
        _MQTTClient.publish(u8"sw/device", String(u8"deviceStateOff").c_str());
      }
    }
  } else if (_MQTTTopic == u8"th/device") {
    if (_MQTTMsg == u8"clientConfirm") {
      Serial.println((String(u8"t") + String(__getDHT11Temp(D3)) + String(u8"h") + String(__getDHT11Humi(D3))));
      _MQTTClient.publish(u8"th/device", String((String(u8"t") + String(__getDHT11Temp(D3)) + String(u8"h") + String(__getDHT11Humi(D3)))).c_str());
    }
  }
}


// setup() 會先被執行且只會執行一次
void setup() {
  Serial.begin(9600);
  pinMode(D1, OUTPUT);

  WiFi.begin(u8"ensan256", u8"935zxc662");
  delay(5000);
  Serial.println((String(u8"IP:") + String((WiFi.localIP().toString()))));
  _MQTTClient.setCallback(_MQTT_Callback);
  digitalWrite(D1, LOW);

}

// loop() 裡面的程式會不斷重複執行
void loop() {
  if (!_MQTTClient.connected()) {
    while (!_MQTTClient.connect(u8"", u8"", u8""));
    Serial.println((String(u8"Connected:") + String(u8"已連上MQTT伺服器")));
    _MQTTClient.subscribe(u8"sw/device");
    _MQTTClient.subscribe(u8"th/device");
  } else {
    _MQTTClient.loop();
    if (millis() - lastTime > 60000) {
      Serial.println((String(u8"t") + String(__getDHT11Temp(D3)) + String(u8"h") + String(__getDHT11Humi(D3))));
      _MQTTClient.publish(u8"th/device", String((String(u8"t") + String(__getDHT11Temp(D3)) + String(u8"h") + String(__getDHT11Humi(D3)))).c_str());
      lastTime = millis();
    }
  }

}
