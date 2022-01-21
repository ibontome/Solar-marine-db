
 int channel;
int sarrera1 = 5;
int sarrera2 = 6;
float chValue1[6];
float chValue2[6];
const int pulseInDelay = 20000;
void setup() 
{ 
  pinMode(sarrera1,INPUT);
   pinMode(sarrera2,INPUT);
  Serial.begin(9600);
}
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void readChannel()
{
  int rawValue = pulseIn(sarrera1, HIGH, pulseInDelay);
  int rawValue2 = pulseIn(sarrera2, HIGH, pulseInDelay);
  chValue1[channel] = fmap( (float)rawValue, 1000.0, 2000.0, 0.0, 1.0);
  chValue1[channel] = chValue1[channel] < 0.0 ? 0.0 : chValue1[channel]; 
  chValue1[channel] = chValue1[channel] > 1.0 ? 1.0 : chValue1[channel];
  chValue2[channel] = fmap( (float)rawValue2, 1000.0, 2000.0, 0.0, 1.0);
  chValue2[channel] = chValue2[channel] < 0.0 ? 0.0 : chValue2[channel]; 
  chValue2[channel] = chValue2[channel] > 1.0 ? 1.0 : chValue2[channel];
}


void loop()
{
readChannel();
    Serial.print("Ch1#");

    Serial.print(": ");
    Serial.println(chValue1[channel]);
 
  Serial.println("------------");
   Serial.print("Ch2 #");

    Serial.print(": ");
    Serial.println(chValue2[channel]);
 
  Serial.println("------------");
  delay(1000);
}
