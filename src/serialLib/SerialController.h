#ifndef SerialController_h
#define SerialController_h
#include "Arduino.h"
#include "./components/SerialUtils.h"
#include "./GameDefinitions.h"

class SerialController
{
  public:
    SerialController();
    void loop(); //should be called every arduino loop
    VesselData getVesselData();
    void setVesselControls(VesselControls controls);
  private:
    //data
    VesselData _lastData;
    SerializedVesselControls _lastControls;
    bool _lastControlsIsValid;
    //Income handling
    uint8_t _incomePacketSize; //expected size for packet
    uint8_t _receivedBytes; //actual received
    byte _receivedPayload[MAX_PACKET_SIZE];
    void _receivedData();
    bool _readIncomeHeader();
    void _readIncomePacket();
    void _sendData();
    void _sendLastControls();
};
#endif
