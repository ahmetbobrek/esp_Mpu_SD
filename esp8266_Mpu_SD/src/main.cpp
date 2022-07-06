#include <Arduino.h>
#include <Print.h>
#include "SD.h"
#include "SPI.h"
#include "RTClib.h"
#include "EEPROM.h"
#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"
#include "Wire.h"
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

#ifndef STASSID
#define STASSID "Excellence"
#define STAPSK "Bobrek03"
#endif
const char *ssid = STASSID;
const char *password = STAPSK;

#define OFFSET 0
#define sleepPeriod 10000000ul
// const char *ssid = "Excellence";   // your network SSID (name)
// const char *password = "Bo005727"; // your network password
const int chipSelect = 15;
String dosya;
int16_t cal1;
int16_t cal2;
int16_t cal3;
int16_t acc;
String sutun1 = "Örnek_Sayısı";
String sutun2 = "accx";
String sutun3 = "accy";
String sutun4 = "accz";
String sutun8 = "gecen_Sure_ms";
String str = sutun1 + "," + sutun2 + "," + sutun3 + "," + sutun4 + "Gecen_Sure"
                                                                   "\n\n";
uint16_t dosya_no;
uint16_t ornek_no = 0;
String dosya_adi;
int address = 0;
int address_1;
String str1;
uint32_t baslangic;
uint32_t gecen;
byte value;
String olcum = "Olcum";
Adafruit_MPU6050 mpu;
unsigned long myChannelNumber = 1789113;
const char *myWriteAPIKey = "DQWYM7ET7PUDD11W";

void setup()
{

  Serial.begin(115200);
  /*WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }*/
  
  WiFiClient client;
  EEPROM.begin(512);
  value = EEPROM.read(address);
  delay(500);
  dosya_adi = "acc_data" + String(value - 1);

  if (!SD.begin(chipSelect))
  {
    Serial.println("Card mount failed");
    return;
  }
  Serial.println("card initialized.");
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  str1 = "/" + dosya_adi + ".txt";

  dosya_no = EEPROM.read(address);
  dosya_no = dosya_no + 1;
  EEPROM.write(address, dosya_no);
  EEPROM.commit();
  delay(100);
  // ThingSpeak.begin(client); // Initialize ThingSpea
}

void loop()
{
  static bool wait = false;
  WiFiClient client;
  ThingSpeak.begin(client); // Initialize ThingSpea

  Serial.println(str1);
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  Serial.println(str1);
  gecen = millis() - baslangic;
  File dataFile = SD.open(str1, FILE_WRITE);
  if (ornek_no == 0)
  {
    dataFile.println(str);
  }

  String olcum = String(ornek_no) + "," + String(a.acceleration.x) + "," + String(a.acceleration.y) + "," + String(a.acceleration.z) + "," + String(gecen) + "\n";
  if (dataFile)
  {
    dataFile.println(olcum);
    dataFile.close();
    Serial.println(olcum);
  }
  // if the file isn't open, pop up an error:
  else
  {
    Serial.println("error opening datalog.txt");
  }

  baslangic = millis();
  ornek_no += 1;
  int x = ThingSpeak.writeField(1789113, 1, a.acceleration.x, "DQWYM7ET7PUDD11W");
  int y = ThingSpeak.writeField(1789113, 2, a.acceleration.y, "DQWYM7ET7PUDD11W");
  int z = ThingSpeak.writeField(1789113, 3, a.acceleration.z, "DQWYM7ET7PUDD11W");
  delay(200);
}
