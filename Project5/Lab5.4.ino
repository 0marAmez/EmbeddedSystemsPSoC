#include <ArduinoBLE.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343.h>
#include <Wire.h>

#define ADXL343_SCK 13
#define ADXL343_MISO 12
#define ADXL343_MOSI 11
#define ADXL343_CS 10

int leftPin1 = 2;
int leftSensor = HIGH;

int frontPin2 = 3;
int frontSensor = HIGH;

int rightPin3 = 4;
int rightSensor = HIGH;

/* Assign a unique ID to this sensor at the same time */
/* Uncomment following line for default Wire bus      */
//Adafruit_ADXL343 accel = Adafruit_ADXL343(12345);

/* NeoTrellis M4, etc.                    */
/* Uncomment following line for Wire1 bus */
//Adafruit_ADXL343 accel = Adafruit_ADXL343(12345, &Wire1);

/* Uncomment for SPI */
Adafruit_ADXL343 accel = Adafruit_ADXL343(ADXL343_SCK, ADXL343_MISO, ADXL343_MOSI, ADXL343_CS, 12345);
BLEService customService("1101");
BLEFloatCharacteristic customXChar("2101",  BLERead | BLENotify);
BLEFloatCharacteristic customYChar("2102",  BLERead | BLENotify );
BLEFloatCharacteristic customZChar("2102",  BLERead | BLENotify );
BLEBooleanCharacteristic customMovingChar("2102",  BLERead | BLENotify);
BLEBooleanCharacteristic customLEFTChar("2102",  BLERead | BLENotify );
BLEBooleanCharacteristic customFRONTChar("2102",  BLERead | BLENotify );
BLEBooleanCharacteristic customRIGHTChar("2102",  BLERead | BLENotify);




void displayDataRate(void)
{
  Serial.print  ("Data Rate:    ");

  switch(accel.getDataRate())
  {
    case ADXL343_DATARATE_3200_HZ:
      Serial.print  ("3200 ");
      break;
    case ADXL343_DATARATE_1600_HZ:
      Serial.print  ("1600 ");
      break;
    case ADXL343_DATARATE_800_HZ:
      Serial.print  ("800 ");
      break;
    case ADXL343_DATARATE_400_HZ:
      Serial.print  ("400 ");
      break;
    case ADXL343_DATARATE_200_HZ:
      Serial.print  ("200 ");
      break;
    case ADXL343_DATARATE_100_HZ:
      Serial.print  ("100 ");
      break;
    case ADXL343_DATARATE_50_HZ:
      Serial.print  ("50 ");
      break;
    case ADXL343_DATARATE_25_HZ:
      Serial.print  ("25 ");
      break;
    case ADXL343_DATARATE_12_5_HZ:
      Serial.print  ("12.5 ");
      break;
    case ADXL343_DATARATE_6_25HZ:
      Serial.print  ("6.25 ");
      break;
    case ADXL343_DATARATE_3_13_HZ:
      Serial.print  ("3.13 ");
      break;
    case ADXL343_DATARATE_1_56_HZ:
      Serial.print  ("1.56 ");
      break;
    case ADXL343_DATARATE_0_78_HZ:
      Serial.print  ("0.78 ");
      break;
    case ADXL343_DATARATE_0_39_HZ:
      Serial.print  ("0.39 ");
      break;
    case ADXL343_DATARATE_0_20_HZ:
      Serial.print  ("0.20 ");
      break;
    case ADXL343_DATARATE_0_10_HZ:
      Serial.print  ("0.10 ");
      break;
    default:
      Serial.print  ("???? ");
      break;
  }
  Serial.println(" Hz");
}

void displayRange(void)
{
  Serial.print  ("Range:         +/- ");

  switch(accel.getRange())
  {
    case ADXL343_RANGE_16_G:
      Serial.print  ("16 ");
      break;
    case ADXL343_RANGE_8_G:
      Serial.print  ("8 ");
      break;
    case ADXL343_RANGE_4_G:
      Serial.print  ("4 ");
      break;
    case ADXL343_RANGE_2_G:
      Serial.print  ("2 ");
      break;
    default:
      Serial.print  ("?? ");
      break;
  }
  Serial.println(" g");
}

void setup(void)
{

  pinMode(leftPin1, INPUT);
  pinMode(frontPin2, INPUT);
  pinMode(rightPin3, INPUT);
  
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Accelerometer Test"); Serial.println("");

  if (!BLE.begin()) {
      Serial.println("BLE failed to Initiate");
      delay(500);
      while (1);
  }

  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL343 ... check your connections */
    Serial.println("Ooops, no ADXL343 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL343_RANGE_16_G);
  // accel.setRange(ADXL343_RANGE_8_G);
  // accel.setRange(ADXL343_RANGE_4_G);
  // accel.setRange(ADXL343_RANGE_2_G);

  /* Display some basic information on this sensor */
  accel.printSensorDetails();
  displayDataRate();
  displayRange();
  Serial.println("");
  delay(1000);
  // BLE SERVER INIT
    BLE.setLocalName("CSE 121 Lab 5.4");
    BLE.setAdvertisedService(customService);
    customService.addCharacteristic(customXChar);
    customService.addCharacteristic(customYChar);
    customService.addCharacteristic(customZChar);
    customService.addCharacteristic(customMovingChar);
    customService.addCharacteristic(customLEFTChar);
    customService.addCharacteristic(customFRONTChar);
    customService.addCharacteristic(customRIGHTChar);

   
    BLE.addService(customService);
    BLE.advertise();
    Serial.println("Bluetooth device is now active, waiting for connections...");

}

void loop(void)
{
  /* Get a new sensor event */


   BLEDevice central = BLE.central();
    if (central) {
        Serial.print("Connected to central: ");
        Serial.println(central.address());
        while (central.connected()) {
          delay(200);
            sensors_event_t event;
            accel.getEvent(&event);
            leftSensor = digitalRead(leftPin1);
            frontSensor = digitalRead(frontPin2);
            rightSensor = digitalRead(rightPin3);
          
          customXChar.writeValue(event.acceleration.x);
          customYChar.writeValue(event.acceleration.y);
          customZChar.writeValue(event.acceleration.z);

           if((event.acceleration.x>=-0.12&& event.acceleration.x<=-0.4) || (event.acceleration.y>=0.16 && event.acceleration.y<=0.20) || (event.acceleration.z>=9.96&& event.acceleration.z<=10.04)){
              customMovingChar.setValue(true);
           }
           else{
               customMovingChar.setValue(false);
           }


          if (leftSensor == LOW){
              customLEFTChar.setValue(true);   
          }
          else{ 
              customLEFTChar.setValue(false);   
          }

           if (frontSensor == LOW){
               customFRONTChar.setValue(true);   
           }
           else{ 
               customFRONTChar.setValue(false);   
           }

           if (rightSensor == LOW){
                customRIGHTChar.setValue(true);      
           }
           else{ 
                customRIGHTChar.setValue(false);      
           }
        }
    }
  
  /* Display the results (acceleration is measured in m/s^2) */
 // Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  //Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  //Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  
  delay(500);
}
