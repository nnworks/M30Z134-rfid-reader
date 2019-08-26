
#include "m30z134Reader.h"

// constructor
M30Z134Reader::M30Z134Reader(USARTClass serial) {

}

// destructor
M30Z134Reader::~M30Z134Reader() {

}

std::unique_ptr<M30Z134Reader::RequestMessage> M30Z134Reader::createRequestMessage(uint16_t command, sp_v_ui8 parameters) {  
  std::unique_ptr<RequestMessage> message = std::unique_ptr<RequestMessage>(new RequestMessage(command, parameters));

  return message;
}

boolean M30Z134Reader::activateField(void) {
  return false;
}

M30Z134Reader::RequestMessage::RequestMessage(uint16_t command, sp_v_ui8 parameters) {
  m_command = command;

  if (parameters->size() > 0) {
    // create unique_ptr to vector with copy of parameters
    m_parameters = up_v_ui8(new std::vector<uint8_t>(*parameters));
  } else {
    m_parameters = nullptr;
  }
}

M30Z134Reader::up_v_ui8 M30Z134Reader::RequestMessage::serializeMessage(void) {
  uint8_t size = sizeof(m_header) + sizeof(m_length) + sizeof(m_deviceId) + sizeof(m_command) + sizeof(m_paramSize) + sizeof(m_checksum);
  
  up_v_ui8 bufferPtr = up_v_ui8(new std::vector<uint8_t>(size));
  std::vector<uint8_t> buffer = *bufferPtr;
  buffer[0] = 0xAA;
  buffer[1] = 0xBB;
  buffer[2] = size;
  buffer[3] = 0x00;
  
  return bufferPtr;
}

M30Z134Reader::ResponseMessage::ResponseMessage(sp_v_ui8 responseData) {
  deserializeMessage(responseData);
}

std::unique_ptr<M30Z134Reader::ResponseMessage> M30Z134Reader::ResponseMessage::deserializeMessage(sp_v_ui8 response) {
  return nullptr;
}
