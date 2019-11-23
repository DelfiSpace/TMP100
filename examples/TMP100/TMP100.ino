/* This code test the temperature measurement
    from TMP100 thermal sensor
   code written by J.W.Chia @ 6/3/2017
*/

#include <DWire.h>
#include <DSerial.h>
#include <TMP100.h>

DWire wire;
DSerial serial;

TMP100 TMP_1(wire, 0x49);   //the current test board used TMP101, with ADD0 float (b1001001)

//Parameters
signed short temp;

void setup() {
  wire.begin();          // initialize I2C master
  serial.begin();       //initialize debug UART

  delay(20);           // ensure the serial port is initialized


  TMP_1.init();

  delay(1000);

  serial.println();
  serial.println("---------------------------------------------------------");
  serial.println("-------------------   TMP100 TESTER    ------------------");
  serial.println("---------------------------------------------------------");
  serial.println();

  delay(20);
}

void loop()
{
  if (TMP_1.getTemperature(temp) == 0)
  {
    serial.print("The temperature measurement is: ");
    serial.print(temp, DEC);
    serial.print(" E-1 DegC");
    serial.println();
  }
  else
  {
    serial.print("Fail");
  }
  delay(1000);
}
