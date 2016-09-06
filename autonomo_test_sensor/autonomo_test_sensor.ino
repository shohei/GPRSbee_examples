/****************************************************************
 * ReadSHT2x
 *  An example sketch that reads the sensor and prints the
 *  relative humidity to the PC's SerialUSB port
 *
 *  Tested with:
 *    - SHT21-Breakout Humidity sensor from Modern Device
 *    - SHT2x-Breakout Humidity sensor from MisensO Electronics
 ***************************************************************/

#include <Wire.h>
#include <Sodaq_SHT2x.h>


void setup()
{
  Wire.begin();
  SerialUSB.begin(9600);
}

void loop()
{
  SerialUSB.print("Humidity(%RH): ");
  SerialUSB.print(SHT2x.GetHumidity());
  SerialUSB.print("     Temperature(C): ");
  SerialUSB.println(SHT2x.GetTemperature());
  SerialUSB.print("     Dewpoint(C): ");
  SerialUSB.println(SHT2x.GetDewPoint());
  
  delay(1000);
}

