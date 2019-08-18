
#include <Arduino.h>
#include "m30z134Reader.h"

M30Z134Reader::M30Z134Reader(USARTClass serial) {

}


M30Z134Reader::~M30Z134Reader() {

}

std::unique_ptr<M30Z134Reader::m_message> M30Z134Reader::createCommandMessage(uint16_t command, uint8_t* parameters) {
  
  return nullptr;
}

boolean M30Z134Reader::activateField(void) {
  return false;
}

u_int8_t M30Z134Reader::getByte(void) {
  return 0;
}

