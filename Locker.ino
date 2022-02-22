/* Catatan: untuk SoftwareSerial, gunakan baudrate 4800 
   Arduino ini bertugas untuk membaca masukan dari keypad:
   '*' -> mulai memasukkan (ulang) password
   '#' -> tombol Enter
   'A' -> untuk mereset password (harus sudah login)
   'B' -> untuk 'backspace'
   'D' -> untuk shutdown system (harus sudah login)

*/

#include <Servo.h>
#include <SoftwareSerial.h>
#include <Keypad.h>

#define pinServo 13

Servo myservo;

int baselineTemp = 0;
int celsius = 0;
int fahrenheit = 0;
int servo = 0;

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; 
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

SoftwareSerial a(11, 12);

int y;
String x;
int keylock = 1;
int alarm = 1;
int stateZ = 0;


void setup(){
  Serial.begin(115200);
  a.begin(4800);
  
  pinMode(10, OUTPUT);

  myservo.attach(pinServo);
}

void loop(){
  temp();
  gas();
  
  if(a.available()){
  y = a.read();
    
  	if ( y == 1){
      keylock = 0;
      Serial.println("KEYPPAD UNLOCKED");
    }
    if ( y == 2){
      keylock = 1;
      Serial.println("KEYPAD LOCKED");
    }
    if ( y == 3){
      alarm = 0;
      Serial.println("ALARM ON");
    }
    if( y == 4){
     alarm = 1; 
      Serial.println("ALARM OFF");
    }
    
    if (y == 5){
     servo = 0;
      Serial.println("Servo Locked");
    }
    
    if (y == 6){
     servo = 1; 
      Serial.println("Servo Unlocked");
    }
    if (y == 7){
      Serial.println("SHUTDOWN");
      exit(0);
    }
  }
  
  if (keylock == 0){
    char keypressed = keypad.getKey();
  	if (keypressed != NO_KEY){
      Serial.print(keypressed);
      a.print(keypressed);
    }
  }
  if (keylock == 1){
  	
  }
  
  if (alarm == 0){
    tone(10, 3000, 1);
    
    
  }
  if (alarm == 1){
  	digitalWrite(10, LOW);
  }
  
  if (servo == 0)
  	myservo.write(0);
  
  if (servo == 1)
    myservo.write(180);
  
  if(celsius >= 50 && gas() >= 150 && stateZ == 0){
    alarm = 0;
    a.print('Z');
    Serial.print('Z');
    stateZ = 1;
  }
  if((celsius < 50 || gas() < 150) && stateZ == 1){
    alarm = 1;
  	stateZ = 0;
    a.print('X');
    Serial.print('X');
  }
}

int temp(){
  baselineTemp = 40;
  
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  
}

int gas(){
  int gas = analogRead(A2);
  return gas;
}


