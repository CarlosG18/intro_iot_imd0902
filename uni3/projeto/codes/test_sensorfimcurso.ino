#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ThingsBoard.h>
#include <ArduinoHttpClient.h>

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

const char* wifi_ssid = "MEDEIROS SILVA";
const char* wifi_password = "lage1890";
int wifi_timeout = 100000;

const char* mqtt_broker = "mqtt.thingsboard.cloud";
const int mqtt_port = 1883;

#define TOKEN "xuuto5gbwck4h6bornbf"

int mqtt_timeout = 10000;

int led = 2;     // Pino D2 (GPIO 2) para LED desligado
//int sensorLuminosidadePin = 34;  // Pino A0 (GPIO 34) para o fotoresistor no ESP32
int fimDeCursoPin = 14;

int lerFimDeCurso() {
  return digitalRead(fimDeCursoPin);
}

/*int lerLuminosidade() {
  return analogRead(sensorLuminosidadePin);
}*/

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  //pinMode(sensorLuminosidadePin, INPUT);
  pinMode(fimDeCursoPin, INPUT);

  WiFi.mode(WIFI_STA); //"station mode": permite o ESP32 ser um cliente da rede 
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
    /*int fotoresistor_value = analogRead(sensorLuminosidadePin);
    
    if (fotoresistor_value < 100) {
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }*/

    bool fimdecurso = lerFimDeCurso();

    //String payload = "{\"Luz\":" + String(fotoresistor_value)+",\"fimdecurso\":" + String(fimdecurso)+"}";
    String payload = "{\"fimdecurso\":" + String(fimdecurso)+"}";
    char attributes [1000];

    payload.toCharArray(attributes, 1000);

    mqtt_client.publish("v1/devices/me/telemetry", attributes);
    mqtt_client.publish("v1/devices/me/attributes", attributes);

    Serial.print(attributes);

    delay(1000);
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


void connectMQTT() {
  unsigned long tempoInicial = millis();
  while (!mqtt_client.connected() && (millis() - tempoInicial < mqtt_timeout)) {
      if (WiFi.status() != WL_CONNECTED){
        connectWiFi();
      }
      Serial.print("Conectando ao MQTT Broker..");
     
      if (mqtt_client.connect("ESP32Client", TOKEN, NULL)) {
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
