#include "DHT.h"

#define DHTPIN 21     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT22 test!"));
  dht.begin();
}

void loop() {
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //float f = dht.readTemperature(true);

  if (isnan(h)) {
    Serial.println(F("Falha na leitura de umidade do sensor!"));
    return;
  }

  if (isnan(t)) {
    Serial.println(F("Falha na leitura de temperatura do sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Umidade: "));
  Serial.print(h);
  Serial.print(F("%  Temperatura: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Sensação Térmica: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}