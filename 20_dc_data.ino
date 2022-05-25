/*
 * Data untuk DC motor dan Opto Coupler
 */

// pin yang digunakan

int pin_opto = DI2;

// variabel kontrol/pengukuran motor

int motor_rpm = 0;

// variabel pengukuran opto_coupler
portMUX_TYPE opto_mux = portMUX_INITIALIZER_UNLOCKED;
volatile unsigned opto_counter = 0;
unsigned long opto_last_time = 0;

// periode task 
unsigned ts_measure = 100;
unsigned ts_display = 1000;
