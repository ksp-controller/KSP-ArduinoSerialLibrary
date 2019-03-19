#ifndef SerialUtils_h
#define SerialUtils_h

static uint8_t packetChecksum(byte payload[],uint8_t length) {
  uint8_t verifier = length;
  for (int i = 0; i < length; i++) verifier ^= payload[i];
  return verifier;
};

#endif
