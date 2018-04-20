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
void sensorReset() {
  for(int n = 0; n < 26; n++){
    digitalWrite(n, false);
  }
  for(int m = 0; m < IME_ADDR_MAX; m++){
      imeReset(m);
  }
}
