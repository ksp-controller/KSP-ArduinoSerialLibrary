#include <Arduino.h>
#include "./serialLib/SerialController.h"
#include "./Potentiometer.h"
static SerialController *serialCom;
static Potentiometer *throttle;
#define PIN1 20
#define PIN2 21

void setup() {
  serialCom = new SerialController();
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  throttle = new Potentiometer(A2,0,1000);
}
//get the current state of main controls and custom action groups using enumeration above, e.g. ControlStatus(AGBrakes);
byte GetControlStatus(VesselData data, byte n)
{
  return ((data.ActionGroups >> n) & 1) == 1;
}
void loop() {
  serialCom->loop();
  if (GetControlStatus(serialCom->getVesselData(), RCS) == 1) {
    digitalWrite(PIN1, HIGH);
  }else {
    digitalWrite(PIN1, LOW);
  }
  if (GetControlStatus(serialCom->getVesselData(), SAS) == 1) {
    digitalWrite(PIN2, HIGH);
  }else {
    digitalWrite(PIN2, LOW);
  }

  throttle->loop();
  SerializedVesselControls *control = new SerializedVesselControls();
  control->Throttle = throttle->getCurrentValue();
  serialCom->setVesselControls(*control);
}
