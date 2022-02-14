#include <MapFloat.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h> 

Adafruit_BNO055 bno = Adafruit_BNO055(55);
int rcPins[6] = {6,7};
int hasiera;
int start;
int pote;
int geldirik =0;
int angeluak;
int iChannel;
int diferentzia;
int potValue;
int potValue2;
float potValue3;
float chValue[6];
float sensorValue1 = 0;// Voltaje2 medicion de corriente en A1
float voltage = 0;
float corriente = 0;
float corriente1=0;
float corrienteTotal=0;
float Power_now = 0, Power_anc = 0, voltage_anc = 0;
float delta = 10;
float pwm = 0  ;
const int pulseInDelay = 20000;
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
float fmap(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;}

  
void pot(){
long potValue = Serial.parseInt();
}

void readChannel(int channel){
  int rawValue = pulseIn(rcPins[channel], HIGH, pulseInDelay);
    chValue[channel] = fmap( (float)rawValue, 1000.0, 2000.0, 0.0, 1.0);
    chValue[channel] = chValue[channel] < 0.0 ? 0.0 : chValue[channel]; 
    chValue[channel] = chValue[channel] > 1.0 ? 1.0 : chValue[channel];}

  
void angeluakk(){
angeluak= (chValue[iChannel])*180;}


void printChannel(){
angeluakk();
Serial.print("Direkzioa:");
Serial.println(angeluak);
Serial.println("------------");
delay(10);}


void mandoa(){
  for(int iChannel = 0; iChannel <6 ; iChannel++){
    readChannel(iChannel);}
    printChannel();}


void mppt(){
corriente = analogRead (A0);
corriente = mapFloat (corriente,512, 0, 0, 6);
corriente1 = analogRead (A1);
corriente1 = mapFloat (corriente1,512, 0, 0, 6);
voltage = analogRead (A5);
voltage = mapFloat (voltage,0,900, 0, 21.7);
corrienteTotal= corriente + corriente1;
Power_now = (corrienteTotal * voltage);
if (Power_now < Power_anc){ 
  if (voltage >= voltage_anc){
      pwm = pwm + delta;}
  else{
      pwm = pwm - delta;}}
else{
   if (voltage >= voltage_anc){
      pwm = pwm + delta;}
   else{
      pwm = pwm - delta;}}
Power_anc = Power_now;
voltage_anc = voltage;
if (pwm < 20){
    pwm = 20;}
if (pwm > 130){
    pwm = 130;}
Serial.print("Power: ");
Serial.println(Power_now);
Serial.println("--------" );

potValue3 = pwm /130;
delay (100);
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
 //diferentzia= (event.orientation.x)- angeluak;}
void motorra(){
  mppt();
mandoa();
pot();
//iparorratza();


 Serial.print("potvalue ");
Serial.println(potValue3);
for (hasiera== 0; hasiera<1 ; hasiera++) {
  Serial.println(" hasiera");
  ESC.write(0); 
  ESC2.write(0); 
  delay(2000);
  hasiera = 4;
  break;}
while (angeluak> 99){
  Serial.println(" eskuibira");
  ESC.write(0); 
  ESC2.write(130*potValue3);
  pote= potValue;
  delay(100);
  break;}
while ((angeluak< 80) and (angeluak>5)){
  Serial.println(" ezkerrera");
  ESC.write(130*potValue3); 
  ESC2.write(0); 
  pote= potValue; 
  delay(100); 
  break;}
while ((angeluak<99) and (angeluak>80)){
//Serial.println(" aurrera");
  if (potValue<pote){
      ESC.write(130*potValue3); 
      ESC2.write(90*potValue3); 
      Serial.println(" aurrera ezker");
      delay(100);}
  if (potValue>pote){
    
      ESC.write(90*potValue3); 
      ESC2.write(130*potValue3); 
      delay(1000);}
  else {
    Serial.println(" aurrera aurrera");
      ESC.write(130*potValue3); 
      ESC2.write(130*potValue3); 
      delay(100);}
  break;}
}
void loop(){
//mppt();
//mandoa();
pot();
//iparorratza();
motorra();

}
