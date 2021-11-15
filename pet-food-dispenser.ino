#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define CLOSE 0
#define OPEN 90

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
const byte COLUMNS = 4;
const byte ROWS = 4;
const byte LED = 9;
const byte PIEZO = 10;
const byte FOOD_DISPENSER_ITERATORS = 3;
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
String _messages[2];
boolean _isMute;

void setup()
{
  _initServomotor();
  _initLed();
  _initPiezo();
  _initLCDDisplay();
  _isMute = false;
}

void loop()
{
  _executeFunctionByKeypad();
}

void _executeFunctionByKeypad()
{
  switch (_getKey()) {
    case 'A':
      _ledSequence();
      _foodDispenser();
      digitalWrite(LED, LOW);
      _reproduceMusic();
      break;
    case 'B':
      _muteOrUnmute();
      break;
  }
}

void _ledSequence()
{
  for (int index = 0; index < 5; index++)
  {
    digitalWrite(LED, HIGH);
    delay(150);
    digitalWrite(LED, LOW);
    delay(150);
  }
  digitalWrite(LED, HIGH);
}

void _foodDispenser()
{
  _messages[0] = "   Dispensando  ";
  _messages[1] = "     Comida     ";
  _showMessageInLCDDisplay(_messages);
  _foodDispenserSequence();
  _updateMessageMuteOrUnmuteInLCD();
}

void _foodDispenserSequence()
{
  for (int index = 0; index < FOOD_DISPENSER_ITERATORS; index++)
  {
    _servoMotor.write(OPEN);
    delay(600);
    _servoMotor.write(CLOSE);
    delay(600);
  }
}

void _muteOrUnmute()
{
  _isMute = !_isMute;
  _ledNotice();
  if (!_isMute)
  {
    _piezoNotica();
  }
  _updateMessageMuteOrUnmuteInLCD();
}

void _ledNotice()
{
  digitalWrite(LED, HIGH);
  delay(150);
  digitalWrite(LED, LOW);
}

void _piezoNotica()
{
  tone(PIEZO, 440, 100);
  delay(100);
  noTone(PIEZO);
  digitalWrite(PIEZO, HIGH);
}

void _updateMessageMuteOrUnmuteInLCD() {
  _messages[0] = "A: Dar alimento ";
  if (_isMute)
  {
    _messages[1] = "B: Desmutear    ";
  }
  else
  {
    _messages[1] = "B: Mutear       ";
  }
  _showMessageInLCDDisplay(_messages);
}

void _showMainMessageInLCDDisplay()
{
  lcd.setCursor(0, 0);
  lcd.print("A: Dar alimento ");
  lcd.setCursor(0, 1);
  lcd.print("B: Mutear       ");
}

void _showMessageInLCDDisplay(String message[])
{
  lcd.setCursor(0, 0);
  lcd.print(message[0]);
  lcd.setCursor(0, 1);
  lcd.print(message[1]);
}

char _getKey()
{
  return _keyboard.getKey();
}

void _reproduceMusic()
{
  if (!_isMute)
  {
    tone(PIEZO, 440, 100);
    delay(100);
    tone(PIEZO, 523.25, 100);
    delay(100);
    tone(PIEZO, 587.33, 100);
    delay(200);
    tone(PIEZO, 587.33, 100);
    delay(200);
    tone(PIEZO, 587.33, 100);
    delay(100);
    tone(PIEZO, 659.25, 100);
    delay(100);
    tone(PIEZO, 698.45, 100);
    delay(200);
    tone(PIEZO, 698.45, 100);
    delay(200);
    tone(PIEZO, 698.45, 100);
    delay(100);
    tone(PIEZO, 783.99, 100);
    delay(100);
    tone(PIEZO, 659.25, 100);
    delay(200);
    tone(PIEZO, 659.25, 100);
    delay(200);
    tone(PIEZO, 587.33, 100);
    delay(100);
    tone(PIEZO, 523.25, 100);
    delay(100);
    tone(PIEZO, 523.25, 100);
    delay(100);
    tone(PIEZO, 587.33, 100);
    noTone(PIEZO);
    digitalWrite(PIEZO, HIGH);
  }
}

void _initServomotor()
{
  _servoMotor.attach(8);
  _servoMotor.write(CLOSE);
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