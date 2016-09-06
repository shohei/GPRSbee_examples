#include <GPRSbee.h>
#include <Wire.h>
#include <Sodaq_SHT2x.h>

#define APN "internet"
#define THINGSPEAKURL "http://api.thingspeak.com/update"
//change here for your APIKEY
#define APIKEY "ZDUF837VPFFAA4ZF"

void doHttpGet();

void setup()
{
    // The code will not start unless the serial monitor is opened or 10 sec is passed
    // in case you want to operate Autonomo with external power source
    while ((!SerialUSB) && (millis()<10000))
    ;
    SerialUSB.begin(9600);
    SerialUSB.println("Here we start !! ");
    Wire.begin();

    Serial1.begin(57600);
    gprsbee.initAutonomoSIM800(Serial1, BEE_VCC, BEEDTR, BEECTS);
    gprsbee.setDiag(SerialUSB);

    doHttpGet();
}

void doHttpGet(){
  String msg;
  msg += "&field1=";
  msg += String(SHT2x.GetTemperature());
  msg += "&field2=";
  msg += String(SHT2x.GetHumidity());
  delay(100);

  String url;
  url += THINGSPEAKURL;
  url += "?api_key=";
  url += APIKEY;
  url += msg;

  const char* getURL = (const char *) url.c_str();
  SerialUSB.println("GET requet to following URL");
  SerialUSB.println(getURL);

  char buffer[20];
  if (gprsbee.doHTTPGET(APN, getURL, buffer, sizeof(buffer))) {
  	SerialUSB.println("done.");
  } else {
  	SerialUSB.println("aborted.");
  }

}


void loop()
{
  // uncomment here to iterate uploading in every 1 minute
	// doHttpGet();
	// delay(60*1000);
}


