
#include <Arduino.h>
#include <SPI.h>
#include "ble.h"

void setup() {
  // set up Serial Peripheral Interface
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();
  
  ble_begin();
  
  Serial.begin(38400);
}

void loop() {
  while (ble_available() > 0) {
    unsigned char c = ble_read();
    Serial.write(c);
    if (c == '\n') {
      break;
    }
  }
  
  while (Serial.available() > 0) {
    unsigned char c = Serial.read();
    ble_write(c);  
  }
  
  ble_do_events();
}

