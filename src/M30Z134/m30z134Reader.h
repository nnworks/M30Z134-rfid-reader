#ifndef M30Z134Reader_H
#define M30Z134Reader_H

#include <Arduino.h>
// undef min and max (from Arduino.h) because they are defined in memory.h
#ifdef min
    #undef min
#endif
#ifdef max 
  #undef max
#endif

#include <stdint.h>
#include <vector>
#include <memory>

namespace nnworks {
namespace m30z134reader {

  class M30Z134Reader {

    using v_ui8 = std::vector<uint8_t>;
    using up_v_ui8 = std::unique_ptr<v_ui8>;
    using sp_v_ui8 = std::shared_ptr<v_ui8>;

    private:
      /**
       * RequestMessage class containing a request for the RFID reader
       * Header(16) | Length(16) | Device identifier code(16) | Command(16) | Parameters(n*8) | Checksum(8)
       */
      class RequestMessage {
        public:
          uint16_t m_header = 0xAABB;
          uint16_t m_length;
          uint16_t m_deviceId = 0x0000;
          uint16_t m_command;
          up_v_ui8 m_parameters;
          uint8_t  m_paramSize;
          uint8_t  m_checksum;

          // constructor
          RequestMessage(uint16_t command, sp_v_ui8 parameters);

          up_v_ui8 serializeMessage(void);
      };

    public: // for test

      std::unique_ptr<RequestMessage> createRequestMessage(uint16_t command, sp_v_ui8 parameters);


    public:
      /**
       * Constructor 
       */
      M30Z134Reader(USARTClass serial);

      /**
       * Destructor
       */
      ~M30Z134Reader();


      /**
       * RequestMessage class containing a request for the RFID reader
       * Header(16) | Length(16) | Device identifier code(16) | Command(16) | Parameters(n*8) | Checksum(8)
       */
      class ResponseMessage {
        private:
          uint16_t m_header;
          uint16_t m_length;
          uint16_t m_deviceId;
          uint16_t m_command;
          uint8_t  m_status;
          sp_v_ui8 m_answer;
          uint8_t  m_paramSize;
          uint8_t  m_checksum;

          std::unique_ptr<ResponseMessage> deserializeMessage(sp_v_ui8 response);

        public:
          // constructor
          ResponseMessage(sp_v_ui8 responseData);
      };

      /**
       * Get the type and serial number of the reader
       */
      std::unique_ptr<ResponseMessage> getReaderInfo(void);

      /**
       * Turn the electromagnetic field on to activate the RFID device
       */
      boolean activateField(void);

      /**
       * Switch LED on or of
       */
      std::unique_ptr<ResponseMessage> switchLed(boolean on);

      /**
       * Read the ID
       */
      std::unique_ptr<ResponseMessage> readId();
  };

}

}

#endif