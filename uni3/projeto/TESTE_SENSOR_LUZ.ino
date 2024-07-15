// Pino D4 (GPIO 4) para LED ligado
int led = 2;     // Pino D2 (GPIO 2) para LED desligado
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
