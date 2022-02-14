// 0.2_V. Corrientes estables
// 0.3_V. Corrientes estables
//0.4_v Comienzo de mppt
//0.5_v funciona bien con la placa pero habria que afinarlo un poco.

#include <Ewma.h>
#include <EwmaT.h>

#include <MapFloat.h>
#include <Servo.h>

Ewma adcFilter1(0.001);   // Less smoothing - faster to detect changes, but more prone to noise
Ewma adcFilter2(0.001);  // More smoothing - less prone to noise, but slower to detect changes

unsigned long previousMillis = 0;
const long interval = 1000;
float corrientetotal;
float voltage = 0;
int corriente2 = 0;
int corriente1 = 0;
float pot;
float corrienteTotal = 0;
float lastPower = 0.0;
float lastVoltage;
float pwm = 0.0 ;
float pwmMap = 0.0;

Servo ESC1;
Servo ESC2;
void setup()
{
  Serial.begin(9600);
  ESC1.attach(9, 1000, 2000); // (pin, min pulse width, max pulse width in microseconds)
  ESC2.attach(10, 1000, 2000); // (pin, min pulse width, max pulse width in microseconds)
  ESC1.writeMicroseconds (180);
  ESC2.writeMicroseconds (180);
  delay(5000);
  pwm = 30;
  //delay (1000);

}

void loop() {
  escAttach ();
  voltIntIrakurketa ();
  potenciometro();
}
void potenciometro(){
  pot= analogRead(A0);
  pot=mapFloat(pot,0,1023,1,180);
}
void escAttach () {
  //pwm = analogRead (A0);
  //pwmMap = mapFloat (pwm, 100, 1023 , 0 , 120); // 180raino jar liteke baina momentuz aldeerik ez dago
  ESC1.write(pwm);
  ESC2.write(pwm);

}
void   voltIntIrakurketa () {

  corriente1 = analogRead(A1);
  corriente2 = analogRead(A2);


  int filtered1 = adcFilter1.filter(corriente1);
  int filtered2 = adcFilter2.filter(corriente2);


  voltage = analogRead(A5);
  float realVoltage = mapFloat (voltage, 0, 961, 0, 21.22);

  float corrienteMap1Filtered1 = mapFloat (filtered1, 524, 570, 0.0, 0.98);
  float corrienteMap2Filtered2 = mapFloat (filtered2, 527, 575, 0.0, 1.0);


  float corrienteMap1 = mapFloat (corriente1, 524, 570, 0.0, 0.98);
  float corrienteMap2 = mapFloat (corriente2, 527, 575, 0.0, 1.0);

  corrientetotal = (corrienteMap1Filtered1 + corrienteMap2Filtered2);
  float power = corrientetotal * realVoltage;



  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;


    Serial.print (" corriente1: ");
    Serial.print (corriente1);
    Serial.print (" filtered1: ");
    Serial.print (filtered1);
    Serial.print (" corrienteMap1: ");
    Serial.print (corrienteMap1);
    Serial.print (" corrienteMap1Filtered1: ");
    Serial.println (corrienteMap1Filtered1);

    Serial.print (" corriente2: ");
    Serial.print (corriente2);
    Serial.print (" filtered2: ");
    Serial.print (filtered2);
    Serial.print (" corrienteMap2: ");
    Serial.print (corrienteMap2);
    Serial.print (" corrienteMap2Filtered2: ");
    Serial.println (corrienteMap2Filtered2);

    Serial.print (" corrientetotal: ");
    Serial.println (corrientetotal);

    Serial.print (" voltage: ");
    Serial.print (voltage);
    Serial.print (" realVoltage: ");
    Serial.println (realVoltage);
    Serial.print("pot");
    Serial.println(pot);


    float power = corrientetotal * realVoltage;
    if (power >= lastPower ) {
      if ((realVoltage - lastVoltage) > -0.5 ) {
        pwm = pwm + 3;
      }

      else {
        pwm = pwm +3;
      }
    }

    else {
      if ((realVoltage - lastVoltage) > -0.25 ) {
        pwm = pwm + 3;
      }
      else if ((realVoltage - lastVoltage) < -3 ) {
        pwm =  pwm - 30;
      }
      else {
        pwm = pwm - 6;
      }
    }
    if (realVoltage<4){
      pwm=20;
    }
    lastVoltage = realVoltage;
    lastPower = power;
    if (pwm < 20) {
      pwm = 20;
    }
    if (pwm > 130) {
      pwm = 130;
    }
    Serial.print (" lastPower:  ");
    Serial.println (lastPower);

    Serial.print (" power:  ");
    Serial.println (power);
    Serial.print (" pwm: ");
    Serial.println  (pwm);


    /*Serial.print (" courrent1: ");
      Serial.print (courrent1);
      Serial.print (" courrent2: ");
      Serial.print (courrent2);
      Serial.print (" corriente2: ");
      Serial.print (corriente2);
      Serial.print (" corriente total: ");
      Serial.println (corrientetotal);*/
  }
}
