#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define CERRAR 0
#define ABRIR 90

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
const byte COLUMNS = 4;
const byte ROWS = 4;
const byte LED = 9;
const byte PIEZO = 10;
const char KEYS[ROWS][COLUMNS] = 
{
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' },
};
byte _rowPins[ROWS] = { 7, 6, 5, 4 };
byte _columnPins[COLUMNS] = { 3, 2, 1, 0 };
Keypad _keyboard = Keypad(makeKeymap(KEYS), _rowPins, _columnPins, ROWS, COLUMNS);
Servo _servoMotor;
String messages[2];

void setup()
{
  _initServomotor();
  _initLed();
  _initPiezo();
  _initLCDDisplay();
}

void loop()
{
  _executeFunctionByKeypad();
}

void _executeFunctionByKeypad()
{
  switch (_getKey()) {
    case 'A':
      _foodDispenser();
      break;
    case 'B':
      _setInitialStatus();
      break;
  }
}

void _foodDispenser()
{
  _servoMotor.write(ABRIR);
  digitalWrite(LED, HIGH);
  messages[0] = "   Dispensando  ";
  messages[1] = "     Comida     ";
  _showMessageInLCDDisplay(messages);
}

void _setInitialStatus()
{
  _servoMotor.write(CERRAR);
  digitalWrite(LED, LOW);
  delay(600);
  _showMainMessageInLCDDisplay();
  _reproduceMusic();
}

void _reproduceMusic()
{
  //TODO Pending to do
}

char _getKey()
{
  return _keyboard.getKey();
}

void _initServomotor()
{
  _servoMotor.attach(8);
  _servoMotor.write(CERRAR);
}

void _initLed()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void _initPiezo()
{
  pinMode(PIEZO, OUTPUT);
  digitalWrite(PIEZO, HIGH);
}

void _initLCDDisplay()
{
  lcd.begin(16, 2);
  _showMainMessageInLCDDisplay();
}

void _showMainMessageInLCDDisplay()
{
  lcd.setCursor(0, 0);
  lcd.print("A: Para abrir   ");
  lcd.setCursor(0, 1);
  lcd.print("B: Para cerrar  ");
}

void _showMessageInLCDDisplay(String message[])
{
  lcd.setCursor(0, 0);
  lcd.print(message[0]);
  lcd.setCursor(0, 1);
  lcd.print(message[1]);
}