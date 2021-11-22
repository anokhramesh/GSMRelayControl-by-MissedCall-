#include <SoftwareSerial.h>//Install SoftwareSerial Library 
#include "Adafruit_FONA.h"// Install Adafruit FONA library
 
#define FONA_RX            2//Connect RX pin of GSM module to Digital Pin 2 of Arduino board
#define FONA_TX            3//Connect TX pin of GSM module to Digital Pin 3 of Arduino board
#define FONA_RST           4// No connection
 
#define FONA_RI_INTERRUPT  0
int x=1;
int relay =12;// Connect low active Relay IN Pin to Arduino Digital pin 12
char sendto[21] = "+971557407961"; // Enter your Number here.
char message[141] = "GSM Switch is Ready"; // this message will send when GSM in connected to network.
char switchon[141]= "SWITCH STATUS IS- ON"  ;//this message will send when Relay will Turned ON
char switchoff[141]= "SWITCH STATUS IS- OFF";//this message will send when Relay will Turned OFF
String ramesh;
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
 
void setup() {
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);
  Serial.begin(115200);
  Serial.println(F("FONA incoming call example"));
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(3000);
  fonaSS.begin(4800); // if you're using software serial
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));
 
  if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) {
    Serial.println(F("Caller id notification enabled."));
  }
  else {
    Serial.println(F("Caller id notification disabled"));
  }
 
   fona.sendSMS(sendto, message);
   delay(1000);
}
 
void loop(){
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    digitalWrite(relay,HIGH);
    x=1;
     }
     else
     fona.callerIdNotification(true, FONA_RI_INTERRUPT);
  char phone[32] ={0};
   if (x==1)
 {
  if(fona.incomingCallNumber(phone)){
   Serial.println(F("RING!"));
    Serial.print(F("Phone Number: "));
    ramesh=phone;
    if(ramesh==sendto)
    {
    Serial.println(ramesh);
    digitalWrite(relay,LOW);
    Serial.print("ON");
   fona.sendSMS(sendto, switchon);
   delay(35000);
    if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) {
    Serial.println(F("Caller id notification enabled."));
    x=2;
    } // reenable call id
  }
else if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) 
    Serial.println(F("Caller id notification enabled."));

  
  }  // incoming call check
 }// X==1 loop

 if (x==2)
 {
  if(fona.incomingCallNumber(phone)){
    
    Serial.println(F("RING!"));
    Serial.print(F("Phone Number: "));
 ramesh=phone;
    if(ramesh==sendto)
    {
    Serial.println(ramesh);
    digitalWrite(relay,HIGH);
    Serial.print("OFF");
    fona.sendSMS(sendto, switchoff);
    delay(35000);
    if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) {
    Serial.println(F("Caller id notification enabled."));
    x=1;
  } // reenable call id
    }
  else if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) 
    Serial.println(F("Caller id notification enabled."));
  } // incoming call check
 }// X==2 loop

 
}//Loop
