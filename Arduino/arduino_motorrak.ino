#include <Servo.h>
float Sensibilidad=0.185; 
float voltage=0;
Servo ESC1;  
Servo ESC2; // create servo object to control the ESC
int potValue;  // value from the analog pin

void setup() {
  // Attach the ESC on pin 9
  ESC1.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
   ESC2.attach(10,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  Serial.begin(9600);
 
}



void loop() {
 potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  ESC1.write(potValue);    // Send the signal to the ESC  
  ESC2.write(potValue); 
}
