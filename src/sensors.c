#ifndef SENSORS_C
#define SENSORS_C

void* sensorInit(int portin, float scalingFactorin, int analogin) {
  Sensor s = malloc(sizeOf(Sensor)); // pointer, memory allocation
  s->port = portin;
  s->raw = 0;
  s->val = 0;
  s->speed = 0;
  s->t = 0;
  s->scalingFactor = scalingFactorin;
  s->analog = analogin;
  return s;

}

void sensorUpdate(&sensor) { // updates speed and val
  // speed = (getval - old sensor val) / (get curr time - t)
  // reset val
  // t = getcurr
  int rawSval;
  int sval;

  if (sensor->analog) {
    rawSval = analogReadCalibrated(sensor->port);
    sval = analogReadCalibrated(sensor->port)*sensor->scalingFactor;
  } else {
    rawSval = digitalRead(sensor->port);
    sval = digitalRead(sensor->port)*sensor->scalingFactor;
  }
  // set speed
  sensor->speed = (sval-sensor->val)/(millis() - sensor->t);

  // update the sensor value
  sensor->raw = rawSval;
  sensor->val = sval;
  sensor->t = millis();

}
void sensorUpdateVal(&sensor) { // updates just val
  if (sensor->analog) {
    sensor->raw = analogReadCalibrated(sensor->port);
    sensor->val = analogReadCalibrated(sensor->port)*sensor->scalingFactor;
  } else {
    sensor->raw = digitalRead(sensor->port);
    sensor->val = digitalRead(sensor->port)*sensor->scalingFactor;
  }

}
void sensorReset() {
  for(int n = 1; n < 27; n++){
    digitalWrite(n, false);
  }
  for(int m = 0; m < IME_ADDR_MAX; m++){
    imeReset(m);
  }
}

#endif
