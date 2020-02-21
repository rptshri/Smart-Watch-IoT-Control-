
#include "ESC.h"

#include <SoftwareSerial.h>

#include <Servo.h>

#define LED_PIN (13)            // Pin for the LED
#define SPEED_MIN (1000)        // Set the Minimum Speed in microseconds
#define SPEED_MAX_THRUST (2200) // Set the Minimum Speed in microseconds
#define SPEED_MAX_LIFT (3000)
#define ARM_VALUE (500)
#define MOTOR_DIR_PIN_A (10)
#define MOTOR_DIR_PIN_B (11)
#define MOTOR_SPEED_PWM (9)

ESC ThrustFan(9, SPEED_MIN, SPEED_MAX_THRUST, ARM_VALUE); // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
ESC LiftFan(10, SPEED_MIN, SPEED_MAX_LIFT, ARM_VALUE);    // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
int oESC;                                                 // Variable for the speed sent to the ESC
int ThrustOnceFlag = 1;
int MotorOnceFlag = 1;

SoftwareSerial bluetooth(2, 3); // RX | TX
int SensorPin = A0;             // select the input pin for the potentiometer
int SensorValue = 0;
int SpeedReached = 0;
char Flag = 0;

Servo myservo; // create servo object to control a servo
int Pos = 90;  // variable to store the servo position
int ServoOnceFlag = 1;
int ServoToDefaultFlag = 1;

char ReadBluetooth(); //Function Declarations
void GetPotValue();
void TrustFanOn();
void TrustFanOff();
void LiftFanOn();
void LiftFanOff();
void TurnLeftServo();
void TurnRightServo();
void ServoAtDefaultPos();
void CollectorMotorLift();
void CollectorMotorRelease();

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT); // LED Visual Output
  pinMode(MOTOR_DIR_PIN_A, OUTPUT); //Motor Dir Output A
  pinMode(MOTOR_DIR_PIN_B, OUTPUT); //Motor Dir output B
  pinMode(MOTOR_SPEED_PWM, OUTPUT); //Motor speed control PWM
  digitalWrite(LED_PIN, LOW);
  ThrustFan.arm();
  LiftFan.arm();               // Send the Arm value so the ESC will be ready to take commands
  digitalWrite(LED_PIN, HIGH); // LED High Once Armed
  delay(1000);                 // Wait for a while
  GetPotValue();

  bluetooth.begin(9600);

  myservo.attach(6); // attaches the servo on pin 9 to the servo object
  delay(500);
  myservo.write(Pos);
}

void loop()
{
  switch (ReadBluetooth())
  {
    case 'w':
      TrustFanOn();
      Serial.println("w");
      break;
    case 'a':
      TurnLeftServo();
      Serial.println("l");

      break;
    case 'd':
      TurnRightServo();
      Serial.println("r");

      break;
    case 'o':
      ServoAtDefaultPos();
      Serial.println("def");

      break;
    case '0':
      SpeedReached = 0;
      TrustFanOff();
      Serial.println("off");

      break;

    case '1':
      LiftFanOn();
      break;

    case 'M':
      LiftFanOff();
      break;

    case '2':
      CollectorMotorLift();
      break;

    case 'N':
      CollectorMotorRelease();
      break;

    default:
      Serial.println("default");
      TrustFanOff();
      ServoAtDefaultPos();
      break;
  }
  delay(10);
}

char ReadBluetooth()
{
  if (bluetooth.available())
    Flag = bluetooth.read();
  //  Serial.print(Flag);
  return Flag;
}

void GetPotValue()
{
  SensorValue = analogRead(SensorPin);
  Serial.print(SensorValue);
  Serial.print("     ");
  SensorValue = map(SensorValue, 0, 1023, SPEED_MIN, SPEED_MAX_LIFT);
  Serial.println(SensorValue);
}

void TrustFanOn()
{
  if (ThrustOnceFlag == 1)
  {
    if (SpeedReached == 0)
    {
      Serial.print("Thrust Fan On SpeedIncreasing   ");
      for (int i = 1100; i < SPEED_MAX_THRUST; i += 5)
      {
        ThrustFan.speed(i);
        Serial.print(".");
      }
      Serial.println();
      SpeedReached = 1;
    }
    else
    {
      Serial.println("Thrust Fan On SpeedReached");
      ThrustFan.speed(SPEED_MAX_THRUST);
    }
    ThrustOnceFlag = 0;
  }
}

void TrustFanOff()
{
  if (ThrustOnceFlag == 0)
  {
    Serial.println("Thrust Fan Off");
    ThrustFan.speed(ARM_VALUE);

    ThrustOnceFlag = 1;
  }
}

void LiftFanOn()
{
    Serial.println("Lift Fan On");
  LiftFan.speed(SensorValue);
}

void LiftFanOff()
{
    Serial.println("Lift Fan Off");
  LiftFan.speed(ARM_VALUE);
}

void TurnLeftServo()
{
  if (ServoOnceFlag == 1)
  {
    Pos = 0;
    myservo.write(Pos); // tell servo to go to position in variable 'pos'
    delay(50);          // waits 50ms for the servo to reach the position

    ServoOnceFlag = 0;
  }
}

void TurnRightServo()
{
  if (ServoOnceFlag == 1)
  {
    Pos = 180;
    myservo.write(Pos); // tell servo to go to position in variable 'pos'
    delay(50);          // waits 1ms for the servo to reach the position

    ServoOnceFlag = 0;
  }
}

void ServoAtDefaultPos()
{
  if (ServoOnceFlag == 0)
  {
    Pos = 90;
    myservo.write(Pos); // tell servo to go to position in variable 'pos'

    ServoOnceFlag = 1;
  }
}

void CollectorMotorLift()
{
  if (MotorOnceFlag == 1) {
    Serial.println("Lifting!");
    digitalWrite(MOTOR_DIR_PIN_A, HIGH);
    digitalWrite(MOTOR_DIR_PIN_B, LOW);
    analogWrite(MOTOR_SPEED_PWM, 128);
    delay(2000);
    digitalWrite(MOTOR_DIR_PIN_A, LOW);
    digitalWrite(MOTOR_DIR_PIN_B, LOW);
    analogWrite(MOTOR_SPEED_PWM, 0);
    Serial.println("Lifted!");
    MotorOnceFlag = 0;
  }
}

void CollectorMotorRelease()
{
  if (MotorOnceFlag == 0) {
    Serial.println("Releasing!");
    digitalWrite(MOTOR_DIR_PIN_A, LOW);
    digitalWrite(MOTOR_DIR_PIN_B, HIGH);
    analogWrite(MOTOR_SPEED_PWM, 128);
    delay(2000);
    digitalWrite(MOTOR_DIR_PIN_A, LOW);
    digitalWrite(MOTOR_DIR_PIN_B, LOW);
    analogWrite(MOTOR_SPEED_PWM, 0);
    Serial.println("Released!");
    MotorOnceFlag = 1;
  }
}
