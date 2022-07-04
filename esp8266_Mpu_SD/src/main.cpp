#include <Arduino.h>
#include <Print.h>
#include"SD.h"
#include "SPI.h"
#include"RTClib.h"
//#include"EEPROM.h"
/*RTC_DS1307 rtc;*/
RTC_DS1307 rtc;
/*char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};*/
char daysOfTheWeek[7][12]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define OFFSET 0
#define sleepPeriod 10000000ul
#define CS_PIN  D8
String dosya;
int16_t cal1;
int16_t cal2;
int16_t cal3;
int16_t acc;
String sutun1 = "Örnek_Sayısı";
String sutun2 = "AC_akım1";
String sutun3 = "DC akım1";
String sutun4 = "AC_akım2";
String sutun5 = "DC akım2";
String sutun6 = "AC_akım3";
String sutun7 = "DC_akım3";
String sutun8 = "gecen_Sure_ms";
String str = sutun1 + "," + sutun2 + "," + sutun3 + "," + sutun4 + "," + sutun5 + "," + sutun6 + "," + sutun7+","+sutun8+"\n\n";
uint16_t dosya_no;
uint16_t ornek_no;
String dosya_adi;
int address=0;
int address_1;
String str1;
uint32_t baslangic;
uint32_t gecen;


void setup()
{
  ornek_no=1;
  Serial.begin(115200);
  /// ACS
 
  
  ///EEPROM
  /*if (!EEPROM.begin(1000)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }*/
  /*if (!EEPROM.begin(1000))
  {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }
  address_1=address+sizeof(int);*/
  

  //dosya_no=EEPROM.readUInt(address);
  dosya_adi="/akim_data"+String(dosya_no);

 
  

 
  if (!SD.begin(CS_PIN))
  {
    Serial.println("Card mount failed");
    return;
  }
  
  //createDir(SD, dosya_adi.c_str());
  str1="/"+dosya_adi+".txt";

 
  //appendFile(SD, "/hello.txt", "World!\n");
  dosya_no=dosya_no+1;
  //Serial.printf("Dosya No:%s",dosya_no);
  //EEPROM.writeUInt(address,dosya_no);
  //EEPROM.commit();
  Serial.println(dosya_no);
}

void loop()
{
   
  Serial.println(address_1);
  gecen=millis()-baslangic;
  /*  String olcum=String(ornek_no)+","+String(acs712_1.getCurrentAC())+","+String(acs712_1.getCurrentDC())+","+String(acs712_2.getCurrentAC())+","+String(acs712_2.getCurrentDC())
  +","+String(acs712_3.getCurrentAC())+","+String(acs712_3.getCurrentDC())+","+String(gecen)+"\n";*/


  
  //appendFile(SD,str1.c_str(), olcum.c_str());
  // appendFile(SD, str1.c_str(), str.c_str());
  //Serial.println(olcum);
  //Serial.println(EEPROM.readUInt(address));
  
  Serial.println("gecen :");
  Serial.println(gecen);
  baslangic=millis();
  ornek_no+=1;

  delay(300);

}
