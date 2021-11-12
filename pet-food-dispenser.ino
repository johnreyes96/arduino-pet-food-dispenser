#include <Servo.h>
#include <LiquidCrystal.h>
#define CERRAR 0
#define ABRIR 90

Servo servoMotor;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

void setup()
{
  servoMotor.attach(8);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Puerta cerrada");
  lcd.setCursor(0, 1);
  lcd.print("holiii");
}

void loop()
{
  int lectura;
  lectura=analogRead(A0);
  if(lectura>=300&&lectura<=500){
    servoMotor.write(ABRIR);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    delay(1000);
  }else{
    servoMotor.write(CERRAR);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    delay(1000);
  }
}