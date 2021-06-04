#include <ps4.h>

// TODO
// pass Wire instance in constructor
// support serial comms with USB hub



void setup() {
  Serial.begin(115200);
  Wire.begin();
  ps4::init(&Wire);
}

void loop() {
  ps4::fetchData();
  delay(100);
  ps4::printData(&Serial);
}
