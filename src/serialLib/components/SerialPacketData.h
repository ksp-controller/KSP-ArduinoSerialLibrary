#ifndef SerialPacketData_h
#define SerialPacketData_h
#include "Arduino.h"
#include "GameDefinitions.h"

class SerialPacketData
{
  public:
    SerialPacketData();
    void loop(); //should be called every arduino loop
    //void getReadData();
    //void setControlData();
  private:
    VesselData _serializedData;
};
#endif
