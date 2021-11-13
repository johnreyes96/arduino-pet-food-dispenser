#include <Key.h>
#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

#define CERRAR 0
#define ABRIR 90

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
const byte columns = 4;
const byte rows = 4;
Servo servoMotor;
char inKeys;
byte rowPins[rows] = { 7, 6, 5, 4 };
byte columnPins[columns] = { 3, 2, 1, 0 };
char keys[rows][columns] = 
{
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' },
};
Keypad keyboard = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);

void setup()
{
  servoMotor.attach(8);
  servoMotor.write(CERRAR);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Puerta cerrada");
  lcd.setCursor(0, 1);
  lcd.print("holiii");
}

void loop()
{
  inKeys = keyboard.getKey();
  switch (inKeys) {
    case 'A':
      servoMotor.write(ABRIR);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      break;
    case 'B':
      servoMotor.write(CERRAR);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      break;
  }
}