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
  hidro_joule = 0; //tampilan energi
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
    motor_rpm = optoGetRPM(); // Mendapatkan nilai RPM dari fungsi get RPM yang dijalankan
    pvDisplay(); // Menampilkan data ke Serial Monitor dan juga HMI  
    mqttLoop(); // Mengatur flow data masuk-keluar dari node-red
  }
  else if (btn1.pressed()) { //Apabila tombol ditekan akan menampilkan hasil pengukuran di serial monitor antara PVI dan Energi
    // Kurang berguna karena sejatinya tidak ada interaksi fisik dengan escope
    // toggle mode
    hidro_display_mode = 1-hidro_display_mode;
  }
  wifiLoop();
}
