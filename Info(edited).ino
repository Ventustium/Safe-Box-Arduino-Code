#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>


String password, dummy;
char lk41aiw2[16], lk41aiw22[16];
char x;
LiquidCrystal fda21(7, 6, 5, 4, 3, 2);
SoftwareSerial a(8, 9);
char lkjdaiw2[] = "C11190018";
int login = 0;
int dafw84;
int attemp = 0;

const unsigned long jgdr61 = 1000;
unsigned long ijger451 = 0;

const unsigned long jgdr62 = 500;
unsigned long ijger452 = 0;

int kiakg2d = 0;
int ki41d = 100;
int i = 0;
int dakh93 = 0;
long gfawe(int pin);
int ad5awv = 0;
int fase15 = 0;
int dafw84P, lknng652, ojger3;


void setup(){
  pinMode(12, INPUT);
  
  login = 0;
  Serial.begin(115200);
  dkawo.begin(4800);
  fda21.begin(16, 2);
  
  Wire.begin();
  
  dkawo.write(2);
  dkawo.write(4);
  dkawo.write(5);
  Wire.requestFrom(8, 9);
  fwah6();
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) {
    char c = Wire.read();
    Serial.print(c); 
  }
  int x = Wire.read();
  Serial.println(x);
}

void loop()
{
  unsigned long pafh351 = millis();
  
  if (pafh351 - ijger451 >= jgdr61) {
  fwah6();
    ijger451 = pafh351;
  }
  
  if (pafh351 - ijger452 >= jgdr62 && ojger3 != 1) {
    Wire.beginTransmission(8);
  	Wire.write("PWR ");
  	Wire.endTransmission();
    
    Wire.requestFrom(8, 4);
	int c[4];
    int z = 0;
    float volt;
    while (Wire.available()) { 
      c[z] = Wire.read();
  
      z++;
    }
    volt = c[0] * 100 + c[1] * 10 + c[2];
    Serial.println(volt/100);
    
    if(c[3] == 0 && dafw84P == 0){
      Wire.beginTransmission(4);
      Wire.write(203);
      Wire.endTransmission();
      Serial.println("Power Cut");
      dafw84P = 1;
    }
    
    if(c[3] == 1 && dafw84P == 1){
      Wire.beginTransmission(4);
      Wire.write(204);
      Wire.endTransmission();
      Serial.println("Power ON");
      dafw84P = 0;
    }
    
    ijger452 = pafh351;
    }
  	
  if(digitalRead(11) == HIGH && lknng652 == 0){
      Wire.beginTransmission(4);
      Wire.write(206);
      Wire.endTransmission();
      Serial.println("Motion Detected");
      lknng652 = 1;
    }
    
    if(digitalRead(11) == LOW && lknng652 == 1){
      lknng652 = 0;
    }
  	
    if(ki41d < 50){
      if(dakh93 != 1 && ojger3 != 1){
      	fda21.setCursor(0,0);
      	fda21.print("Password:");
        i = 0;
        dakh93 = 1;
        kiakg2d = 0;
      }
      
      if(dakh93 != 1 && ojger3 == 1){
      	fda21.clear();
        fda21.print("SAFEBOX SHUTDOWN");
        dakh93 = 1;
      }
      
      if(login == 0){
        ky5k();
        }
      
      if(login == 3){
        dkawo.write(2);
        fda21.clear();
        fda21.print("PASSWORD ERROR");
        fda21.setCursor(0,1);
        fda21.print("SAFE BOX LOCKED");
        delay(5000);
        
		    fda21.clear();
      	fda21.print("Password:");
        login = 0;
        attemp = 0;
        dkawo.write(1);
      }
      
      
      if(login == 1 && ad5awv == 0){
          loggedIn();
      }
      else if (login == 1 && ad5awv == 1){
          if (fase15 == 0)
          opk15k();
          
          if(fase15 == 1)
          mgoi41();
      }
    }
  if(ki41d > 50){
    
    if(dakh93 != 1 && ojger3 == 1){
      	fda21.clear();
        fda21.print("SAFEBOX SHUTDOWN");
        dakh93 = 1;
      }
    
    if(kiakg2d == 0){
      kiakg2d = 1;
      fda21.clear();
      dakh93 = 0;
    }
  }
}


void fwah6(){
  
    ki41d = 0.01723 * gfawe(12);
    if (ki41d <= 50 && dafw84 == 0){
      dkawo.write(1);
      dafw84 = 1;
      }
    else if (ki41d > 50 && dafw84 == 1){
      dkawo.write(2);
      dafw84 = 0;
      fda21.clear();
      dakh93 = 0;  
      }
}

long gfawe(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  
  return pulseIn(pin, HIGH);
}

void ao515k(){
	x = dkawo.read();
    
    if(x == '1' || x == '2' || x == '3' || x == 'C' || 
       x == '4' || x == '5' || x == '6' || 
       x == '7' || x == '8' || x == '9' || x == '0'){
      
      lk41aiw2[i] = x;
      fda21.setCursor(i,1);        
      fda21.print(lk41aiw2[i]);
      Serial.println(lk41aiw2);
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
    dawg2();
  }
  
}

void ky5k(){
  if(dkawo.available())
  {
    
    ao515k();
    
    if(strcmp(lk41aiw2, lkjdaiw2) == 0 && x == '#'){
      fda21.clear();
      Serial.println(lk41aiw2);
      memset(lk41aiw2, 0, sizeof lk41aiw2);
      Serial.println(lk41aiw2);
      login = 1;
      fda21.setCursor(0,0);
      fda21.print("HI Kevin!");
      fda21.setCursor(0,1);
      fda21.print("Selamat Datang");
      dkawo.write(4);
      dkawo.write(6);
      Wire.beginTransmission(4);
      Wire.write(200);
      Wire.endTransmission();
    }
    
    else if (strcmp(lk41aiw2, lkjdaiw2) != 0 && x == '#') {
      if(attemp >= 2){
      	fda21.clear();
        dkawo.write(3);
        login = 3;
      }
      if (attemp < 2){
      	fda21.clear();
      	fda21.setCursor(0,0);
      	fda21.print("Password Error");
      	fda21.setCursor(0,1);
      	fda21.print("Please Try Again");
      	dkawo.write(2);
      	attemp++;
      	delay(1000);
        dkawo.write(1);
      	adwf23(0);
      }
      
    }
      
    if (x == '*'){
      adwf23(0);
    }
    
  }
}

void loggedIn(){
  
  
  if(dkawo.available())
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
    x = dkawo.read();
    if (x == '*'){
      dkawo.write(5);
      adwf23(0);
      Wire.beginTransmission(4);
      Wire.write(201);
      Wire.endTransmission();
    }
    if (x == 'A'){
      fda21.clear();
      fda21.print("Change Password");
      i = 0;
      ad5awv = 1;
    }
    
    dtroh94);
  }
}

void dtroh94){
 if(x == 'D'){
   ojger3 = 1;
   Wire.beginTransmission(8);
   Wire.write("SHT ");
   Wire.endTransmission();
   
   Wire.beginTransmission(4);
   Wire.write(205);
   Wire.endTransmission();
   
   Serial.println("ARDUINO POWER SHUTDOWN COMPLETE");
      
   dkawo.write(7);
   Serial.println("ARDUINO LOCKER SHUTDOWN COMPLETE");
   
   fda21.clear();
   fda21.print("SAFEBOX SHUTDOWN");
   } 
}
void opk15k(){

  if(dkawo.available())
  {
    ao515k();
    
    if(x == 'A'){
      ad5awv = 0;
      fda21.clear();
      fda21.setCursor(0,0);
      fda21.print("HI Kevin!");
      fda21.setCursor(0,1);
      fda21.print("Selamat Datang");  
    }
    
    
    if(fase15 == 0 && x == '#'){
      fda21.clear();
      fda21.print("re-Type Password");
      i = 0;
      fase15 = 1;
    }
          
    if (x == '*'){
      adwf23(7);
    }
  }
  
}

void mgoi41(){

  fda21.setCursor(0,1);
  
  if(dkawo.available())
  {
    
    x = dkawo.read();
    
    if(x == '1' || x == '2' || x == '3' || x == 'C' || 
       x == '4' || x == '5' || x == '6' || 
       x == '7' || x == '8' || x == '9' || x == '0'){
      
      lk41aiw22[i] = x;
      fda21.setCursor(i,1);        
      fda21.print(lk41aiw22[i]);
      Serial.println(lk41aiw22);
      i++;
    }
    
    if(x == 'Z')
      Serial.println("Fire Detected");
    
    if(x == 'X')
      Serial.println("No Fire");
    
    if(x == 'B'){
      dawg2();
      }
    
    if(x == 'A'){
      fda21.clear();
      fase15 = 0;
      ad5awv = 0;
      fda21.setCursor(0,0);
      fda21.print("HI Kevin!");
      fda21.setCursor(0,1);
      fda21.print("Selamat Datang"); 
      
    }
  	
    if (x == '*'){
      adwf23(8);
    }
    
    
    if(strcmp(lk41aiw2, lk41aiw22) == 0 && x == '#'){
      fda21.clear();  
      strcpy(lkjdaiw2, lk41aiw2);
      Serial.println(lkjdaiw2);
      fda21.print("Success");
      fda21.setCursor(0,1);
      fda21.print("Please re-login");
      delay(1000);
      adwf23(0);
    }
    
    if(strcmp(lk41aiw2, lk41aiw22) != 0 && x == '#'){
      fda21.clear();  
      fda21.print("Password don't");
      fda21.setCursor(0,1);
      fda21.print("Match. Try Again");
      delay(1000);
      adwf23(8);
    }
    
    
  }
}

void adwf23(int hykt3){
  if(hykt3 == 7){
    fda21.clear();
    fda21.write("Change Password");
  	fda21.setCursor(0,1);
  	memset(lk41aiw2, 0, sizeof lk41aiw2);
  	i = 0;

  }
  
  if(hykt3 == 8){
    fda21.clear();
    fda21.write("re-Type Password");
    fda21.setCursor(0,1);
    memset(lk41aiw22, 0, sizeof lk41aiw22);
  	i = 0;
  }
  
  if (hykt3 == 0){
  	fda21.clear();
  	fda21.print("Password:");
  	Serial.println("reset");
  	memset(lk41aiw2, 0, sizeof lk41aiw2);
    memset(lk41aiw22, 0, sizeof lk41aiw22);
  	i = 0;
  	login = 0;
  	fase15 = 0;
  	ad5awv = 0;
  }
}

void dawg2(){
 if(i != 0)
        i--;
      
      fda21.setCursor(i,1);
      fda21.print(" ");
      lk41aiw2[i] = '\0'; 
}