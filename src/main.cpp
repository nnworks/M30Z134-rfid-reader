#include <Arduino.h>

#include "M30Z134/m30z134Reader.h"

void setup() {
  // for communicating to the host
  Serial1.begin(19200);
  // for communication to the rfid 
  Serial1.begin(9600);
}

void loop() {
}