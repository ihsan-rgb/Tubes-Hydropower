/*
 * Program utama 
 */ 


// Timer untuk loop periodik
Periodic hidro_p1(ts_measure);
Periodic hidro_p2(ts_display);
Periodic pView(1000);

Button btn1(BT1);

void setup() {
  Serial.begin(BAUD);    
  delay(3000);
  Serial.println();
  Serial.println(PROG_NAME);
  delay(3000);

  escopeSetup();
  optoSetup();
  hidro_joule = 0;

  ioSetup();
  //Connect Wifi
  if (wifiSetup() == E_OK) {
    wifiPrintMacAddress();
    wifiPrintIP();
    mqttSetup();  
  }
}

void loop() {
  if (hidro_p1.isTime()) {
    pvMeasure(hidro_p1.getPeriode());
  }
  else if (hidro_p2.isTime()) {
    motor_rpm = optoGetRPM();
    pvDisplay();   
    mqttLoop(); 
  }
  else if (btn1.pressed()) {
    // toggle mode
    hidro_display_mode = 1-hidro_display_mode;
  }
  wifiLoop();
}
