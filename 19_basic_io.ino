// Tab program untuk mengatur Input yang bersumber dari subscribe Node-Red


// Kontrol Baterai
const int Bat = DO0;

//Kontrol Load dengan PWM
//#define AO0 26 -> udah didef di depan
// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void ioSetup(){
  pinMode(Bat, OUTPUT);
  digitalWrite(Bat, LOW);
  
  // Konfigurasi pwm
  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(AO0, ledChannel);
}
