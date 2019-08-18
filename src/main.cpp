#include <Arduino.h>

// undef min and max (from Arduino.h) because they are defined in memory.h
#undef max
#undef min
#include <memory>

#include "M30Z134/m30z134Reader.h"

namespace {
  std::unique_ptr<M30Z134Reader> reader;
}

void setup() {
  // for communicating to the host
  Serial1.begin(19200);
  // for communication to the rfid 
  Serial1.begin(9600);

  // setup the reader
  reader = std::unique_ptr<M30Z134Reader>(new M30Z134Reader(Serial1));

}

void loop() {
  reader->activateField();
}