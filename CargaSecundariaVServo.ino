#include <SoftwareSerial.h>

#include <Servo.h>
int i = 0;
Servo myservo;  // create servo object to control a servo

// The serial connection to the GPS module
SoftwareSerial ss(10, 11);

void setup(){
  Serial.begin(115200);
  ss.begin(9600);
  myservo.attach(2);
  myservo.write(0);
}

void loop(){
  while (ss.available() > 0){
    // get the byte data from the GPS
    byte gpsData = ss.read();
    Serial.write(gpsData);
  }
  i++;
  delay(100);
  if (i==30){
  myservo.write(160);
  Serial.println("1");
  }
  if (i==60){
  myservo.write(0);
  Serial.println("0");
  i = 0;
  }
  
}
