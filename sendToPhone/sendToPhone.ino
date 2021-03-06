
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
}

unsigned char buf[16] = {0};
unsigned char len = 0;
int i = 0;

void loop() {
  while (i % 10 != 0) {
    ble_write(i);
    ble_write('\r');
    ble_write('\n');
    ++i;
  }
  
  ble_do_events();
  ++i;
  
  if (i > 255) {
    i = 0;
  }
  
  delay(200);
}

