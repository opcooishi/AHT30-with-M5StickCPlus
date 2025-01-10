// this sample program is for AOSONG AHT30 Humidity sensor + M5StickCP   by okinawanwinds 20250109
// datasheet https://eleparts.co.kr/data/goods_attach/202306/good-pdf-12751003-1.pdf
// Hardware M5StickCPlus, Board type M5StickCPlus-esp32,  Library type M5StickCPlus2

#include <Wire.h>
#include <M5StickCPlus2.h>
#define I2C_DEV_ADDR 0x38

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.setTextSize(4);
  M5.Lcd.setRotation(2);
  delay(100);

  Wire.begin(32,33);  // for M5StickCPlus HAT as 25,26, GroveIO as 32,33,  other arduino uses A4, A5

}
void loop() {
  Wire.beginTransmission( I2C_DEV_ADDR);
  Wire.write(0xAC);
  Wire.write(0x33);
  Wire.write(0x00);  
  Wire.endTransmission();
  delay(100);  
  Wire.beginTransmission( I2C_DEV_ADDR);
  Wire.write(0x71);
  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 7, true);
  if (Wire.available()==7) { 
    uint8_t rd[bytesReceived];
    Wire.readBytes(rd, bytesReceived);
    double temp = ( (rd[3]&0x0F)*65536 + rd[4]*256 + rd[5] ) * 200.0 / pow(2,20) -50;
    double humi = ( rd[1]*4096+rd[2]*16+(rd[3]>>4) )  * 100.0 / pow(2,20);
    M5.Lcd.setCursor(10,20,1);
    M5.Lcd.print("Temp.");
    M5.Lcd.setCursor(10,60,1);
    M5.Lcd.print(temp);
    M5.Lcd.setCursor(10,140,1);
    M5.Lcd.print("Humi.");
    M5.Lcd.setCursor(10,180,1);
    M5.Lcd.print(humi);
    
    Serial.printf("temp %5.2fc    Humi %5.2f%% \n", temp, humi);
  } else Serial.printf("wire error \n");
  delay(1000);
}
