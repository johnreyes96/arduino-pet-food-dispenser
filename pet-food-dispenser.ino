#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define CLOSE 0
#define OPEN 90

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
const byte COLUMNS = 4;
const byte ROWS = 4;
const byte SERVO = 8;
const byte LED = 9;
const byte PIEZO = 10;
const byte FOOD_DISPENSER_ITERATORS = 3;
const byte LED_SEQUENCE_ITERATORS = 5;
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
  _runByKeypad();
}

void _runByKeypad()
{
  switch (_getKey())
  {
    case 'A':
      _feed();
      break;
    case 'B':
      _muteOrUnmute();
      break;
  }
}

void _feed()
{
  _executeLedSequence();
  _foodDispenser();
  digitalWrite(LED, LOW);
  _reproduceMusic();
}

void _executeLedSequence()
{
  for (int index = 0; index < LED_SEQUENCE_ITERATORS; index++)
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
  String messageFirstLine = "   Dispensando  ";
  String messageSecondLine = "     Comida     ";
  _showMessageInLCDDisplay(messageFirstLine, messageSecondLine);
  _executeServomotorSequence();
  _updateMessageMuteOrUnmuteInLCD();
}

void _executeServomotorSequence()
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
    _piezoNotice();
  }
  _updateMessageMuteOrUnmuteInLCD();
}

void _ledNotice()
{
  digitalWrite(LED, HIGH);
  delay(150);
  digitalWrite(LED, LOW);
}

void _piezoNotice()
{
  tone(PIEZO, 440, 100);
  delay(100);
  noTone(PIEZO);
  digitalWrite(PIEZO, HIGH);
}

void _updateMessageMuteOrUnmuteInLCD()
{
  String messageFirstLine = "A: Dar alimento ";
  String messageSecondLine = _isMute ? "B: Desmutear    " : "B: Mutear       ";
  _showMessageInLCDDisplay(messageFirstLine, messageSecondLine);
}

void _showMessageInLCDDisplay(String messageFirstLine, String messageSecondLine)
{
  lcd.setCursor(0, 0);
  lcd.print(messageFirstLine);
  lcd.setCursor(0, 1);
  lcd.print(messageSecondLine);
}

char _getKey()
{
  return _keyboard.getKey();
}

void _reproduceMusic()
{
  if (!_isMute)
  {
    double _musicalNotes[] = { 523.25, 587.33, 659.25, 698.45, 783.99 };
    double _times[] = { 0, 100, 200 };
    int _notesSequence[] = { 0, 1, 1, 1, 2, 3, 3, 3, 4, 2, 2, 1, 0, 0, 1 };
    int _timesSequence[] = { 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 0 };
    for (int index = 0; index < 16; index++)
    {
      tone(PIEZO, _musicalNotes[_notesSequence[index]], 100);
      delay(_times[_timesSequence[index]]);
    }
    noTone(PIEZO);
    digitalWrite(PIEZO, HIGH);
  }
}

void _initServomotor()
{
  _servoMotor.attach(SERVO);
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
  _updateMessageMuteOrUnmuteInLCD();
}