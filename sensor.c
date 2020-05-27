
/**********************************************
   brantje
   Read temperature, pressure & humidity from BME280
   and send it to MQTT
**********************************************/
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>

#include <ESP8266WiFi.h>
#include <MQTT.h>

Adafruit_BME280 bme;
BH1750 lightMeter;

/**************************
     C O N F I G
 **************************/

const char* ssid = "your-ssid";
const char* password = "wifi-password";
const char* broker = "mqtt-server";
int        port     = 1883;
const char* mqttUser = "mqtt-user";
const char* mqttPass = "mqtt-pass";

const String discoveryPrefix = "homeassistant/";
const String displayName = "Living Room";
String room = "livingroom";

int        sendInterval = 60;
unsigned long lastMillis = 0;

WiFiClient wifi;
MQTTClient mqtt(512);


/**************************
     S E T U P
 **************************/
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);
  // Wait for serial to initialize.
  while (!Serial) { }

  // Set the I2C bus
  Wire.begin(D2, D1);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  if (!lightMeter.begin()) {
    Serial.println("Could not find a valid BH1750 sensor, check wiring!");
  }

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println();

  mqtt.begin("192.168.2.50", wifi);

  Serial.print("Connecting to MQTT broker: ");
  Serial.println(broker);

  while (!mqtt.connect(broker, mqttUser, mqttPass)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("You're connected to the MQTT broker!");
  //sendConfig();
  // Make sure data is send after setup
  lastMillis = millis() - (sendInterval * 1000) - 1;
}

/**************************
   M E T H O D S
**************************/
void sendData() {

  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float humidity = bme.readHumidity();
  float lux = lightMeter.readLightLevel();

  Serial.print("T=");
  Serial.print(temperature);
  Serial.print(" *C");

  Serial.print(" P=");
  Serial.print(pressure);
  Serial.print(" hPa");
  Serial.print(" H=");
  Serial.print(humidity);
  Serial.print("%");
  Serial.print(" A= ");
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");


  String stateTopic = "homeassistant/sensor/" + room + "/state";

  DynamicJsonDocument payloadObj(256);
  payloadObj["temperature"] = (double) temperature;
  payloadObj["humidity"] = (double) roundDescimals(humidity);
  payloadObj["pressure"] = (double) roundDescimals(pressure);
  payloadObj["light"] = (double) roundDescimals(lux);
  String statePayload;
  serializeJsonPretty(payloadObj, statePayload);
  mqtt.publish(stateTopic, statePayload);
  //  String topicTemp = discoveryPrefix + "sensor/" + room + "/temperature";
  //  String topicPressure = discoveryPrefix + "sensor/" + room + "/pressure";
  //  String topicHumidity = discoveryPrefix + "sensor/" + room + "/humidity";
  //  String topicLight = discoveryPrefix + "sensor/" + room + "/light";
  //
  //  mqtt.publish(topicTemp, (String) temperature);
  //  mqtt.publish(topicPressure, (String) pressure);
  //  mqtt.publish(topicHumidity, (String) humidity);
  //  mqtt.publish(topicLight, (String) lux);

}

void reconnectWifi() {
  Serial.print("Reconnecting to ");
  Serial.println(ssid);
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected!");
}


void reconnectMqtt() {
  // Loop until we're reconnected
  mqtt.disconnect();
  Serial.print("Attempting MQTT connection...");
  // Attempt to connect
  int len = room.length()+1;
  char clientid[len];
  room.toCharArray(clientid, len);
  if (mqtt.connect(clientid, mqttUser, mqttPass)) {
    Serial.println("connected");
  } else {
    Serial.print("failed!");
    Serial.println(" try again in 5 seconds");
    // Wait 5 seconds before retrying
    delay(5000);
  }
}

float roundDescimals(float number){
  float multiplied = number * 100;
  int ni = (int) multiplied;
  float fni = (float) ni;
  return fni / 100;
}

void sendConfig() {
  DynamicJsonDocument payloadObj(512);
  payloadObj["device_class"] = "temperature";
  payloadObj["name"] = displayName + " Temperature";
  payloadObj["state_topic"] = "homeassistant/sensor/" + room + "/state";
  payloadObj["unit_of_measurement"] = "°C";
  payloadObj["value_template"] = "{{ value_json.temperature }}";
  String payload1;
  serializeJsonPretty(payloadObj, payload1);
  String topic1 = discoveryPrefix + "sensor/" + room + "T/config";
  mqtt.publish(topic1, payload1);

  payloadObj["device_class"] = "humidity";
  payloadObj["name"] = displayName + " Humidity";
  payloadObj["state_topic"] = "homeassistant/sensor/" + room + "/state";
  payloadObj["unit_of_measurement"] = "%";
  payloadObj["value_template"] = "{{ value_json.humidity }}";
  String payload2;
  serializeJsonPretty(payloadObj, payload2);
  String topic2 = discoveryPrefix + "sensor/" + room + "H/config";
  mqtt.publish(topic2, payload2);

  payloadObj["device_class"] = "pressure";
  payloadObj["name"] = displayName + " Pressure";
  payloadObj["state_topic"] = "homeassistant/sensor/" + room + "/state";
  payloadObj["unit_of_measurement"] = "hPa";
  payloadObj["value_template"] = "{{ value_json.pressure }}";
  String payload3;
  serializeJsonPretty(payloadObj, payload3);
  String topic3 = discoveryPrefix + "sensor/" + room + "P/config";
  mqtt.publish(topic3, payload3);

  payloadObj["device_class"] = "illuminance";
  payloadObj["name"] = displayName + " Illuminance";
  payloadObj["state_topic"] = "homeassistant/sensor/" + room + "/state";
  payloadObj["unit_of_measurement"] = "lux";
  payloadObj["value_template"] = "{{ value_json.light }}";
  String payload4;
  serializeJsonPretty(payloadObj, payload4);
  String topic4 = discoveryPrefix + "sensor/" + room + "L/config";
  mqtt.publish(topic4, payload4);
}

/**************************
   L O O P
**************************/
void loop() {
  if (WiFi.status() == WL_CONNECTION_LOST || WiFi.status() == WL_DISCONNECTED) {
    Serial.print("Wifi not connected?");
    reconnectWifi();
  }

  if (!mqtt.connected()) {
    Serial.println("No mqtt connection?");
    reconnectMqtt();
  }

  mqtt.loop();
  
  if (millis() - lastMillis > (sendInterval * 1000)) {
    lastMillis = millis();
    sendConfig();
    sendData();
  }
  delay(500);
}
