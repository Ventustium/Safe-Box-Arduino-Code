/* Catatan: Arduino "Log" ini dilengkapi dengan SDcard dan RTC
   yang bisa digunakan untuk mencatat setiap event yang terjadi:
   - waktu login
   - waktu logout
   - waktu shutdown
   - adanya event CCTV (tertangkap kamera)
   - adanya kejadian kebakaran
   - adanya kejadian listrik cut-off
   
   Arduino ini akan menerima perintah via Serial dari komputer
   dengan sintaks sebagai berikut:
   "SHOWLOG" -> tampilkan semua informasi di log-nya
   "CLEARLOG" -> hapus semua informasi di log-nya
*/
#include <Wire.h>

int day = 10;
int month = 12;
int year = 2021;

int hour = 7;
int minutes = 30;
int second = 0;
int second2 = 0;
int milisecond = 0;

int x;
int i = 0;
#define n  50

int logday[n];
int logmonth[n];
int logyear[n];

int loghour[n];
int logminutes[n];
int logsecond[n];
int logmilisecond[n];
int logstatus[n];

const unsigned long eventInterval1 = 1000;
unsigned long previousTime1 = 0;

String a;
String b = "SHOWLOG";
  
void setup()
{
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  
  
}

void loop()
{
  unsigned long currentTime1 = millis();
  if (currentTime1 - previousTime1 >= eventInterval1) {
    second++;
    second2++;
    previousTime1 = currentTime1;
  }
  timestamp();
  
  if(Serial.available() > 0)
  {
    String terminalText = Serial.readStringUntil('\n');
    if(terminalText == "CLEARLOG"){
      Serial.println("CLEARING LOG");
      for(int j = 0; j < n; j++){
        if(logday[j] != 0){
        logday[j] = 0;
        logmonth[j] = 0;
        logyear[j] = 0;
        loghour[j] = 0;
        logminutes[j] = 0;
        logsecond[j] = 0;
        logmilisecond[j] = 0;
        logstatus[j] = 0;
        }     
      } Serial.println("COMPLETED");
    }
    
    if(terminalText == "SHOWLOG")
    {
      int stateLog = 0;
      Serial.println("SHOWING LOG");
      for(int j = 0; j < n; j++){
        if(logday[0] == 0 && stateLog == 0){
          Serial.println("NO LOG");
          stateLog = 1;
        }
        if(logday[j] != 0){
          Serial.print(logday[j]);
          Serial.print("-");
          Serial.print(logmonth[j]);
          Serial.print("-");
          Serial.print(logyear[j]);
          Serial.print(" - ");
          Serial.print(loghour[j]);
          Serial.print(":");
          Serial.print(logminutes[j]);
          Serial.print(":");
          Serial.print(logsecond[j]);
          Serial.print(".");
          Serial.print(logmilisecond[j]);
          Serial.print(": ");
          if(logstatus[j] == 200)
            Serial.println("LOGGED IN");
          if(logstatus[j] == 201)
            Serial.println("LOGGED OUT");
          if(logstatus[j] == 202)
            Serial.println("FIRE DETECTED");
          if(logstatus[j] == 203)
            Serial.println("POWER CUT OFF");
          if(logstatus[j] == 204)
            Serial.println("POWER ON");
          if(logstatus[j] == 205)
            Serial.println("SAFEBOX SHUTDOWN");
          if(logstatus[j] == 206)
            Serial.println("MOTION DETECTED");
        }
      }
    }
  } 
}

void receiveEvent(int howMany)
{
  x = Wire.read();    // receive byte as an integer

  if(x == 200){
    logday[i] = day;
  logmonth[i] = month;
    logyear[i] = year;
    loghour[i] = hour;
    logminutes[i] = minutes;
    logsecond[i] = second;
    logmilisecond[i] = milisecond;
    logstatus[i] = 200;
  }
  
  if(x == 201){
    logday[i] = day;
  logmonth[i] = month;
    logyear[i] = year;
    loghour[i] = hour;
    logminutes[i] = minutes;
    logsecond[i] = second;
    logmilisecond[i] = milisecond;
    logstatus[i] = 201;
  }
  
  if(x == 202){
    logday[i] = day;
  logmonth[i] = month;
    logyear[i] = year;
    loghour[i] = hour;
    logminutes[i] = minutes;
    logsecond[i] = second;
    logmilisecond[i] = milisecond;
    logstatus[i] = 202;
  }
  
  if(x == 203){
    logday[i] = day;
  logmonth[i] = month;
    logyear[i] = year;
    loghour[i] = hour;
    logminutes[i] = minutes;
    logsecond[i] = second;
    logmilisecond[i] = milisecond;
    logstatus[i] = 203;
  }
  
  if(x == 204){
    logday[i] = day;
  logmonth[i] = month;
    logyear[i] = year;
    loghour[i] = hour;
    logminutes[i] = minutes;
    logsecond[i] = second;
    logmilisecond[i] = milisecond;
    logstatus[i] = 204;
  }
  
  if(x == 205){
    logday[i] = day;
  logmonth[i] = month;
    logyear[i] = year;
    loghour[i] = hour;
    logminutes[i] = minutes;
    logsecond[i] = second;
    logmilisecond[i] = milisecond;
    logstatus[i] = 205;
  }
  
  if(x == 206){
    logday[i] = day;
  logmonth[i] = month;
    logyear[i] = year;
    loghour[i] = hour;
    logminutes[i] = minutes;
    logsecond[i] = second;
    logmilisecond[i] = milisecond;
    logstatus[i] = 206;
  }
  i++;
}

void timestamp(){
  unsigned long currentTime1 = millis();
  milisecond = currentTime1 - second2*1000;
  
  if(second >= 60){
    minutes++;
    second = 0;
  }
  
  if(minutes >= 60){
    hour++;
  minutes = 0;
  }
  if(hour >= 24){
    day++;
    hour = 0;
  }

  if(month == 1 || 
     month == 3 || 
     month == 5 ||
     month == 7 ||
     month == 8 ||
     month == 10 ||
     month == 12 && day >= 32){
    day = 1;
  }
  if (month == 2 && day >= 29){
    day = 1;
    month++;
  }
  if(month == 4 || 
     month == 6 ||
     month == 9 ||
     month == 11
     && day >= 30){
    day = 1;
    month++;
  }
  
  if(month >= 13){
  year++;
    month = 1;
  }
}