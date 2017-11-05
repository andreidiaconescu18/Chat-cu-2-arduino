#include <Wire.h>
#include <LiquidCrystal.h>  
 
#define adress_2 0x2
#define adress_1 0x1

String text="";
char buf[200];

int A_Pin=9; //pin pentru brightness
int Brightness=255;
int RS_Pin=12;
int E_Pin=11;
int D4_Pin=5;
int D5_Pin=4;
int D6_Pin=3;
int D7_Pin=2;
int V0_Pin=6;
int Contrast=110;
/*
 * K, RW, VSS - GND
 * VDD - 5V
 * V0 - potentiometru sau la pin 6 si se face scriere analoga pe el - contrast
 */
LiquidCrystal lcd(RS_Pin, E_Pin, D4_Pin, D5_Pin, D6_Pin, D7_Pin); 

void setup() {
  Serial.begin(9600);
  Wire.begin(adress_1);
  Wire.onReceive(receive_func);
  analogWrite(A_Pin,Brightness);
  analogWrite(V0_Pin,Contrast);
  lcd.begin(16, 2);
}

void loop() {
 if(Serial.available()>0){
    text=Serial.readStringUntil('\n');
    if(text!="")
      {        
        byte x=text.length();
        text.toCharArray(buf, x+1);
        Wire.beginTransmission(adress_2);
        Wire.write(x);
        Wire.write(buf);
        Wire.endTransmission();
        Serial.print("Arduino 1: ");
        Serial.println(text);
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 0);
        lcd.print(text);
      }
  }
}

char buff2[200];

void receive_func(int howMany) {
 if(Wire.available()>0){
    byte l = Wire.read();
    for(int i=0; i<l; i++)
    {
      char c = Wire.read();
      buff2[i]=c;
    }
    buff2[l]='\0';
    Serial.print("Arduino 2: ");
    Serial.println(buff2);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(buff2);
  }
}
