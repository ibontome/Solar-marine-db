#include <MapFloat.h>
#include <Servo.h>
#include <Wire.h>
#include <Ewma.h>
#include <EwmaT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
unsigned long previousMillis = 0;
const long interval = 1000;
float corrientetotal;
float voltage = 0;
int corriente2 = 0;
int corriente1 = 0;
int power;
float corrienteTotal = 0;
int power_before;
float pwm  ;
Adafruit_BNO055 bno = Adafruit_BNO055(55);
int rcPins[6] = {6, 7};
int hasiera;
int pote;
int angeluak;
int iChannel;
int diferentzia;
int direkzioa;
int posizioa;
float Vel;
float chValue[6];
float sensorValue1 = 0;// Voltaje2 medicion de corriente en A1
const int pulseInDelay = 20000;
Servo ESC1;
Servo ESC2;
Ewma adcFilter1(0.01);   // Less smoothing - faster to detect changes, but more prone to noise
Ewma adcFilter2(0.01);  // More smoothing - less prone to noise, but slower to detect changes
void setup() {
  Serial.begin(9600);
  ESC1.attach(9, 1000, 2000); // (pin, min pulse width, max pulse width in microseconds)
  ESC2.attach(10, 1000, 2000); // (pin, min pulse width, max pulse width in microseconds)
  delay(5000);
  pwm = 60;
}
float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void loop() {
  motorra();
  //mandoa();
  //pot();
  //iparorratza();
 // Serial.println(angeluak);
 // delay(1000);

}

void pot() {
   while (Serial.available() > 0) {
    delay(100);
    String irakurri = Serial.readString();
    int ant_bru = irakurri.indexOf("gradN360: ");
    int pos_bru = irakurri.indexOf("brujula:");
    String bruj = irakurri.substring(ant_bru + 10 , pos_bru);
    posizioa = bruj.toInt();
    Serial.println(posizioa);
    Serial.println("------------");
  }
}


void readChannel(int channel) {
  int rawValue = pulseIn(rcPins[channel], HIGH, pulseInDelay);
  chValue[channel] = fmap( (float)rawValue, 1000.0, 2000.0, 0.0, 1.0);
  chValue[channel] = chValue[channel] < 0.0 ? 0.0 : chValue[channel];
  chValue[channel] = chValue[channel] > 1.0 ? 1.0 : chValue[channel];
}


void angeluakk() {
  angeluak = (chValue[iChannel]) * 180;
}


void printChannel() {
  angeluakk();
  Serial.print("angeluak:");
  Serial.println(angeluak);
  Serial.println("------------");
  delay(10);
}


void mandoa() {
  for (int iChannel = 0; iChannel < 6 ; iChannel++) {
    readChannel(iChannel);
  }
  printChannel();
}




void motorra(){
  mandoa();
  pot();
  mppt();


  while (angeluak > 99) {
    Serial.println(" eskuibira");
    Serial.println("------------");
    direkzioa = posizioa;
    ESC1.write(30*Vel);
    ESC2.write(100 *Vel);
    delay(100);
    break;
  }
  while ((angeluak < 80) and (angeluak > 5)) {
    Serial.println(" ezkerrera");
    Serial.println("------------");
    ESC1.write(100*Vel);
    ESC2.write(30*Vel);
    direkzioa = posizioa;
    delay(100);
    break;
  }
  while ((angeluak < 99) and (angeluak > 80)) {
    Serial.print("posizioa: ");
    Serial.println(posizioa);
    Serial.println("------------");

    if ((posizioa > 354) and (posizioa < 360)) {
      if (((posizioa - direkzioa) < 354) and ((posizioa - direkzioa) >= 180))  {
        Serial.println(" aurrera ezker 355");
        Serial.println("------------");
        ESC1.write(100*Vel);
        ESC2.write(90*Vel);
        delay(100);
      }
     else if (((posizioa - direkzioa) < 180) and ((posizioa - direkzioa) > 5)) {
        Serial.println(" aurrera eskuin 355");
        Serial.println("------------");
        ESC1.write(90*Vel);
        ESC2.write(100*Vel);
        delay(100);
      }
      else {
        Serial.println(" aurrera aurrera 355");
        Serial.println("------------");
        ESC1.write(100*Vel);
        ESC2.write(100*Vel);
        delay(100);
      }
    }
    else if ((posizioa > 0) and (posizioa < 5)) {
      if (((posizioa - direkzioa) <= -180) and ((posizioa - direkzioa) > -355))  {
        Serial.println(" aurrera eskuin 0");
        Serial.println("------------");
        ESC1.write(90*Vel);
        ESC2.write(100*Vel);
        delay(100);
      }
      else if (((posizioa - direkzioa) < -5) and ((posizioa - direkzioa) > -180)) {
        
        Serial.println(" aurrera ezker 0");
        Serial.println("------------");
        ESC1.write(100*Vel);
        ESC2.write(90*Vel);
        delay(100);
      }
      else {
        Serial.println(" aurrera aurrera 0");
        Serial.println("------------");
        ESC1.write(100*Vel);
        ESC2.write(100*Vel);
        delay(100);
      }
    }
    else {
      if ((posizioa - direkzioa) < -5) {
        Serial.println(" aurrera ezker");
        Serial.println("------------");
        ESC1.write(100*Vel);
        ESC2.write(90*Vel);
        delay(100);
      }
      else if ((posizioa - direkzioa) > 5) {
        Serial.println(" aurrera eskuin");
        Serial.println("------------");
        ESC1.write(90*Vel);
        ESC2.write(100*Vel);
        delay(100);
      }
      else {
        Serial.println(" aurrera aurrera");
        Serial.println("------------");
        ESC1.write(100*Vel);
        ESC2.write(100*Vel);
        delay(100);
      }
    }
    break;
  }
}
  

void mppt() {
  voltIntIrakurketa ();
  if (power < power_before)
  { if (voltage >= 17) {
      pwm = pwm + 2;

    }
    else {
      pwm = pwm - 20;
      delay(100);
    }
  }

  else {
    if (voltage >= 17) {
      pwm = pwm + 2;
      delay(100);
    }
    else {
      pwm = pwm - 20;
      delay(100);
    }
  }
  power_before = power;
  if (pwm < 20) {
    pwm = 20;
  }
  if (pwm > 130) {
    pwm = 130;
  }
  Vel = mapFloat(pwm,20,130 ,0,1);
  }

void   voltIntIrakurketa () {

  corriente1 = analogRead(A1);
  corriente2 = analogRead(A2);

  int filtered2 = adcFilter2.filter(corriente2);
  int filtered1 = adcFilter1.filter(corriente1);

  voltage = analogRead(A5);
  voltage = mapFloat (voltage, 0, 900, 0, 21.7);

  float corrienteMap1Filtered1 = mapFloat (filtered1, 470, 560, 0.0, 1.65);
  float corrienteMap2Filtered2 = mapFloat (filtered2, 498, 560, 0.0, 1.4);

  float corrienteMap1 = mapFloat (corriente1, 470, 560, 0.0, 1.66);
  float corrienteMap2 = mapFloat (corriente2, 498, 560, 0.0, 1.4);

  corrientetotal = (corrienteMap1Filtered1 + corrienteMap2Filtered2);
  int power = corrientetotal * voltage;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    Serial.print (pwm);
    Serial.println (" pwm: ");
    Serial.print (corriente1);
    Serial.print (" corriente1: ");
    Serial.print (corrienteMap1);
    Serial.print (" corrienteMap1: ");
    Serial.print (corrienteMap1Filtered1);
    Serial.println (" corrienteMap1Filtered1: ");
    Serial.print (corriente2);
    Serial.print (" corriente2: ");
    Serial.print (corrienteMap2);
    Serial.print (" corrienteMap2: ");
    Serial.print (corrienteMap2Filtered2);
    Serial.println (" corrienteMap2Filtered2: ");
    Serial.print (voltage);
    Serial.println (" voltage: ");
    Serial.print (power);
    Serial.println (" power:  ");
  }
}
