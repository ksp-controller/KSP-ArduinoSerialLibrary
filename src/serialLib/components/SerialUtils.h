#ifndef SerialUtils_h
#define SerialUtils_h
#include "./../GameDefinitions.h"

static uint8_t packetChecksum(byte payload[],uint8_t length) {
  uint8_t verifier = length;
  for (int i = 0; i < length; i++) verifier ^= payload[i];
  return verifier;
};
static bool writeControllerPacket(uint8_t* payloadAddr, uint8_t length) {
  if (!Serial.availableForWrite()) return false;
  uint8_t verifier = length; //will change it on for loop
  Serial.write(PACKET_ACK);
  Serial.write(PACKET_VERIFIER);
  Serial.write(length);
  for (int i = 0; i < length; i++) {
    verifier ^= *(payloadAddr+i);
    Serial.write( *(payloadAddr+i) );
  } Serial.write(verifier);
  Serial.flush();
  return true;
};
static uint8_t sendDebugMessage(String message) {
  if (!Serial.availableForWrite()) return;
  //
  byte payload[message.length()];
  message.getBytes(payload, message.length());
  //
  uint8_t verifier = message.length();
  Serial.write(PACKET_ACK);
  Serial.write(PACKET_VERIFIER);
  Serial.write(verifier); //still can use verifier at this point
  for (int i = 0; i < message.length(); i++) {
    verifier ^= payload[i];
    Serial.write(payload[i]);
  } Serial.write(verifier);
  Serial.flush();
  free(payload);
};
#endif
