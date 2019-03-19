#ifndef SerialController_h
#define SerialController_h
#include "Arduino.h"
#include "./components/SerialUtils.h"
#include "./components/GameDefinitions.h"

class SerialController
{
  public:
    SerialController();
    void loop(); //should be called every arduino loop
    //void getReadData();
    //void setControlData();
    VesselData lastData;

  private:
    //Income handling
    uint8_t _incomePacketSize; //expected size for packet
    uint8_t _receivedBytes; //actual received
    byte _receivedPayload[MAX_PACKET_SIZE];
    void _receivedData();
    bool _readIncomeHeader();
    void _readIncomePacket();
};
#endif
