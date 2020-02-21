#include <SoftwareSerial.h>
SoftwareSerial EEBlue(3, 2); // RX | TX
void setup()
{

  Serial.begin(9600);
  EEBlue.begin(9600);  //Default Baud for comm, it may be different for your Module.
  Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!.");

}
int counter = 0;
void loop()
{
  counter += 1;
  // Feed any data from bluetooth to Terminal.
  if (EEBlue.available())
    Serial.write(EEBlue.read());


  EEBlue.write(counter);
  delay(500);
}
