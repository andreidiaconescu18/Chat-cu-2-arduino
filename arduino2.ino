#include <Wire.h>

#define adress_2 0x2
#define adress_1 0x1

String text="";
char buf[200];
int led=9;
int buzzer=5;

void setup() {
  pinMode(led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  Wire.begin(adress_2);
  Wire.onReceive(receive_func);
}

void loop() {
  if(Serial.available()>0){
  text=Serial.readStringUntil('\n');
  if(text!="")
    {
    byte x=text.length();
    text.toCharArray(buf, x+1);
    Wire.beginTransmission(adress_1);
    Wire.write(x);
    Wire.write(buf);
    Wire.endTransmission();
    Serial.print("Arduino 2: ");
    Serial.println(text);
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
    if(buff2[0]!='/'){
      Serial.print("Arduino 1: ");
      Serial.println(buff2);    
    }
    else
      command(); 
  }
}

void command()
{
  if(strncmp(buff2+1,"led",3)==0)
    {
      int val=0;
      val=atoi(buff2+4);
      //Serial.print(val);
      analogWrite(led, val);
    }
   if(strncmp(buff2+1,"buz",3)==0)
    {
      int val=0;
      val=atoi(buff2+4);
      tone(buzzer,val,10000);
    }
}

