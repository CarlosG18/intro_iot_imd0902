#include <EEPROM.h>

#define EEPROM_SIZE 2
// Exemplo de pino para o sensor de fim de curso
const int fimDeCursoPin = 14;
const int Led_interno = 2;

bool status_fimdecurso = 0;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  pinMode(fimDeCursoPin, INPUT);
  pinMode(Led_interno, OUTPUT);

  status_fimdecurso = EEPROM.read(0);
  Serial.print("valor da variavel gravada = ");
  Serial.println(status_fimdecurso);
  if(status_fimdecurso){
    digitalWrite(Led_interno, HIGH);
  }else{
    digitalWrite(Led_interno, LOW);
  }
}

void loop() {
  status_fimdecurso = digitalRead(fimDeCursoPin);
  delay(500);



  EEPROM.write(0, status_fimdecurso); // args: endereço , variavel a ser gravada 
  EEPROM.commit(); // salvando de fato
}
