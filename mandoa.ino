int rcPins[6] = {6,};
float chValue[6];
const int pulseInDelay = 20000;
int angeluak;
int iChannel;
void setup() 
{ 
  Serial.begin(9600);
}
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void angeluakk(){
  
  angeluak= (chValue[iChannel])*180;
}

void readChannel(int channel)
{
  int rawValue = pulseIn(rcPins[channel], HIGH, pulseInDelay);
  chValue[channel] = fmap( (float)rawValue, 1000.0, 2000.0, 0.0, 1.0);
  chValue[channel] = chValue[channel] < 0.0 ? 0.0 : chValue[channel]; 
  chValue[channel] = chValue[channel] > 1.0 ? 1.0 : chValue[channel];
}
void printChannel()
{
  angeluakk();
  for(int iChannel = 0; iChannel < 1; iChannel++)
  {
    Serial.print("Direkzioa:");
    Serial.println(angeluak);
  };
  Serial.println("------------");
}
void loop()
{
  for(int iChannel = 0; iChannel < 6; iChannel++)
  {
    readChannel(iChannel);
  }
  printChannel();
  delay(2500);
}
