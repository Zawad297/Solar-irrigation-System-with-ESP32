//dh11 include part
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 10


#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//char auth[] = "FrTUdw4eTT679ZihMb9i6C20bxRzQ69P";//Enter your Auth token
//char ssid[] = "2020_plus";//Enter your WIFI name
//char pass[] = "ztzz2020";//Enter your WIFI password



int water;//random variable
int mosture;
int temp;
int humid;
//int servoPin = 9;


void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT); //output pin for relay board, this will sent signal to the relay
  Serial.begin(9600);
  //servo.attach(servoPin);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM IS ON ");
  lcd.print("");
  delay(1000);
  lcd.clear();
//  lcd.println("Starting wifi");
//  delay(1000);
//  lcd.clear();
  

}

void loop() {
  //Serial.print("Moisture is ");
  mosture = analogRead(A0);
  DHT.read(DHT11_PIN);
  temp = DHT.temperature;
  humid = DHT.humidity;

  //Serial.println(mosture);
  if (mosture>300){
    digitalWrite(2, LOW);
    
    Serial.println(mosture);
    Serial.println(temp);
    Serial.println(humid);


    lcd.print("Mstr:");
    lcd.print(mosture);
    lcd.print(" Tmp:");
    lcd.print(temp);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Wtr:ON ");
    lcd.print("Humid:");
    lcd.print(humid);
    delay(1000);
    lcd.clear();
  }
  else{
    digitalWrite(2, HIGH);
    Serial.println(mosture);
    Serial.println(temp);
    Serial.println(humid);

    //lcd.setCursor(0, 1);
    lcd.print("Mstr:");
    lcd.print(mosture);
    lcd.print(" Tmp:");
    lcd.print(temp);
    lcd.print("C");
    //Serial.println("Mosture is ok");
    lcd.setCursor(0,1);
    lcd.print("Wtr:off ");
    lcd.print("Humid:");
    lcd.print(humid);
    delay(1000);
    lcd.clear();

  }
  delay(1000);
}
