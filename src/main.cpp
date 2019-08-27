#include <Arduino.h>


#include "M30Z134/m30z134Reader.h"

using namespace nnworks::m30z134reader;

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

  reader->createRequestMessage(0x1234, std::shared_ptr<std::vector<uint8_t>>(new std::vector<uint8_t>()));
  M30Z134Reader::ResponseMessage(std::shared_ptr<std::vector<uint8_t>>(new std::vector<uint8_t>()));
}

void loop() {
  reader->activateField();
}