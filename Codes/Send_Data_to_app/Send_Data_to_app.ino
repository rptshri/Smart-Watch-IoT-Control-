#include <SoftwareSerial.h>     //include SoftwareSerial library
#include <EasyButton.h>         //include Button library

SoftwareSerial bt(2, 3); /* (Rx,Tx) */   //create object instance for class SoftwareSerial along with dedicated rx and tx pin no's

#define BUTTON_1_PIN 4      //define pin no's for buttons
#define BUTTON_2_PIN 5
#define BUTTON_3_PIN 6
#define BUTTON_4_PIN 7

EasyButton buttonOne(BUTTON_1_PIN);   //create object instance for every button from parent class along passing the button pin no
EasyButton buttonTwo(BUTTON_2_PIN);
EasyButton buttonThree(BUTTON_3_PIN);
EasyButton buttonFour(BUTTON_4_PIN);

char switch_status = '0';
int temp = 0;

void sendToApp();     //function Declaration

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
  //check for button read one by one
  if (buttonOne.read())
  {
    Serial.println("Button 1 pressed");
    switch_status  = '1';      //update the switch status
    sendToApp();                 //call the data send to app function
  }
  else if (buttonTwo.read())
  {
    Serial.println("Button 2 pressed");
    switch_status  = '2';
    sendToApp();
  }
  else if (buttonThree.read())
  {
    Serial.println("Button 3 pressed");
    switch_status  = '3';
    sendToApp();
  }
  else if (buttonFour.read())
  {
    Serial.println("Button 4 pressed");
    switch_status = '4';
    sendToApp();
  }
}

void sendToApp()    //function Declaration
{
  if (switch_status != temp)     //condition to make sure that data is sent only once when button is present
  {
    Serial.print("Sending::  ");
    bt.write(switch_status);      //send the switch status over Bluetooth
    bt.write("\n");     //for new line feed after every data send
    temp = switch_status;
    Serial.println(switch_status);
    Serial.println("-------------");
  }
}
