#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);
int k = 3;
double x = 0;
void setup() {
   Serial.begin(9600);
  // put your setup code here, to run once:
  for (k = 3; k<9;k++){
    pinMode(k,OUTPUT);    
  }
  for (k = 3; k<9;k++){
    digitalWrite(k,1);
    delay(1000);
    digitalWrite(k,0);
    delay(500);       
  }
  Serial.println(F("DHTxx test!"));
  dht.begin();
  
  
}

void loop() {
   double t0 = millis();
   delay(2000);
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   float f = dht.readTemperature(true);
   if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
   double t1 = millis();
   x = x+(t1-t0)/1000;
   
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(x);
  Serial.print(F("; Humidity; "));
  Serial.print(h);
  Serial.print(F("% ;Temperature; "));
  Serial.print(t);
  Serial.print(F(";°C; "));
  Serial.print(f);
  Serial.print(F(";°F  Heat index: ;"));
  Serial.print(hic);
  Serial.print(F(";°C; "));
  Serial.print(hif);
 
  if(t>39){
    digitalWrite(k,1);
    Serial.print(";" +String(k)+ ";OFF");
    k++;
    if (k>8) k = 3;
  }
  if (t<36.5){
    digitalWrite(k,0);    
    Serial.print(";"+String(k)+ ";ON");
    k++;
    if (k>8) k = 3;
  }
   Serial.println(F(";°F"));
}
