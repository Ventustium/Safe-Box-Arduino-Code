/* Catatan: Ada rangkaian yang kurang pada Arduino Info ini
Rangkaian yang kurang yaitu adalah tidak adanya kabel ground
yang terhubung ke Arduino Log.
*/

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>


String password, dummy;
char show[17], show2[17];
char x;
LiquidCrystal lcd1(7, 6, 5, 4, 3, 2);
SoftwareSerial a(8, 9);
char int_password[17] = "C11190018";
int login = 0;
int state;
int attemp = 0;

const unsigned long eventInterval1 = 1000;
unsigned long previousTime1 = 0;

const unsigned long eventInterval2 = 5000;
unsigned long previousTime2 = 0;

int clear = 0;
int cm = 100;
int i = 0;
int print = 0;
long readUltrasonicDistance(int pin);
int pass = 0;
int verification = 0;
int stateP, stateIP, pSHT;


void setup(){
  pinMode(12, INPUT);
  
  login = 0;
  Serial.begin(115200);
  a.begin(4800);
  lcd1.begin(16, 2);
  
  Wire.begin();
  
  a.write(2);
  a.write(4);
  a.write(5);
  Wire.requestFrom(8, 9);
  ultraRead();
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

void loop()
{
  unsigned long currentTime1 = millis();
  
  if (currentTime1 - previousTime1 >= eventInterval1) {
  ultraRead();
    previousTime1 = currentTime1;
  }
  
  //request data from power
  if (currentTime1 - previousTime2 >= eventInterval2 && pSHT != 1) {
    Wire.beginTransmission(8);
  	Wire.write("PWR ");
  	Wire.endTransmission();
    
    Wire.requestFrom(8, 4);    // request 6 bytes from slave device #8
	int c[4];
    int z = 0;
    float volt;
    while (Wire.available()) { // slave may send less than requested
      c[z] = Wire.read(); // receive a byte as character
               // print the character
      z++;
    }
    volt = c[0] * 100 + c[1] * 10 + c[2];
    Serial.println(volt/100);
    
    if(c[3] == 0 && stateP == 0){
      Wire.beginTransmission(4);
      Wire.write(203);
      Wire.endTransmission();
      Serial.println("Power Cut");
      stateP = 1;
    }
    
    if(c[3] == 1 && stateP == 1){
      Wire.beginTransmission(4);
      Wire.write(204);
      Wire.endTransmission();
      Serial.println("Power ON");
      stateP = 0;
    }
    
    previousTime2 = currentTime1;
    }
  	
  if(digitalRead(11) == HIGH && stateIP == 0){
      Wire.beginTransmission(4);
      Wire.write(206);
      Wire.endTransmission();
      Serial.println("Motion Detected");
      stateIP = 1;
    }
    
    if(digitalRead(11) == LOW && stateIP == 1){
      stateIP = 0;
    }
  	
    if(cm < 50){
      if(print != 1 && pSHT != 1){
      	lcd1.setCursor(0,0);
      	lcd1.print("Password:");
        i = 0;
        print = 1;
        clear = 0;
      }
      
      if(print != 1 && pSHT == 1){
      	lcd1.clear();
        lcd1.print("SAFEBOX SHUTDOWN");
        print = 1;
      }
      
      if(login == 0){
        logingIn();
        }
      
      if(login == 3){
        a.write(2);
        lcd1.clear();
        lcd1.print("PASSWORD ERROR");
        lcd1.setCursor(0,1);
        lcd1.print("SAFE BOX LOCKED");
        delay(5000);
		lcd1.clear();
      	lcd1.print("Password:");
        login = 0;
        attemp = 0;
        a.write(1);
      }
      
      
      if(login == 1 && pass == 0){
          loggedIn();
      }
      else if (login == 1 && pass == 1){
          if (verification == 0)
          changepass();
          
          if(verification == 1)
          reType();
      }
    }
  if(cm > 50){
    
    if(print != 1 && pSHT == 1){
      	lcd1.clear();
        lcd1.print("SAFEBOX SHUTDOWN");
        print = 1;
      }
    
    if(clear == 0){
      clear = 1;
      lcd1.clear();
      print = 0;
    }
  }
}


void ultraRead(){
  
    cm = 0.01723 * readUltrasonicDistance(12);
    if (cm <= 50 && state == 0){
      a.write(1);
      state = 1;
      }
    else if (cm > 50 && state == 1){
      a.write(2);
      state = 0;
      lcd1.clear();
      print = 0;  
      }
}

long readUltrasonicDistance(int pin)
{
  pinMode(pin, OUTPUT);  // Clear the trigger
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  // Sets the pin on HIGH state for 10 micro seconds
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  // Reads the pin, and returns the sound wave travel time in microseconds
  return pulseIn(pin, HIGH);
}

void serialDetect(){
	x = a.read();
    
    if((x == '1' || x == '2' || x == '3' || x == 'C' || 
       x == '4' || x == '5' || x == '6' || 
       x == '7' || x == '8' || x == '9' || x == '0') && i <= 15){
      
      show[i] = x;
      lcd1.setCursor(i,1);        
      lcd1.print(show[i]);
      Serial.print(i);
      Serial.println(show);
      i++;
    }
    
  if(x == 'Z'){
    Serial.println("Fire Detected");
    Wire.beginTransmission(4);
    Wire.write(202);
    Wire.endTransmission();
  }
  
  if(x == 'X')
    Serial.println("No Fire");
  
  if(x == 'B'){
    backspace();
  }
  
}

void logingIn(){
  if(a.available())
  {
    
    serialDetect();
    
    if(strcmp(show, int_password) == 0 && x == '#'){
      lcd1.clear();
      Serial.println(show);
      memset(show, 0, sizeof show);
      Serial.println(show);
      login = 1;
      lcd1.setCursor(0,0);
      lcd1.print("HI Kevin!");
      lcd1.setCursor(0,1);
      lcd1.print("Selamat Datang");
      a.write(4);
      a.write(6);
      Wire.beginTransmission(4);
      Wire.write(200);
      Wire.endTransmission();
    }
    
    else if (strcmp(show, int_password) != 0 && x == '#') {
      if(attemp >= 2){
      	lcd1.clear();
        a.write(3);
        login = 3;
      }
      if (attemp < 2){
      	lcd1.clear();
      	lcd1.setCursor(0,0);
      	lcd1.print("Password Error");
      	lcd1.setCursor(0,1);
      	lcd1.print("Please Try Again");
      	a.write(2);
      	attemp++;
      	delay(1000);
        a.write(1);
      	reset(0);
      }
      
    }
      
    if (x == '*'){
      reset(0);
    }
    
  }
}

void loggedIn(){
  
  
  if(a.available())
  {
    if(x == 'Z'){
    Serial.println("Fire Detected");
    Wire.beginTransmission(4);
    Wire.write(202);
    Wire.endTransmission();
  }
  
  if(x == 'X')
    Serial.println("No Fire");
    
    Serial.print(x);
    x = a.read();
    if (x == '*'){
      a.write(5);
      reset(0);
      Wire.beginTransmission(4);
      Wire.write(201);
      Wire.endTransmission();
    }
    if (x == 'A'){
      lcd1.clear();
      lcd1.print("Change Password");
      i = 0;
      pass = 1;
    }
    
    shutDown();
  }
}

void shutDown(){
 if(x == 'D'){
   pSHT = 1;
   Wire.beginTransmission(8);
   Wire.write("SHT ");
   Wire.endTransmission();
   
   Wire.beginTransmission(4);
   Wire.write(205);
   Wire.endTransmission();
   
   Serial.println("ARDUINO POWER SHUTDOWN COMPLETE");
      
   a.write(7);
   Serial.println("ARDUINO LOCKER SHUTDOWN COMPLETE");
   
   lcd1.clear();
   lcd1.print("SAFEBOX SHUTDOWN");
   } 
}
void changepass(){

  if(a.available())
  {
    serialDetect();
    
    if(x == 'A'){
      pass = 0;
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("HI Kevin!");
      lcd1.setCursor(0,1);
      lcd1.print("Selamat Datang");  
    }
    
    
    if(verification == 0 && x == '#'){
      lcd1.clear();
      lcd1.print("re-Type Password");
      i = 0;
      verification = 1;
    }
          
    if (x == '*'){
      reset(7);
    }
  }
  
}

void reType(){

  lcd1.setCursor(0,1);
  
  if(a.available())
  {
    
    x = a.read();
    
    if((x == '1' || x == '2' || x == '3' || x == 'C' || 
       x == '4' || x == '5' || x == '6' || 
       x == '7' || x == '8' || x == '9' || x == '0') && i <= 15){
      
      show2[i] = x;
      lcd1.setCursor(i,1);        
      lcd1.print(show2[i]);
      Serial.print(i);
      Serial.println(show2);
      i++;
    }
    
    if(x == 'Z')
      Serial.println("Fire Detected");
    
    if(x == 'X')
      Serial.println("No Fire");
    
    if(x == 'B'){
      backspace2();
      }
    
    if(x == 'A'){
      lcd1.clear();
      verification = 0;
      pass = 0;
      lcd1.setCursor(0,0);
      lcd1.print("HI Kevin!");
      lcd1.setCursor(0,1);
      lcd1.print("Selamat Datang"); 
      
    }
  	
    if (x == '*'){
      reset(8);
    }
    
    
    if(strcmp(show, show2) == 0 && x == '#'){
      lcd1.clear();  
      strcpy(int_password, show);
      Serial.println(int_password);
      lcd1.print("Success");
      lcd1.setCursor(0,1);
      lcd1.print("Please re-login");
      delay(1000);
      reset(0);
    }
    
    if(strcmp(show, show2) != 0 && x == '#'){
      lcd1.clear();  
      lcd1.print("Password don't");
      lcd1.setCursor(0,1);
      lcd1.print("Match. Try Again");
      delay(1000);
      reset(8);
    }
    
    
  }
}

void reset(int prio){
  if(prio == 7){
    lcd1.clear();
    lcd1.write("Change Password");
  	lcd1.setCursor(0,1);
  	memset(show, 0, sizeof show);
  	i = 0;

  }
  
  if(prio == 8){
    lcd1.clear();
    lcd1.write("re-Type Password");
    lcd1.setCursor(0,1);
    memset(show2, 0, sizeof show2);
  	i = 0;
  }
  
  if (prio == 0){
  	lcd1.clear();
  	lcd1.print("Password:");
  	Serial.println("reset");
  	memset(show, 0, sizeof show);
    memset(show2, 0, sizeof show2);
  	i = 0;
  	login = 0;
  	verification = 0;
  	pass = 0;
  }
}

void backspace(){
 if(i != 0)
        i--;
      
      lcd1.setCursor(i,1);
      lcd1.print(" ");
      show[i] = '\0'; 
}

void backspace2(){
 if(i != 0)
        i--;
      
      lcd1.setCursor(i,1);
      lcd1.print(" ");
      show2[i] = '\0'; 
}