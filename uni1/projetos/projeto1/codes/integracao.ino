#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#define DHTPIN 18     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

const char* wifi_ssid = "sala203";
const char* wifi_password = "s@l@203#";
int wifi_timeout = 100000;


const char* mqtt_broker = "broker.hivemq.com";
const int mqtt_port = 1883;
int mqtt_timeout = 10000;

void setup() {
  //sensor
  Serial.begin(115200);
  dht.begin();

  WiFi.mode(WIFI_STA); //"station mode": permite o ESP32 ser um cliente da rede WiFi
  WiFi.begin(wifi_ssid, wifi_password);
  connectWiFi();
  mqtt_client.setServer(mqtt_broker, mqtt_port);
}


void loop() {
  if (!mqtt_client.connected()){
    connectMQTT();
  }
  if (mqtt_client.connected()){
    mqtt_client.loop();

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    //float f = dht.readTemperature(true);
    Serial.print("publicando temperatura: ");
    Serial.println(String(t).c_str());
    if (mqtt_client.publish("/imd0902/projeto1/temperatura", String(t).c_str(), true)) {
      Serial.println("Temperatura publicada com sucesso!");
    }else{
      Serial.println("Falha ao publicar a temperatura!");
    }
    
    Serial.print("publicando umidade: ");
    Serial.println(String(h).c_str());
    if (mqtt_client.publish("/imd0902/projeto1/umidade", String(h).c_str(), true)) {
      Serial.println("Umidade publicada com sucesso!");
    }else{
      Serial.println("Falha ao publicar a umidade!");
    }
    delay(2000);
  }
    

    /*if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(f);
    Serial.println();
    Serial.print(F("°F  Heat index: "));
    Serial.print(hic);
    Serial.print(F("°C "));
    Serial.print(hif);
    Serial.println(F("°F"));*/
}

void connectWiFi(){
  Serial.print("Conectando à rede WiFi .. ");

  unsigned long tempoInicial = millis();
  while(WiFi.status() != WL_CONNECTED && (millis() - tempoInicial < wifi_timeout)){
    Serial.print(".");
    delay(100);
  }
  Serial.println();


  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Conexão com WiFi falhou!");
  } else{
    Serial.print("Conectado com o IP: ");
    Serial.println(WiFi.localIP());
  }
}


void connectMQTT() {
  unsigned long tempoInicial = millis();
  while (!mqtt_client.connected() && (millis() - tempoInicial < mqtt_timeout)) {
      if (WiFi.status() != WL_CONNECTED){
        connectWiFi();
      }
      Serial.print("Conectando ao MQTT Broker..");
     
      if (mqtt_client.connect("ESP32Client")) {
        Serial.println();
        Serial.print("Conectado ao broker MQTT!");
      } else{
        Serial.println();
        Serial.print("Conexão com o broker MQTT falhou!");
      }
      delay(100);
  }
  Serial.println();
}
