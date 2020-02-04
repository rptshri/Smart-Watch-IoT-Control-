#include <SoftwareSerial.h>
#include <EasyButton.h>

SoftwareSerial bt(2, 3); /* (Rx,Tx) */

#define BUTTON_1_PIN 4
#define BUTTON_2_PIN 5
#define BUTTON_3_PIN 6
#define BUTTON_4_PIN 7

EasyButton buttonOne(BUTTON_1_PIN);
EasyButton buttonTwo(BUTTON_2_PIN);
EasyButton buttonThree(BUTTON_3_PIN);
EasyButton buttonFour(BUTTON_4_PIN);

char swstatus = '0';
int temp = 0;
//char senddata = '0';

void sendble();

void setup() {
  bt.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);
  pinMode(BUTTON_4_PIN, INPUT_PULLUP);
  buttonOne.begin();
  buttonTwo.begin();
  buttonThree.begin();
  buttonFour.begin();
}

void loop() {

  if (buttonOne.read())
  {
    Serial.println("Button 1 pressed");
    swstatus  = '1';
    sendble();
  }
  else if (buttonTwo.read())
  {
    Serial.println("Button 2 pressed");
    swstatus  = '2';
    sendble();
  }
  else if (buttonThree.read())
  {
    Serial.println("Button 3 pressed");
    swstatus  = '3';
    sendble();
  }
  else if (buttonFour.read())
  {
    Serial.println("Button 4 pressed");
    swstatus = '4';
    sendble();
  }
}

void sendble()
{
  if (swstatus != temp)     //condition to make sure that data is sent only once when button is present
  {
    Serial.print("Sending::  ");
    bt.write(swstatus);
    bt.write("\n");     //for new line feed after every data send
    temp = swstatus;
    Serial.println(swstatus);
    Serial.println("-------------");

  }

}
