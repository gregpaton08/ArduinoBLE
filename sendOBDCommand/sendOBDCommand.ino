
#include <Arduino.h>
#include <SPI.h>
#include "ble.h"
#include <EEPROM.h>

void setup() {
  // set up Serial Peripheral Interface
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();
  
  ble_begin();
  
  Serial.begin(38400);
}

//bool sent = false;
unsigned char val = 65;
unsigned char len = 0;
bool rec = false;
unsigned char a = 0;

void loop() {
  while (ble_available()) {
    unsigned char c = ble_read();
    //if (c > 64 && c < 91) {
      Serial.write(c);
      rec = true;
    //}
    //sent = true;
  }
  if (rec) {
    Serial.write('\r');
    Serial.write('\n');
  }
  
  while (rec && Serial.available() > 0) {
    unsigned char c = Serial.read();
    /*if (c == '>') {
      Serial.write("01 0c\r");
      delay(500);
    }*/
    EEPROM.write(a, c);
    ++a;
    if (a > 1023) {
      a = 0;
    }
    ble_write(c);
    //delay(200);
  }
  
  rec = false;
    
  ble_do_events();
}

