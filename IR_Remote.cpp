#include "IR_Remote.h"
#include <Arduino.h>

IRRecv::IRRecv(uint8_t pin) {
  irRecvPin = pin;
}

void IRRecv::begin() {
  pinMode(irRecvPin, INPUT_PULLUP);
}

int16_t IRRecv::recvRaw(uint16_t buf[], uint32_t timeout) {
  
  uint16_t sira = 0;
  
  //while (sira < 32) {
	  
	sira = 0;
	  
	uint32_t kapatma_bas_zaman = millis();
    uint32_t kapatma_zaman_fark = millis() - kapatma_bas_zaman;
  
    while (digitalRead(irRecvPin) and kapatma_zaman_fark < timeout) kapatma_zaman_fark = millis() - kapatma_bas_zaman;

    if (kapatma_zaman_fark >= timeout) {
      return -1;
    }
  
    uint32_t bas_zaman = micros();
    uint32_t zaman_fark = micros() - bas_zaman;
    while (not digitalRead(irRecvPin)) zaman_fark = micros() - bas_zaman;
    buf[sira] = zaman_fark;
    sira++;
  
    while (true) {
    
      bas_zaman = micros();
      zaman_fark = micros() - bas_zaman;
      while (digitalRead(irRecvPin) and zaman_fark < 1000000) zaman_fark = micros() - bas_zaman;
      if (zaman_fark >= 1000000) break;
      buf[sira] = zaman_fark;
      sira++;
    
      bas_zaman = micros();
      zaman_fark = micros() - bas_zaman;
      while (not digitalRead(irRecvPin)) zaman_fark = micros() - bas_zaman;
      buf[sira] = zaman_fark;
      sira++;
    }
  //}

  return sira;
}

IRSend::IRSend(uint8_t pin) {
  irSendPin = pin;
}

void IRSend::begin() {
  pinMode(irSendPin, OUTPUT);
  digitalWrite(irSendPin, LOW);
}

void IRSend::sendRaw(uint16_t buf[], uint16_t len, uint16_t hz) {
  
  if (hz < 1000) hz *= 1000;
  if (hz == 0) hz = 1;
  
  uint32_t period = (1000000 + hz / 2) / hz;
  period = max((uint32_t)1, period - 1);
  uint32_t onTimePeriod = period / 2;
  uint32_t offTimePeriod = period - onTimePeriod;
  
  for (uint16_t i = 0; i < len; i++) {
    
    if (i & 1) {
      digitalWrite(irSendPin, LOW);
      //if (buf[i] == 0) return;
      delayMicroseconds(buf[i]);
    }
    
    else {
      
      uint32_t begin_time = micros();
      uint32_t elapsed_time = micros() - begin_time;
      
      while (elapsed_time < buf[i]) {
        digitalWrite(irSendPin, HIGH);
        delayMicroseconds(min((uint32_t)onTimePeriod, buf[i] - elapsed_time));
        digitalWrite(irSendPin, LOW);
        delayMicroseconds(min(buf[i] - elapsed_time - onTimePeriod, (uint32_t)offTimePeriod));
        elapsed_time = micros() - begin_time;
      }
    }
  }
  
  digitalWrite(irSendPin, LOW);
}
