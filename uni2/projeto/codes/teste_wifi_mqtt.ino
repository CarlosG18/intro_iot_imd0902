#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

const char* mqtt_broker = "broker.mqtt.cool";
const int mqtt_port = 1883;
int mqtt_timeout = 10000;

const char* wifi_ssid = "sala203";
const char* wifi_password = "s@l@203#";
int wifi_timeout = 100000;

int variavel = 0;

void setup() {
  Serial.begin(9600);

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
    variavel = random(1,100);
    if(mqtt_client.publish("/imd0902/pratica03/variavel", String(variavel).c_str(), true)){
      mqtt_client.publish("/imd0902/pratica03/variavel", String(variavel).c_str(), true);
      Serial.println("enviado!");
    }else{
      Serial.println("erro envio!");
    }
    delay(1000);
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