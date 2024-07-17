#include <Preferences.h>

Preferences preferences;

// Exemplo de pino para o sensor de fim de curso
const int fimDeCursoPin = 13;

 // Exemplo de pino para o sensor de luminosidade (LDR)
const int sensorLuminosidadePin = 34;

int lerFimDeCurso() {
  return digitalRead(fimDeCursoPin);
}

int lerLuminosidade() {
  return analogRead(sensorLuminosidadePin);
}

void setup() {
  Serial.begin(115200);

  // Inicialize os pinos dos sensores
  pinMode(fimDeCursoPin, INPUT);
  pinMode(sensorLuminosidadePin, INPUT);

  // Inicie as preferências com um namespace
  preferences.begin("sensores", false);

  // Leia os valores dos sensores
  int fimDeCursoValor = lerFimDeCurso();
  int luminosidadeValor = lerLuminosidade();

  // Armazene os valores dos sensores
  preferences.putInt("fimDeCurso", fimDeCursoValor);
  preferences.putInt("luminosidade", luminosidadeValor);

  // Recupere os valores armazenados
  int fimDeCursoArmazenado = preferences.getInt("fimDeCurso", 0);
  int luminosidadeArmazenada = preferences.getInt("luminosidade", 0);

  // Exiba os valores no Serial Monitor
  Serial.print("Fim de Curso Armazenado: ");
  Serial.println(fimDeCursoArmazenado);
  Serial.print("Luminosidade Armazenada: ");
  Serial.println(luminosidadeArmazenada);

  // Feche as preferências
  preferences.end();
}

void loop() {
  // Nada aqui
}
