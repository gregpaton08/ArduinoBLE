
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
  
  Serial.write("ATE0\r");
  //obd.init();
  delay(1000);
  
  Serial.begin(38400);
}

void loop() {
  while (ble_available() > 0) {
    unsigned char c = ble_read();
    Serial.write(c);
    if (c == '\r') {
      // Wait for serial data
      while (Serial.available() == 0);
  
      while (true) {
        unsigned char c = Serial.read();
        if (c == 'E' || c == 'S') {
          while (false == Serial.find(">"));
          break;
        }
        if (c == (unsigned char)-1) continue;
        if (c == '\n' || c == '\r') break;
        ble_write(c);  
      }
      break;
    }
  }
  
  ble_do_events();
}

