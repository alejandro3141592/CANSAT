//ESP32-RA01-LoRa-TX.ino
//======================================================================//
#include <SPI.h>
#include <LoRa.h>
//======================================================================//
#define PIN_LORA_COPI   23
#define PIN_LORA_CIPO   19
#define PIN_LORA_SCK    18
#define PIN_LORA_CS     5
#define PIN_LORA_RST    2
#define PIN_LORA_DIO0   4
#define LORA_FREQUENCY  433E6
//======================================================================//
int counter = 0;
//======================================================================//



#include <Wire.h>
//#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25

//Adafruit_BMP085 bmp;


#include <MPU6050_light.h>
MPU6050 mpu(Wire);


void setup() {
  Serial.begin (115200);
  while (!Serial);
  delay (1500);
  Serial.println ("LoRa Sender");
  LoRa.setPins (PIN_LORA_CS, PIN_LORA_RST, PIN_LORA_DIO0);
  LoRa.setSPIFrequency (20000000);
  LoRa.setTxPower (20);
  if (!LoRa.begin (LORA_FREQUENCY)) {
    Serial.println ("Starting LoRa failed!");
    while (1);
  }
  else {
    Serial.print ("LoRa initialized with frequency ");
    Serial.println (LORA_FREQUENCY);
  }


Wire.begin();

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");

//   if (!bmp.begin(0x77)) {
//  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
//  while (1) {}
//  }
}
//======================================================================//
void loop() {
  




//  Serial.print("Temperature = ");
//    Serial.print(bmp.readTemperature());
//    Serial.println(" *C");
//    
//    Serial.print("Pressure = ");
//    Serial.print(bmp.readPressure());
//    Serial.println(" Pa");
//
//    Serial.print("Altitude = ");
//    Serial.print(bmp.readAltitude());
//    Serial.println(" meters");
//
//    Serial.print("Pressure at sealevel (calculated) = ");
//    Serial.print(bmp.readSealevelPressure());
//    Serial.println(" Pa");
//
//    Serial.print("Real altitude = ");
//    Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
//    Serial.println(" meters");
//    
//    Serial.println();


  mpu.update();


    Serial.print(F("ACCELERO  X: "));Serial.print(mpu.getAccX());
    Serial.print("\tY: ");Serial.print(mpu.getAccY());
    Serial.print("\tZ: ");Serial.println(mpu.getAccZ());

    
    Serial.print(F("ANGLE     X: "));Serial.print(mpu.getAngleX());
    Serial.print("\tY: ");Serial.print(mpu.getAngleY());
    Serial.print("\tZ: ");Serial.println(mpu.getAngleZ());
    Serial.println(F("=====================================================\n"));

  Serial.print ("Sending packet: ");
  Serial.println (counter);
  // send packet
  LoRa.beginPacket();
  LoRa.print (mpu.getAccX());
  LoRa.print (",");
  LoRa.print (mpu.getAccY());
  LoRa.print (",");
  LoRa.print (mpu.getAccZ());
  LoRa.print (",");
  LoRa.print (mpu.getAngleX());
  LoRa.print (",");
  LoRa.print (mpu.getAngleY());
  LoRa.print (",");
  LoRa.print (mpu.getAngleZ());
  LoRa.endPacket();
  counter++;

    
  delay (1000);
}
//======================================================================//
