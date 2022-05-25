/*
 * Bagian PV menampilkan hasil pengukuran ke OLED
 * dan ke Serial plotter
 */

void pvMeasure(unsigned ts) {
  hidro_v = ina219.getBusVoltage_V();
  hidro_ma = ina219.getCurrent_mA();
  hidro_mw = ina219.getPower_mW();

  //Masukan ke array untuk di publish
  inputs[V] = hidro_v*1000; //dikirim ke dashboard dalam satuan mV
  inputs[I] = hidro_ma;
  inputs[P] = hidro_mw;
  inputs[RPM] = motor_rpm;

  //mengukur tegangan V1 dan V2 serta masukan ke data untuk publisher
  load_V1 = analogReadMv(DI0);
  load_V2 = analogReadMv(DI1);
  inputs[V1] = load_V1;
  inputs[V2] = load_V2;

  // hitung total energi
  hidro_joule += hidro_mw * (0.001 * ts); 
}


//-----------------------------
byte chart[D_WIDTH];

// konstanta display OLED
#define CHART_MIN  0
#define CHART_MAX  20
#define CHART_SPAN (CHART_MAX-CHART_MIN)

void pvDisplay() {
  char buff[60];

  // masukkan data ke chart
  for(int i=D_WIDTH-1; i>0;i--) {
    chart[i]= chart[i-1];
  }
  
  // tambah data baru ke chart, konversi
  chart[0] = hidro_mw * CHART_SPAN / PV_MW_SPAN;
  if (chart[0] > CHART_SPAN)
    chart[0] = CHART_SPAN;


  // format tampilan text
  sprintf(buff, "V:%04.2f I:%04.2f P:%05.1f RPM:%d",
    hidro_v, hidro_ma, hidro_mw, motor_rpm);

  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.print(buff);

  if (hidro_display_mode == 0) {
    // plot chart
    for(int i=1; i<D_WIDTH; i++) {
      oled.drawLine(i, D_HEIGHT-chart[i-1], i+1, D_HEIGHT-chart[i], WHITE);
    }
  }
  else {
    // print total energi
    sprintf(buff, "E:%8.1f", hidro_joule);
    oled.setTextSize(2);
    oled.setCursor(0, 12);
    oled.print(buff);
    oled.setTextSize(1);
  }  
  oled.display();


  // tampil ke Serial
  // header
  //sprintf(buff, "V I P E:%8.2f", pv_joule);
  Serial.print(buff);
  // data
  sprintf(buff, " E=%.2f", hidro_joule);
  //sprintf(buff, "%5.3f %5.2f %5.2f", pv_v, pv_ma, pv_mw);
  Serial.println(buff);
}
