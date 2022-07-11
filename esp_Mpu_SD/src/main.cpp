#include <Arduino.h>
#include <Print.h>
#include"FS.h"
#include "SD.h"
#include "SPI.h"
#include "EEPROM.h"
#include "I2Cdev.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

String sutun1 = "Örnek_Sayısı";
String sutun2 = "accx";
String sutun3 = "accy";
String sutun4 = "accz";
String sutun8 = "gecen_Sure_ms";
String str = sutun1 + "," + sutun2 + "," + sutun3 + "," + sutun4 + "Gecen_Sure" + "\n\n";
uint16_t dosya_no;
uint16_t ornek_no = 0;
String dosya_adi;
int address = 0;
int address_1;
String str1;
uint32_t baslangic;
uint32_t gecen;
byte value;
const int chipSelect = 32;
String dosya;

Adafruit_MPU6050 mpu;
void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}
void appendFile(fs::FS &fs, const char *path, const char *message)
{
<<<<<<< HEAD
  //Serial.printf("Appending to file: %s\n", path);
=======
  Serial.printf("Appending to file: %s\n", path);
>>>>>>> c0f130a7b8b02c475c9677bf9491138ce1935297

  File file = fs.open(path, FILE_APPEND);
  if (!file)
  {
    Serial.println("Failed to open file for appending");
    return;
  }
<<<<<<< HEAD
  /* if (file.print(message))
=======
  if (file.print(message))
>>>>>>> c0f130a7b8b02c475c9677bf9491138ce1935297
  {
    Serial.println("Message appended");
  }
  else
  {
    Serial.println("Appended failed");
    return;
<<<<<<< HEAD
  }*/
 
=======
  }
>>>>>>> c0f130a7b8b02c475c9677bf9491138ce1935297
  file.close();
}
void setup()
{
  Serial.begin(115200);
  EEPROM.begin(512);
  value = EEPROM.read(address);
  delay(500);
  dosya_adi = "acc_data" + String(value - 1);
  //////////////////
  if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
  Serial.println("card initialized.");
  delay(50);
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  while (!Serial)
  {
    delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  str1 = "/" + dosya_adi + ".txt";
  writeFile(SD,str1.c_str(),str.c_str());
<<<<<<< HEAD
  //Serial.println(str);
=======
  Serial.println(str);
>>>>>>> c0f130a7b8b02c475c9677bf9491138ce1935297
  //appendFile(SD, str1.c_str(), str.c_str());
  delay(300);

  dosya_no = EEPROM.read(address);
  dosya_no = dosya_no + 1;
  EEPROM.write(address, dosya_no);
  EEPROM.commit();
  delay(100);
}

void loop()
{
  
<<<<<<< HEAD
 // Serial.println(str1);
  sensors_event_t a, g,temp;
  mpu.getEvent(&a, &g, &temp);
  //Serial.println(dosya_no);
  gecen = millis() - baslangic;
  String olcum =String(a.acceleration.x) + "," + String(a.acceleration.y) + "," + String(a.acceleration.z) + "," + String(gecen) + "\n"; 
=======
  Serial.println(str1);
  sensors_event_t a, g,temp;
  mpu.getEvent(&a, &g, &temp);
  Serial.println(dosya_no);
  gecen = millis() - baslangic;
  String olcum = String(ornek_no) + "," + String(a.acceleration.x) + "," + String(a.acceleration.y) + "," + String(a.acceleration.z) + "," + String(gecen) + "\n"; 
>>>>>>> c0f130a7b8b02c475c9677bf9491138ce1935297
  appendFile(SD,str1.c_str(), olcum.c_str());
  Serial.println(olcum);
  ornek_no+=1;
  baslangic = millis();
  
  delay(100);
}