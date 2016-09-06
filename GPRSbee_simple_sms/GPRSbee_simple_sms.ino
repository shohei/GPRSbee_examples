#include <GPRSbee.h>

bool sent_sms = false; 

void setup()
{
    // The code will not start unless the serial monitor is opened or 10 sec is passed
    // in case you want to operate Autonomo with external power source
    while ((!SerialUSB) && (millis()<10000))
        ;
    SerialUSB.begin(9600);
    SerialUSB.println("Here we start !! ");

    Serial1.begin(57600);
    gprsbee.initAutonomoSIM800(Serial1, BEE_VCC, BEEDTR, BEECTS);
    gprsbee.setDiag(SerialUSB);
}

void loop()
{
    // Check if we already send a previous message or not, since
    // we don't want to send the same message several times
    if (sent_sms == false) {
        sent_sms = true;
        SerialUSB.println("Switching on..");
        bool retval = gprsbee.on();
        SerialUSB.println( "...done. Retval = " );
        SerialUSB.println(retval);
        SerialUSB.println( "Sending SMS" );
        // phone number including the country code
        bool  smsSent = gprsbee.sendSMS( "+22671313609", "I <3 GPRSBee. " );
        if (smsSent) {
            SerialUSB.println( "SMS sent!" );
            // Set it True so we stop fullfilling the starting condition of the loop
            sent_sms = true;
        } else {
            SerialUSB.println( "SMS NOT SENT!" );
        }
    }
}
