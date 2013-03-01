
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

unsigned char val = 65;
unsigned char len = 0;

void loop() {
  while (ble_available() > 0) {
    Serial.write(ble_read());
  }
  
  delay(50);
  
  while (Serial.available() > 0) {
    unsigned char c = Serial.read();
    
    // allow only alphanumeric and white space input
    if ((c > 64 && c < 91) || (c > 47 && c < 58) 
        || (c > 69 && c < 123) || c == 32) {
      ble_write(c);
    }
  }
    
  ble_do_events();
}

