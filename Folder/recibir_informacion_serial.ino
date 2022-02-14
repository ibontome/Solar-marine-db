int posizioa;
void setup {
  
  Serial.begin(9600);
  }

void loop {
  if (Serial.available() > 0) {
    posizioa = Serial.parseInt();
    Serial.print("posizioa");
    Serial.println(posizioa);
    Serial.println("------------");
  }
}
