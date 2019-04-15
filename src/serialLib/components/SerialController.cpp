#include "Arduino.h"
#include "./../SerialController.h"

SerialController::SerialController()
{
  //setup
  _receivedBytes = 0;
  _incomePacketSize = 0;
  _lastSentStamp = -1;
  _lastControlsIsValid = false;
  _lastData = VesselData();
  //
  Serial.begin(SERIAL_BAUDRATE);
}
// Public methods
VesselData SerialController::getVesselData() { return _lastData; }
void SerialController::setVesselControls(SerializedVesselControls controls) {
  _lastControls = controls; //SerializedVesselControls
  _lastControlsIsValid = true;
}
void SerialController::loop()
{
  this->_receivedData();
  this->_sendData();
}



void SerialController::_receivedData() {
  //initial read
  if (_incomePacketSize == 0 && Serial.available() >= PACKET_HEADER_SIZE) {
    if (this->_readIncomeHeader()) {
       this->_readIncomePacket(); //READ MORE OF THE PACKET?
    } else Serial.println("Income header errored!");
  } else if (_incomePacketSize != 0) this->_readIncomePacket();
}
bool SerialController::_readIncomeHeader() {
  //while we dont have ACK keep trying
  while (Serial.available() > 0 && Serial.read() != PACKET_ACK);
  //check header verifier
  if (Serial.available() <= 0 || Serial.read() != PACKET_VERIFIER) return false;
  //read size, check if it's the same and expected struct
  _incomePacketSize = (uint8_t)Serial.read();
  if (_incomePacketSize != sizeof(_lastData)) {
    _incomePacketSize = 0; //reset
    return false;
  }
  _receivedBytes = 0; //cleanup for new receive
  return true;
}
void SerialController::_readIncomePacket() {
  if (!_incomePacketSize) return;
  //try to read data from buffer till reach the expected size
  while (Serial.available() > 0 && _receivedBytes <= _incomePacketSize) {
    _receivedPayload[_receivedBytes] = Serial.read();
    _receivedBytes++;
  }
  //check if received the full message
  if ((_receivedBytes-1) == _incomePacketSize) {
    //generate checksum
    uint8_t checksum = packetChecksum(_receivedPayload,_incomePacketSize);
    //check if checksum matches with last received payload byte
    if (checksum == _receivedPayload[(_receivedBytes-1)]) {
      memcpy((uint16_t*)&_lastData, _receivedPayload, _incomePacketSize);
    } else Serial.println("Checksum failed!");
    //reset for next receive
    _receivedBytes = 0;
    _incomePacketSize = 0;
  } //else body still been built
}


void SerialController::_sendData() {
  if (_lastControlsIsValid == true &&
      (millis() - _lastSentStamp > SERIAL_THREAD_FREQUENCY || _lastSentStamp == -1)) { this->_sendLastControls(); }
}
void SerialController::_sendLastControls() {
  if (writeControllerPacket((uint8_t*)&_lastControls, sizeof(_lastControls))) {
    _lastControlsIsValid = false;
    _lastSentStamp = millis();
  }
}
