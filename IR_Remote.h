#ifndef IR_REMOTE
#define IR_REMOTE

#include <stdint.h>

class IRRecv {

  public:
    IRRecv(uint8_t pin);
    void begin();
    int16_t recvRaw(uint16_t buf[], uint32_t timeout = 30000);
  
  private:
    uint8_t irRecvPin;
};

class IRSend {

  public:
    IRSend(uint8_t pin);
    void begin();
    void sendRaw(uint16_t buf[], uint16_t len, uint16_t hz = 50);

  private:
    uint8_t irSendPin;
};

#endif
