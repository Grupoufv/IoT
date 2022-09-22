#include <dht.h>
#define dht_dpin 23                                    ,                                                              
dht DHT2;

void setup()
{
  Serial.begin(9600);
  delay(1000);
}

void loop(){
  DHT2.read(dht_dpin); 
  Serial.print("Umidade = ");
  Serial.print(DHT2.humidity);
  Serial.print(" %  ");
  Serial.println("");
Serial.print("Temperatura = ");
 Serial.print(DHT2.temperature); 
 
  delay(4000);  
}
