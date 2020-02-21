#include <SoftwareSerial.h>     //include SoftwareSerial library
#include <EasyButton.h>         //include Button library

SoftwareSerial bt(3, 2); /* (Rx,Tx) */   //create object instance for class SoftwareSerial along with dedicated rx and tx pin no's

#define BUTTON_1_PIN 4      //define pin no's for buttons
#define BUTTON_2_PIN 5
#define BUTTON_3_PIN 6
#define BUTTON_4_PIN 7

EasyButton buttonOne(BUTTON_1_PIN);   //create object instance for every button from parent class along passing the button pin no
EasyButton buttonTwo(BUTTON_2_PIN);
EasyButton buttonThree(BUTTON_3_PIN);
EasyButton buttonFour(BUTTON_4_PIN);

char switch_status = '0';
int state_all = 0;
int state1 = 0 ;
int state2 = 0 ;
int state3 = 0 ;
int state4 = 0 ;
int temp = 0;
int temp1 = 0;

void sendToApp();     //function Declaration

void setup() {
  bt.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);
  pinMode(BUTTON_4_PIN, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  buttonOne.begin();
  buttonTwo.begin();
  buttonThree.begin();
  buttonFour.begin();
}

void loop() {
  //check for button read one by one
  if (buttonOne.read())
  {
    state1 = !state1;
    if (state1 == 1)
    {
      Serial.println("a1 pressed");
      state_all = '1';
    }
    else if (state1 == 0)
    {
      Serial.println("a0 pressed");
      state_all = '0';
    }
    switch_status  = 'a';      //update the switch status
    sendToApp();                 //call the data send to app function
    digitalWrite(13, HIGH);
  }
  else if (buttonTwo.read())
  {
    state2 = !state2;
    if (state2 == 1)
    {
      Serial.println("b1 pressed");
      state_all = '1';
    }
    else if (state2 == 0)
    {
      Serial.println("b0 pressed");
      state_all = '0';
    }
    switch_status  = 'b';
    sendToApp();
    digitalWrite(13, HIGH);
  }
  else if (buttonThree.read())
  {
    state3 = !state3;
    if (state3 == 1)
    {
      Serial.println("c1 pressed");
      state_all = '1';
    }
    else if (state3 == 0)
    {
      Serial.println("c0 pressed");
      state_all = '0';
    }
    switch_status  = 'c';
    sendToApp();
    digitalWrite(13, HIGH);
  }
  else if (buttonFour.read())
  {
    state4 = !state4;
    if (state4 == 1)
    {
      Serial.println("d1 pressed");
      state_all = '1';
    }
    else if (state4 == 0)
    {
      Serial.println("d0 pressed");
      state_all = '0';
    }
    switch_status = 'd';
    sendToApp();
    digitalWrite(13, HIGH);
  }
  delay(500);
  digitalWrite(13, LOW);

}

void sendToApp()    //function Declaration
{
  if (switch_status != temp || state_all != temp1)     //condition to make sure that data is sent only once when button is present
  {
    Serial.print("Sending::  ");
    bt.write(switch_status);      //send the switch status over Bluetooth
    bt.write(state_all);
    bt.write("\n");     //for new line feed after every data send
    temp = switch_status;
    temp1 = state_all;
    Serial.print(switch_status);
    Serial.println(state_all);
    Serial.println("-------------");
  }
}
