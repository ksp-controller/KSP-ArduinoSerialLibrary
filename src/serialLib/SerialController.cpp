#include "Arduino.h"
#include "SerialController.h"

SerialController::SerialController()
{
  _receivedBytes = 0;
  _incomePacketSize = 0;
  Serial.begin(9600);
}
void SerialController::loop()
{
  this->_receivedData();
}
void SerialController::_receivedData() {
  //initial read
  if (_incomePacketSize == 0 && Serial.available() >= PACKET_HEADER_SIZE) {
    if (this->_readIncomeHeader()) {
       this->_readIncomePacket(); //READ MORE OF THE PACKET?
    }else {
       Serial.println("Income header errored!");
    }
  }
  else if (_incomePacketSize != 0) {
    // Serial.println("Income body received with success!");
    this->_readIncomePacket();
  }
}

bool SerialController::_readIncomeHeader() {
  //
  while (Serial.available() > 0 && Serial.read() != PACKET_ACK);
  //
  if (Serial.available() <= 0 || Serial.read() != PACKET_VERIFIER) return false;
  //
  _incomePacketSize = (uint8_t)Serial.read();
  lastData = VesselData();
  if (_incomePacketSize != sizeof(lastData)) {
    _incomePacketSize = 0;
    return false;
  }
  //cleanup for new receive
  _receivedBytes = 0;
  return true;
}
void SerialController::_readIncomePacket() {
  if (!_incomePacketSize) return;
  //try to read data from buffer
  while (Serial.available() && _receivedBytes <= _incomePacketSize) {
    _receivedPayload[_receivedBytes] = Serial.read();
    _receivedBytes++; //cant use received byte after here
  }
  //check if received the full message
  if ((_receivedBytes-1) == _incomePacketSize) {
    //generate checksum
    uint8_t checksum = packetChecksum(_receivedPayload,_incomePacketSize);
    //check if checksum matches with last received payload byte
    if (checksum == _receivedPayload[(_receivedBytes-1)]) {
      memcpy((uint16_t*)&lastData, _receivedPayload, _incomePacketSize);
    }else {
      Serial.println("Checksum failed!");
    }
    _receivedBytes = 0;
    _incomePacketSize = 0;
  }else {
     //Serial.println("Incomplete body!");
  }
}
