//Teste Basico do Display 16x2
#include "LiquidCrystal.h" //Biblioteca para Controlar o Display

LiquidCrystal lcd(14,12,27,26,25,33); //Inicializa o Display

void setup()
{
  lcd.begin(16, 2); //Identifica que o display possui 16 colunas e 2 linhas
}

void loop()
{
  lcd.clear(); //Apaga todos os caracteres do Display
  lcd.setCursor(0,0);//Marca o cursor na posição coluna 0, linha 0
  lcd.print("teste");//Escreve a mensagem a partir da posição coluna 0, linha 0
  lcd.setCursor(0,1);//Marca o cursor na posição coluna 0, linha 1
  lcd.print("lcd");//Escreve a mensagem a partir da posição coluna 0, linha 1
  delay(3000);  
}
