#include <SoftwareSerial.h>
SoftwareSerial bluetooth(2, 3); // RX | TX

#define MOTOR_DIR_PIN_A (10)
#define MOTOR_DIR_PIN_B (11)
int MotorOnceFlag = 1;
char Flag = 0;

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_DIR_PIN_A, OUTPUT); //Motor Dir Output A
  pinMode(MOTOR_DIR_PIN_B, OUTPUT); //Motor Dir output B
  bluetooth.begin(9600);
}
void loop() {
  Serial.println(MotorOnceFlag);
  switch (ReadBluetooth())
  {
    case '2':
      CollectorMotorLift();
      break;

    case 'N':
      CollectorMotorRelease();
      break;
    default:
      Serial.println("default");
      //      TrustFanOff();
      //      ServoAtDefaultPos();
      break;
  }
}

char ReadBluetooth()
{
  if (bluetooth.available())
    Flag = bluetooth.read();
  //  Serial.print(Flag);
  return Flag;
}

void CollectorMotorLift()
{
  if (MotorOnceFlag == 1) {
    Serial.println("Lifting!");
    digitalWrite(MOTOR_DIR_PIN_A, HIGH);
    digitalWrite(MOTOR_DIR_PIN_B, LOW);
    //    analogWrite(MOTOR_SPEED_PWM, 128);
    delay(2000);
    digitalWrite(MOTOR_DIR_PIN_A, LOW);
    digitalWrite(MOTOR_DIR_PIN_B, LOW);
    //    analogWrite(MOTOR_SPEED_PWM, 0);
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
    //    analogWrite(MOTOR_SPEED_PWM, 128);
    delay(2000);
    digitalWrite(MOTOR_DIR_PIN_A, LOW);
    digitalWrite(MOTOR_DIR_PIN_B, LOW);
    //    analogWrite(MOTOR_SPEED_PWM, 0);
    Serial.println("Released!");
    MotorOnceFlag = 1;
  }
}
