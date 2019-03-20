#ifndef SerialUtils_h
#define SerialUtils_h
#include "./../GameDefinitions.h"

static uint8_t packetChecksum(byte payload[],uint8_t length) {
  uint8_t verifier = length;
  for (int i = 0; i < length; i++) verifier ^= payload[i];
  return verifier;
};
static uint8_t writePacket(uint8_t* payloadAddr, uint8_t length) {
  uint8_t verifier = length;
  Serial.write(PACKET_ACK);
  Serial.write(PACKET_VERIFIER);
  Serial.write(length);
  for (int i = 0; i < length; i++) {
    verifier ^= *(payloadAddr+i);
    Serial.write( *(payloadAddr+i) );
  } Serial.write(verifier);
};
#endif
