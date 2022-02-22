/*
 Arduino "Power" ini berfungsi sebagai I2C-slave dari Arduino 
 "Info". Arduino ini mendeteksi level tegangan baterei dan
 menghasilkan sinyal PWM dengan frekuensi 1Kz untuk pengisian
 baterei. Arduino ini juga dilengkapi dengan indikator status
 charger: 
 - red: jika tegangan baterei di bawah 4 volt
 - green: jika aktif charging (dc-PWM: 1% - 50%)
 - blue: jika baterei full (=5volt)
 
 Mekanisme charging:
 jika baterei < 4 volt, dc:50%
 Jika baterei > 4.5 volt, dc: 25%
 Jika baterei > 4.9 volt: dc: 1%
 Jika baterei = 5 volt: dc: 0% 
 
 Ketika menerima kode I2C "PWR", 
 berikan respon level tegangan baterei ("4.75")
*/

#include <Wire.h>
int volt;
char c[] = "\0\0\0";
int power;
int sht = 0;

void setup()
{
  int i;
  for (i = 3; i < 7; i++){
  	pinMode(i, OUTPUT);
  }
  pinMode(10, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  Serial.begin(9600);

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop()
{
  volt = analogRead(A0);
  volt = map(volt, 0, 1023, 350, 500);
  
  if (volt < 400){
    analogWrite(10, 128);
    digitalWrite(6, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
  }
  else if(volt >= 400 && volt < 450){
    analogWrite(10, 64);
    digitalWrite(4, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(3, LOW);
  }
  else if(volt >= 450 && volt < 500){
    analogWrite(10, 26);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
  }
  else if(volt == 500){
    analogWrite(10, 0);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
  }
  if(digitalRead(2) == HIGH){
  	power = 1;
  }
  if(digitalRead(2) == LOW){
  	power = 0;
  }
  
  delay(100);
}

void receiveEvent(int howMany) {
  int k = 0;
  c[0] = '\0'; c[1] = '\0'; c[2] = '\0';
  while (1 < Wire.available()) { 
    c[k] = Wire.read();
    k++;
  }
  int x = Wire.read();
}

void requestEvent() {
  if(strcmp (c, "PWR") == 0){
    Wire.write(volt/100);
    Wire.write(volt/10%10);
    Wire.write(volt%10);
    Wire.write(power);
    Serial.println(volt);
  }
  
  if(strcmp(c, "SHT") == 0){
	exit(0);
  }
}