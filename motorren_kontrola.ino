#include <Servo.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h> 
Adafruit_BNO055 bno = Adafruit_BNO055(55);
int rcPins[6] = {6,7};
float chValue[6];
const int pulseInDelay = 20000;
int angeluak;
int iChannel;
int diferentzia;
int potValue;
int potValue2;

int hasiera;
int start;
int pote;
Servo ESC; 
Servo ESC2; 
 
void setup(void) {
  Serial.begin(9600); 
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC2.attach(10,1000,2000); // (pin, min pulse width, max pulse width in microseconds)  
  Serial.println("Orientation Sensor Test");
  Serial.println("");    /* Initialise the sensor */ 
  if(bno.begin())  {    /* There was a problem detecting the BNO055 ... check your connections */   
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");   
    while(1);  }   
    delay(1000);    
    bno.setExtCrystalUse(false);}
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
 
}
void pot(){
potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 360);   // scale it to use it with the servo library (value between 0 and 180)
      // Send the signal to the ESC
Serial.print("Orientazioa: ");
Serial.println(potValue);
delay(1000);
Serial.println("------------");
 
}

void readChannel(int channel)
{
  int rawValue = pulseIn(rcPins[channel], HIGH, pulseInDelay);
  chValue[channel] = fmap( (float)rawValue, 1000.0, 2000.0, 0.0, 1.0);
  chValue[channel] = chValue[channel] < 0.0 ? 0.0 : chValue[channel]; 
  chValue[channel] = chValue[channel] > 1.0 ? 1.0 : chValue[channel];
}
void angeluakk(){
  
  angeluak= (chValue[iChannel])*180;
}
void printChannel()
{
  angeluakk();
 
    Serial.print("Direkzioa:");
    Serial.println(angeluak);
  
  Serial.println("------------");
  delay(1000);
}
void mandoa()
{
  for(int iChannel = 0; iChannel <6 ; iChannel++)
  {
    readChannel(iChannel);
  }
  printChannel();
  
}





  //void iparorratza(void) {  /* Get a new sensor event */  
     // printChannel();
     // sensors_event_t event;   bno.getEvent(&event); /* Display the floating point data */  
     
    //  Serial.print("X: ");  
     // Serial.print(event.orientation.x, 4);  
     // Serial.print("\tY: ");  
     // Serial.print(event.orientation.y, 4); 
     // Serial.print("\tZ: ");  
     // Serial.print(event.orientation.z, 4); 
    //  Serial.println("");   
    //  delay(500);
      // Serial.println("------------");
 //diferentzia= (event.orientation.x)- angeluak;
   // }

void loop(){
 potValue2 = analogRead(A5);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue2 = map(potValue2, 0, 1023, 0,100);
  //iparorratza();
  potValue2 = potValue2/100;
  mandoa();
  pot();
   for (hasiera== 0; hasiera<1 ; hasiera++) {
    Serial.println(" aaaaaaaaaaaaaaaaaaaaaa");
    ESC.write(130); 
    ESC2.write(130);
    delay(5000);
    ESC.write(0); 
    ESC2.write(0); 
    delay(2000);
    hasiera = 4;
    break;
   }
   while (angeluak> 99){
    Serial.println(" eskuibira");
    ESC.write(100*potValue2); 
    ESC2.write(70*potValue2);
    pote= potValue;
    delay(1000);
    break;}
    
    while (angeluak< 80){
    Serial.println(" ezkerrera");
    ESC.write(100*potValue2); 
    ESC2.write(70*potValue2); 
     pote= potValue; 
         delay(1000); 
    break;}
        Serial.println(pote);

    while ((angeluak<99) and (angeluak>80)){
    Serial.println(" aurrera");
  if (potValue<pote){
      ESC.write(100*potValue2); 
    ESC2.write(90*potValue2); 
        delay(1000);
  }
  if (potValue>pote){
      ESC.write(90*potValue2); 
    ESC2.write(100*potValue2); 
        delay(1000);
  }
  else {
    ESC.write(110*potValue2); 
    ESC2.write(110*potValue2); 
        delay(1000);
  }
    break;
    
  }}
