#include <Arduino.h>
#include "./serialLib/SerialController.h"
static SerialController *serialCom;

void setup() {
  serialCom = new SerialController();
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}
//get the current state of main controls and custom action groups using enumeration above, e.g. ControlStatus(AGBrakes);
byte GetControlStatus(VesselData data, byte n)
{
  return ((data.ActionGroups >> n) & 1) == 1;
}
void loop() {
  serialCom->loop();
  if (serialCom->getVesselData().Vsurf > 1.0) {
    digitalWrite(6, HIGH);
  }else {
    digitalWrite(6, LOW);
  }
  if (GetControlStatus(serialCom->getVesselData(), SAS) == 1) {
    digitalWrite(7, HIGH);
  }else {
    digitalWrite(7, LOW);
  }
}
