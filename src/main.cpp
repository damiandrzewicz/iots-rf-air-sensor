#include <Arduino.h>
#include "RFAirSensorNode.h"

RFAirSensorNode node;

void setup() 
{     
  Serial.begin(38400);
  node.setup();
}

void loop() 
{
  node.loop();
}