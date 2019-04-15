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
    void setVesselControls(SerializedVesselControls controls);
  private:
    //Receiive handling
    SerializedVesselControls _lastControls;
    bool _lastControlsIsValid;
    unsigned long _lastSentStamp;//
    //Income handling
    VesselData _lastData;
    uint8_t _incomePacketSize; //expected size for packet
    uint8_t _receivedBytes; //actual received
    byte _receivedPayload[MAX_PACKET_SIZE];
    //Income methods
    void _receivedData();
    bool _readIncomeHeader();
    void _readIncomePacket();
    //Receive methods
    void _sendData();
    void _sendLastControls();
};
#endif
