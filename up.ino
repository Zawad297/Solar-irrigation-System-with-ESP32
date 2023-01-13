/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLDuuY-v3O"
#define BLYNK_DEVICE_NAME "Smart solar irrigation"
#define BLYNK_AUTH_TOKEN "zht3sugRt-UUEx2hNLmtDX26lcMj2dDd"

#define RXp2 16
#define TXp2 17


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "UIU-STUDENT";
char pass[] = "12345678";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
// BLYNK_WRITE(V0)
// {
//   // Set incoming value from pin V0 to a variable
//   int value = param.asInt();
//   digitalWrite(2,value);

//     //Serial.println(Serial2.parseInt());
    

  
// }

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  //pinMode(2,OUTPUT);
  //pinMode(2,OUTPUT);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  
    

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
    int mosture = 0;
    int temp =    0;
    int humid =   0;
  // Blynk.run();
  // timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  if (Serial2.available()>0){
    mosture = Serial2.parseInt();
    temp =    Serial2.parseInt();
    humid =   Serial2.parseInt();
  }

    
Serial.println(mosture);
Serial.println(temp);
Serial.println(humid);  

// Update state
if(temp>0){
if(temp<35){
  Blynk.virtualWrite(V6, mosture);
  Blynk.virtualWrite(V3, temp);
  Blynk.virtualWrite(V5, humid);  
}  

}  
  delay(120);  
}
