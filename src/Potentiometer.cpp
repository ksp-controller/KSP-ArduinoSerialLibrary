#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(uint8_t pin, int min, int max)
{
  _pin = pin;
  _min = min;
  _max = max;
}
void Potentiometer::loop()
{
  int readingValue = analogRead(_pin);
  //leap a little rest gap
  _lastValue = max(min(map(readingValue, 40, 1020, _min, _max), _max), _min);
}
int Potentiometer::getCurrentValue()
{
  return _lastValue;
}
