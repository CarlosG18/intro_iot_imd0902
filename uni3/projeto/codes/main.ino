#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <ThingsBoard.h>
#include <ArduinoHttpClient.h>
#include <EEPROM.h>

#define EEPROM_SIZE 4 // definindo a quantidade de endereços para serem gravados - [0] sensorfimdecurso; [1] sensorluminosidade; [2] estado da porta; [3] contador porta aberta
#define TOKEN "xuuto5gbwck4h6bornbf" // token para autenticação do thingsboard

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

const char* wifi_ssid = "sala203";
const char* wifi_password = "s@l@203#";
int wifi_timeout = 100000;

const char* mqtt_broker = "mqtt.thingsboard.cloud";
const int mqtt_port = 1883;

int mqtt_timeout = 10000;
int contador_open = 0;
int estado_porta = 0; // estado da porta - inicialmente fechada (0)
int estado_anterior = 0;

int led = 2;     // Pino D2 (GPIO 2) para led interno - função de sinalizar a conectividade do esp32 com o wifi
int sensorLuminosidadePin = 34;  // Pino A0 (GPIO 34) para o fotoresistor no ESP32
int fimDeCursoPin_left = 14; // sensor fim de curso para obter o estado do armario (aberto ou fechado) para a porta esquerda
int fimDeCursoPin_right = 27; // sensor fim de curso para obter o estado do armario (aberto ou fechado) para a porta direita
String estado_armario_s;

void setup() {
  // configuração inicial para armazenar na memoria interna do esp32
  EEPROM.begin(EEPROM_SIZE); 
  //estado_porta = EEPROM.read(2);
  contador_open = EEPROM.read(1);

  // configuração dos pinos do esp32
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(sensorLuminosidadePin, INPUT);
  pinMode(fimDeCursoPin_left, INPUT);
  pinMode(fimDeCursoPin_right, INPUT);

  // configuração do wifi
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

    // realizando a leitura dos sensores
    int fotoresistor_value = analogRead(sensorLuminosidadePin); // lendo o valor do sensor de luminosidade LDR
    bool fimdecurso_left = digitalRead(fimDeCursoPin_left);
    bool fimdecurso_right = digitalRead(fimDeCursoPin_right);
    
    bool estado_armario = fimdecurso_left || fimdecurso_right;
    
    if(estado_anterior != estado_armario && estado_armario == 1){
      contador_open += 1;
    }
    estado_anterior = estado_armario;

    if(estado_armario){
      estado_armario_s = "Aberto";
    } else{
      estado_armario_s = "Fechado";
    }

    String payload = "{\"Luz\":" + String(fotoresistor_value)+",\"fimdecurso_left\":" + String(fimdecurso_left)+",\"fimdecurso_right\":" + String(fimdecurso_right)+",\"estado_armario\":" + estado_armario_s+",\"contador\":" + String(contador_open)+"}";
    char attributes [1000];

    payload.toCharArray(attributes, 1000);

    mqtt_client.publish("v1/devices/me/telemetry", attributes);
    mqtt_client.publish("v1/devices/me/attributes", attributes);

    Serial.println(attributes);

    delay(1000);

    EEPROM.write(1, contador_open); // args: endereço , variavel a ser gravada 
    EEPROM.commit(); // salvando de fato
  }  
}

void connectWiFi(){
  /*
    função para conectar no wifi
  */

  Serial.print("Conectando à rede WiFi .. ");
  unsigned long tempoInicial = millis();
  while(WiFi.status() != WL_CONNECTED && (millis() - tempoInicial < wifi_timeout)){
    Serial.print(".");
    delay(100);
  }
  Serial.println();


  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Conexão com WiFi falhou!");
    digitalWrite(led, LOW);
  } else{
    Serial.print("Conectado com o IP: ");
    // ligando o led interno para sinalizar conexão com o wifi
    digitalWrite(led, HIGH);
    Serial.println(WiFi.localIP());
  }
}


void connectMQTT() {
  /*
    Função para conectar no protocolo mqtt
  */
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
