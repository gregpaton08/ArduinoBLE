
#include <Arduino.h>
#include <SPI.h>
#include "ble.h"
#include "OBDLib.h"

OBDLib obd;

void setup() {
  // set up Serial Peripheral Interface
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();
  
  ble_begin();
  
  Serial.begin(38400);
  
  //while (false == obd.init());
}

unsigned char val = 65;
unsigned char len;
bool sent = false;
unsigned long time;

void loop() {
  len = 0;
  sent = false;
  
  while (ble_available() > 0) {
    unsigned char c = ble_read();
    Serial.write(c);
    if (c == '\n') {
      sent = true;
      break;
    }
  }
  
  if (sent) {
    // wait for data to become available
    time = millis();
    while (millis() - time < 1000 && Serial.available() == 0);
    
    while (Serial.available() > 0) {
      unsigned char c = Serial.read();
      ble_write(c);
      // allow only alphanumeric and white space input
      /*if ((c > 64 && c < 91) || (c > 47 && c < 58) 
          || (c > 69 && c < 123) || c == 32) {
        ble_write(c);
      }*/
    }
  }
    
  ble_do_events();
}

