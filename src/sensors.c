#ifndef SENSORS_C
#define SENSORS_C

void* sensorInit() {

}
void sensorUpdate(&sensor) { // updates speed and val
  // speed = (getval - old sensor val) / (get curr time - t)
  // reset val
  // t = getcurr
  int sval;
  if (sensor->analog) {
    sval = analogReadCalibrated(sensor->port);
  } else {
    sval = digitalRead(sensor->port);
  }
  // set speed
  sensor->speed = (sval-sensor->val)/(millis() - sensor->t);

  // update the sensor value
  sensor->val = sval;
  sensor->t = millis();

}
void sensorUpdateVal(&sensor) { // updates just val
  if (sensor->analog) {
    sensor->val = analogReadCalibrated(sensor->port);
  } else {
    sensor->val = digitalRead(sensor->port);
  }

}
#endif
