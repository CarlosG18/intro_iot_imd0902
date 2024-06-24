#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#define DHTPIN 18    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define IO_USERNAME 
//#define IO_KEY 

DHT dht(DHTPIN, DHTTYPE);

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

const char* wifi_ssid = "sala203";
const char* wifi_password = "s@l@203#";
int wifi_timeout = 100000;

const char* mqtt_broker = "io.adafruit.com";
const int mqtt_port = 1883;
int mqtt_timeout = 10000;

void setup() {
  Serial.begin(9600);
  
  //sensor
  dht.begin();

  //wifi
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

    Serial.print("publicando temperatura: ");
    Serial.println(String(t).c_str());
    if (mqtt_client.publish("CarlosG18/feeds/temperatura", String(t).c_str(), true)) {
      Serial.println("Temperatura publicada com sucesso!");
    }else{
      Serial.println("Falha ao publicar a temperatura!");
    }
    
    Serial.print("publicando umidade: ");
    Serial.println(String(h).c_str());
    if (mqtt_client.publish("CarlosG18/feeds/umidade", String(h).c_str(), true)) {
      Serial.println("Umidade publicada com sucesso!");
    }else{
      Serial.println("Falha ao publicar a umidade!");
    }
    delay(5000);
  }
}

void connectMQTT() {
  // Loop até conseguir conectar
  unsigned long tempoInicial = millis();
  while (!mqtt_client.connected() && (millis() - tempoInicial < mqtt_timeout)) {
    if (WiFi.status() != WL_CONNECTED){
        connectWiFi();
    }
    Serial.print("Attempting MQTT connection...");
    // Tente conectar
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    // Tente conectar usando as credenciais do Adafruit IO
    if (mqtt_client.connect(clientId.c_str(), IO_USERNAME, IO_KEY)) {
      Serial.println("conetado!");
    } else {
      Serial.print("falha de conexão, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      // Espere 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
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
