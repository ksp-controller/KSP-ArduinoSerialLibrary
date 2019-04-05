#ifndef Potentiometer_h
#define Potentiometer_h
#include "Arduino.h"

class Potentiometer
{
  public:
    Potentiometer(uint8_t pin, int min, int max);
    void loop(); //should be called every arduino loop
    int getCurrentValue();
  private:
    uint8_t _pin; //green light pin location
    int _min, _max;
    int _lastValue; //Voltage last read value
};

#endif
