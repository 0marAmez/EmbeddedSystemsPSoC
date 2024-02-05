

int LED = 5;
int obstaclePin = 4;
int hasObstacle = HIGH;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(obstaclePin, INPUT);
}

void loop() {
    hasObstacle = digitalRead(obstaclePin);
  if (hasObstacle == HIGH)
  {
   
    digitalWrite(LED, HIGH);
  }
  else
  {  
   digitalWrite(LED, LOW);
  }
  delay(200);

}
