#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
int persistent_hour=0,hour=0,minute=0,second=0,i=0;

void hrsf(){ //set to hour indicator
  lcd.setCursor(0,0);
}

void minf(){ //set to minute indicator
  lcd.setCursor(3,0);
}

void secf(){ //set to second indicator
  lcd.setCursor(6,0);
}

void setup(){
  lcd.init(); // initialize the lcd
  lcd.backlight();//gotta let em see stuff
  lcd.setCursor(2,0);//Usage: setCursor(column,line)
  lcd.print(":  :");//seperators
  hrsf();
  lcd.print("00");
  minf();
  lcd.print("00");
  secf();
  lcd.print("00");
  pinMode(2, INPUT);//hour input init
  pinMode(3, INPUT);//minute input init
  pinMode(4, INPUT);//second input init
  pinMode(5, INPUT);//start/stop input init
  digitalWrite(7, LOW);
  //pinMode(2, INPUT);
  //==debug usage, enable output to debug console,to delete on production environment==
  Serial.begin(9600);
  //==debug end==
}
int pin_2_status,pin_3_status,pin_4_status,pin_5_status;
void loop(){
  pin_2_status = digitalRead(2); //input status code(HIGH/LOW) into corresponding handlers
  pin_3_status = digitalRead(3); //2 to 5 for hour, minute, second and start stop input
  pin_4_status = digitalRead(4);
  pin_5_status = digitalRead(5);
  //if(persistent_hour !=0){ //TODO: resume last hour after reboot
  //  hour=persistent_hour;
  //}
  //else hour=0;
  secf();
  if(second>59){
	  minute++;
	  second-=60;
  }
  if(second<10){
	  lcd.print("0");
	  lcd.setCursor(7,0);
	  lcd.print(second);
  }
  else lcd.print(second);
  
  minf();
  if(minute>59){ //hour increment
	  hour++;
	  minute-=60;
  }
  if(minute<10){
	  lcd.print("0");
	  lcd.setCursor(4,0);
	  lcd.print(minute);
  }
  else lcd.print(minute);
  
  hrsf();
  if(hour>99){ //==TEMP FIX FOR HOUR LARGER THAN DISPLAY SIZE==
    hour-=100;
  }//==TEMP FIX ENDS HERE==
  if(hour<10){ //set cursor on single digit when hour<10
    lcd.print("0");
    lcd.setCursor(1,0);
    lcd.print(hour);
  }
  else lcd.print(hour);
  if (pin_2_status == HIGH)hour++;
  if (pin_3_status == HIGH)minute++;
  if (pin_4_status == HIGH)second++;
  if (pin_5_status == HIGH) //wat shud i do next? OuO
  //==debug usage,print to debug console, del on production==
  Serial.print(hour:);
  Serial.println(pin_2_status);
  Serial.print(min:);
  Serial.println(pin_3_status);
  Serial.print(sec:);
  Serial.print(pin_4_status);
  //==debug end==
  delay(1000);
  //lcd.clear(); ref usage
}
