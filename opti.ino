#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

Adafruit_LiquidCrystal lcd(0);

const int ROW_NUM = 4;
const int COLUMN_NUM = 4;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {13, 12, 11, 10};
byte pin_column[COLUMN_NUM] = {9, 8, 7, 6};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

long unsigned int input_password;
int dell=0;
char x ='0';
int val = 0;
int val1[5];
long duration, distance;
int col[5] = {A0, A1, A2, A3, A6};  
char key ;
void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BOOTING");
  delay(1000);
  lcd.clear();  
  lcd.setBacklight(HIGH);
}
void loop()
{
      Servo myservo;  
      char key = keypad.getKey();
      x=key;
      if (key)
      {
      Serial.println(key);
      }
  switch (x)
  {   
    case '0':
      lcd.setCursor(0,0);
      lcd.print("1LED 2IR 3US 4AR");
      lcd.setCursor(0,1);
      lcd.print("5KNOB 6ROBO 7Servo");  
      break;
    case '1':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("A> Blink");
      lcd.setCursor(0, 1);
      lcd.print("B> Knob value");
      if (key == 'A' && x=='1')
      {
        x = '8';
      }
      if (key == 'B')
      {
        x = '9';
      }
      break;
    case '2':
#define IR A1
      pinMode(IR, INPUT);
      val = analogRead(IR);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("IR value");
      lcd.setCursor(0, 1);
      lcd.print(val);
      if (key == 'B')
      {
        x = '0';
      }
      break;
    case '3':
      dis();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("distance:");
      lcd.setCursor(0, 1);
      lcd.print(distance);
      if (key == 'B')
      {
        x = '0';
      }
      break;
    case '4':
      for (int i = 0 ; i < 5 ; i++)
      {
        lcd.clear();
        pinMode(col[i], INPUT);
        val1[i] = analogRead(col[i]);
        lcd.setCursor(0, 0);
        lcd.print("value of ");
        lcd.print(i);
        lcd.setCursor(0, 1);
        lcd.print(val1[i]);
        delay(1000);
      }
      if (key == 'B')
      {
        x = '0';
      }
      break;
    case '5':
      kno();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("pot value");
      lcd.setCursor(0, 1);
      lcd.print(val);
      if (key == 'B')
      {
        x = '0';
      }
      break;
    case '6':
#define RM 2
#define LM A3
      dis();
      val=distance;
      if (val < 50)
      {
        digitalWrite(RM, LOW);
        digitalWrite(LM, HIGH);
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("X");
        lcd.setCursor(9, 0);
        lcd.print("X");
        lcd.setCursor(7, 1);
        lcd.print("O");
      }
      else if (val <= 10)
      {
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("X");
        lcd.setCursor(9, 0);
        lcd.print("X");
        lcd.setCursor(7, 1);
        lcd.print("^");
      }
      else
      {
        digitalWrite(RM, HIGH);
        digitalWrite(LM, HIGH);
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("^");
        lcd.setCursor(9, 0);
        lcd.print("^");
        lcd.setCursor(6, 1);
        lcd.print("___");
      }
      if (key == 'B')
      {
        x = '0';
      }
      break;
    case '7':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("A> Set angel");
      lcd.setCursor(0, 1);
      lcd.print("B> Knob value");
      if (key == 'A')
      {
        x = '10';
      }
      if (key == 'B')
      {
        x = '11';
      }
      break;
    case '8':
      if (0<=key<=9)
       {
         dell += key;
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Delay val");
         lcd.setCursor(0,1);
         lcd.print(input_password);
#define LED_BUILTIN 5
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(input_password);
        digitalWrite(LED_BUILTIN, LOW);
        delay(input_password); 
       }
      if (key == 'B')
      {
        x = '0';
        dell=0;
      }
      break;
    case '9':
#define LED_BUILTIN 5
      pinMode(LED_BUILTIN, OUTPUT);
      kno();
      analogWrite(LED_BUILTIN, val);
      if (key == 'B')
      {
        x = '5';
      }
      break;
    case '10':
      myservo.attach(A5);
      if (0<=key<=9)
       {
         dell += key;
        if (0<=dell<=180)
        {
         myservo.write(dell);
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Angles");
         lcd.setCursor(0,1);
         lcd.print(dell);
        }
       }
      if (key == 'B')
      {
        x = '2';
      }
      break;
    case '11':
      myservo.attach(A5);
      kno();
      myservo.write(val);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Angles");
      lcd.setCursor(0, 1);
      lcd.print(val);
      if (key == 'B')
      {
        x = '2';
      }
      break;
    default:
      Serial.println(x);
      break;
  }
}
void dis()
{
#define trigPin 4
#define echoPin 3
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034;
}
void kno()
{
#define knob A0
      pinMode(knob, INPUT);
      val = analogRead(knob);
}