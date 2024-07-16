// code main of project

/*
    o codigo principal deverá conter:
        - conexão com wifi;
        - parte do sensor de luminosidade LDR
        - parte do sensor de fim de curso
*/

int led = 2;     // LED interno do esp32 (verificar a conexão com o wifi)
int fotoresistor = 34;  // Pino A0 (GPIO 34) para o fotoresistor no ESP32

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(fotoresistor, INPUT);
}

void loop()
{
  int fotoresistor_value = analogRead(fotoresistor);
  Serial.println(fotoresistor_value);
  
  // Quando o valor lido do fotoresistor é menor que 100, acende o LED ligado (led_pc_on)
  if (fotoresistor_value < 100) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  
  delay(100); // Pequeno delay para estabilidade da leitura
}
