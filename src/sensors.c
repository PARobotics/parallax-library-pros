void sensorInit(){

}
void sensorUpdate(&Sensor) { // updates speed and val
}
void sensorUpdateVal(&Sensor) { // updates just val

}
void sensorReset() {
  for(int n = 0; n < 26; n++){
    digitalWrite(n, false);
  }
  for(int m = 0; m < IME_ADDR_MAX; m++){
      imeReset(m);
  }
}
