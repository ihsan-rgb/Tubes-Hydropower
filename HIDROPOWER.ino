/* Program : IOT - PLTA HMI in Node-RED 
 * Membaca V,I dan P dari PLTA serta V1 dan V2 pada load
 * Mengatur Koneksi Baterai Ke rangkaian
 * Mengatur kecerahan LED 
 * Creator : Ihsan M. Fauzan, Timothy Taro Tarigan
 * Mengambil referensi sebagian besar dari Kode Modul 05 (Optocoupler) dan Modul 06
 * © Eko M.B
 * © Abdul Ghani
 */

// pustaka
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TFPeriodic.h>
#include <Button.h>
#include <TFPeriodic.h>
#include <TFRingBuffer.h>

#define BAUD 500000
#define PROG_NAME "Hydropower"
#define PROG_VERSION  "1.0"

#define NODE "K1-03" //Ganti dengan Regu/NIM anda
