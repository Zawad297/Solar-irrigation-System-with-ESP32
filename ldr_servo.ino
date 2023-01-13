#include <Servo.h> //includes the servo library

// #include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x27, 16, 2);
// #include "ACS712.h"

Servo myservoS;
Servo myservoD;

#define ldr1 A0 // set ldr 1 Analog input pin of East ldr as an integer
#define ldr2 A1 // set ldr 2 Analog input pin of West ldr as an integer

int pos = 90; // initial position of the Horizontal movement controlling servo motor
int posD= 0;
int tolerance = 200; // allowable tolerance setting - so solar servo motor isn't constantly in motion

//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A

//ACS712  ACS(A3, 5.0, 1023, 185);

void setup(){
  myservoS.attach(2); // attaches the servo on digital pin 2 to the horizontal movement servo motor
  myservoD.attach(4); 
  Serial.begin(9600); 
  pinMode(ldr1, INPUT); //set East ldr pin as an input
  pinMode(ldr2, INPUT); //set West ldr pin as an input
  pinMode(7,OUTPUT);
  myservoS.write(pos); // write the starting position of the horizontal movement servo motor
  myservoD.write(posD);
  // lcd.init();
  // lcd.backlight();
  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("Current");

  // delay(1000);
  // lcd.clear();
  //ACS.autoMidPoint();
  
    
//delay(1000); // 1 second delay to allow the solar panel to move to its staring position before comencing solar tracking
}

void loop(){      
int valR = analogRead(ldr1); // read the value of ldr 1
int valL = analogRead(ldr2); // read the value of ldr 2

int rain = analogRead(A3);//read Rain value


//int mA = ACS.mA_AC();
//int curr = analogRead(A3);
// int volt = analogRead(A3);
// float voltage = (volt*5)/1023.0;
// float voltage_new = voltage - ((0.5*5)+0.012);
// float current = (voltage-2.51)/0.185;

// if(current<=0.04){
//     current =0;
// }

  if (rain < 300) {//check condition
    //digitalWrite(4, HIGH);
  for(posD = 0; posD <= 180; posD += 1) 
  {
    Serial.println("rain move");                                  
    myservoD.write(posD);      
    delay(15);                    
  } 

  } else if(posD == 180)  {
      for(posD = 180; posD>=0; posD-=1)     
  {
    Serial.println("no rain move");                                
    myservoD.write(posD);              
    delay(15);                     
  }

  }
else{
  Serial.println("no move");
  }  


//led part
if(valR>1000 && valL>1000){
digitalWrite(7,HIGH);  
}else{
  
digitalWrite(7,LOW);  

  if((abs(valR - valL) <= tolerance)) {

  //Serial.println("Led condition not ok");
  //delay(1000);
// Serial.print("right:");
// Serial.println(valR);
// Serial.print("Left");
// Serial.println(valL);  
// delay(1000);
//no servo motor horizontal movement will take place if the ldr value is within the allowable tolerance
}else {
if(valR > valL) // if ldr1 senses more light than ldr2 
{

  // lcd.print("curent:");
  // lcd.print(current);
  // lcd.print("A");
  // Serial.println("moving A0");
// Serial.print("on right:");
// Serial.println(valR);
// Serial.print("Left");
// Serial.println(valL);  
  
  

  pos = pos+1; // decrement the 90 degree poistion of the horizontal servo motor - this will move the panel position Eastward
  myservoS.write(pos);
  delay(200);
  //lcd.clear();
}
if(valR < valL) // if ldr2 senses more light than ldr1
{
// Serial.print("right:");
// Serial.println(valR);
// Serial.print("on Left");
// Serial.println(valL);  

  // lcd.print("curent:");
  // lcd.print(current);
  // lcd.print("A");
  // Serial.println("Moving A1");
  

  pos = pos-1; // increment the 90 degree position of the horizontal motor - this will move the panel position Westward
  myservoS.write(pos);
  delay(200);
  //lcd.clear();
 }
}
}

     
if(pos > 180) {pos = 180;} // reset the horizontal postion of the motor to 180 if it tries to move past this point
if(pos < 0) {pos = 0;} // reset the horizontal position of the motor to 0 if it tries to move past this point
myservoS.write(pos); // write the starting position to the horizontal motor

delay(50);

}
