void setup() {
  Serial.begin(9600);
}
 
void loop() {
 
 // Leitura do sensor no pino A0 e armazenamento em SensorValue
 
 int sensorValue = analogRead(A0);
 int solo=map(sensorValue , 1024, 300, 0, 100);
 // verifica se valor de leitura está acima de 600 (umido abaixo de 600  e seco até 1023)
 Serial.println("leitura do sensor : ");
 Serial.println(sensorValue);
 Serial.println("solo: ");
 Serial.println(solo);
 delay(3000); // Aguarda 3s para verificar se solo está umido novamente
}
