#include <TinyGPS++.h>
#include <SoftwareSerial.h>
TinyGPSPlus gps;
SoftwareSerial gpsSerial(50,51); // RX || TX 
double latitude, longitude; 
double NWLat, NWLng, NELat, NELng, SWLat, SWLng, SELat, SELng;
String textMessage;
String coordinate;
void setup() {
  Serial.begin(9600); 
  gpsSerial.begin(9600);
  Serial2.begin(4800);
  // Give time to your GSM shield log on to network
  delay(2000);

  // AT command to set SIM900 to SMS mode
  Serial2.print("AT+CMGF=1\r"); 
  delay(100);
  Serial2.println();
  for (int i = 1; i <= 15; i++) {
    Serial.print("AT+CMGD=");
    Serial.println(i);
    delay(200);
}
}
void loop() {
  getLoc();
  geoDomain();
  if(Serial2.available()>0){
    textMessage = Serial2.readString();
   textMessage.toUpperCase();   
    delay(10);
  } 
  if(textMessage.indexOf("NWLA")>=0){
      coordinate = textMessage.substring(55);
      NWLat = coordinate.toDouble();
      Serial.println("SMS NWLA RECEIVED");
    }
  if(textMessage.indexOf("NWLN")>=0){
      coordinate = textMessage.substring(55);
      NWLng = coordinate.toDouble();
      Serial.println("SMS NWLN RECEIVED");
    }
  if(textMessage.indexOf("NELA")>=0){
      coordinate = textMessage.substring(55);
      NELat = coordinate.toDouble();
      Serial.println("SMS NELA RECEIVED");
    }
  if(textMessage.indexOf("NELN")>=0){
      coordinate = textMessage.substring(55);
      NELng = coordinate.toDouble();
      Serial.println("SMS NELN RECEIVED");
    }
  if(textMessage.indexOf("SWLA")>=0){
      coordinate = textMessage.substring(55);
      SWLat = coordinate.toDouble();
      Serial.println("SMS SWLA RECEIVED");
    }
  if(textMessage.indexOf("SWLN")>=0){
      coordinate = textMessage.substring(55);
      SWLng = coordinate.toDouble();
      Serial.println("SMS SWLN RECEIVED");
    }
  if(textMessage.indexOf("SELA")>=0){
      coordinate = textMessage.substring(55);
      SELat = coordinate.toDouble();
      Serial.println("SMS SELA RECEIVED");
    }
  if(textMessage.indexOf("SELN")>=0){
      coordinate = textMessage.substring(55);
      SELng = coordinate.toDouble();
      Serial.println("SMS SELN RECEIVED");
    }

}
void getLoc(){
      while(gpsSerial.available()){
      int data = gpsSerial.read();
      if(gps.encode(data)){
          latitude = gps.location.lat(); 
          longitude = gps.location.lng();
          Serial.print("latitude: "); 
          Serial.println(latitude, 6); 
          Serial.print("longitude: "); 
          Serial.println(longitude, 6); 
          
        }
    }
    delay(500);
}
void geoDomain(){
        if( latitude <= NWLat and latitude >= SWLat and longitude >= NWLng and longitude <= SELng ) {
        Serial.print("Within geolocation domain");
        delay(500); 
      }
    else{
        Serial.print("out of geolocation domain");
        delay(500); 
      }
   Serial.println();
      } 
