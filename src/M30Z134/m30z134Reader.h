#ifndef M30Z134Reader_H
#define M30Z134Reader_H

#include <Arduino.h>
#include <stdint.h>
#include <memory>

class M30Z134Reader {
    private:

      /**
       * Header(16) | Length(16) | Device identifier code(16) | Command(16) | Parameters(n*8) | Checksum(8)
       */
      struct m_message {
          uint16_t header = 0xAABB;
          uint16_t length;
          uint16_t deviceId = 0x0000;
          uint16_t command;
          uint8_t* parameters;
          uint8_t checksum;
      };

      std::unique_ptr<m_message> createCommandMessage(uint16_t command, uint8_t* parameters);
      
    public:
      M30Z134Reader(USARTClass serial);
      ~M30Z134Reader();
      boolean activateField(void);
      u_int8_t getByte(void);
};

#endif