
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
  
  Serial.begin(57600);
}

bool sent = false;
int val = 65;

void loop() {
  while ( ble_available() ) {
    Serial.write(ble_read());
    sent = true;
  }
    
  if (sent) {
    delay(500);
    ble_write(val);
    ++val;
    if (val > 90) {
      val = 65;
    }
    ble_write('\r');
    ble_write('\n');
    delay(500);
    sent = false;
  }
    
  ble_do_events();
}

