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
  _lastValue = map(readingValue, 540, 1024, _min, _max);
}
int Potentiometer::getCurrentValue()
{
  return _lastValue;
}
