#include "DFRobot_RGBLCD1602.h"

const int colorR = 0;
const int colorG = 255;
const int colorB = 0;
int LED = 5;

int obstaclePin1 = 2;
int leftSensor = HIGH;

int obstaclePin2 = 3;
int frontSensor = HIGH;

int obstaclePin3 = 4;
int rightSensor = HIGH;

DFRobot_RGBLCD1602 lcd(/*lcdCols*/16,/*lcdRows*/2);  //16 characters and 2 lines of show

void setup() {
    /**
     *  @brief initialize the LCD and master IIC
     */ 
    lcd.init();
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.

    pinMode(LED, OUTPUT);
    pinMode(obstaclePin1, INPUT);
    pinMode(obstaclePin2, INPUT);
    pinMode(obstaclePin3, INPUT);


    delay(1000);

}

void loop() {
    leftSensor = digitalRead(obstaclePin1);
    frontSensor = digitalRead(obstaclePin2);
    rightSensor = digitalRead(obstaclePin3);

    lcd.clear();
    lcd.print("LEFT FRONT RIGHT");


  if (leftSensor == LOW)
  {
    lcd.setCursor(0, 1);
    digitalWrite(LED, LOW);
    lcd.print("YES");

  }
  else
  { 
    lcd.setCursor(0, 1); 
    digitalWrite(LED, HIGH);
    lcd.print("NO");
  }

   if (frontSensor == LOW)
  {
    lcd.setCursor(6, 1);
    digitalWrite(LED, LOW);
    lcd.print("YES");

  }
  else
  { 
    lcd.setCursor(6, 1); 
    digitalWrite(LED, HIGH);
    lcd.print("NO");
  }

    if (rightSensor == LOW)
  {
    lcd.setCursor(12, 1);
    digitalWrite(LED, LOW);
    lcd.print("YES");

  }
  else
  { 
    lcd.setCursor(12, 1); 
    digitalWrite(LED, HIGH);
    lcd.print("NO");
  }
  delay(200);
}
