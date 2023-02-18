#include "string.h"
#include "SRF05.h"
#include <AFMotor.h>

int Speed = 255;
int distance;
char blth;
String voice;

#define trigger 12
#define echo 13
#define MAX_DISTANCE 300
#define IR A5
#define l_motor 9  // ENA
#define l_motor_in1 7
#define l_motor_in2 6
#define r_motor 10  // ENB
#define r_motor_in3 4
#define r_motor_in4 5

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

SRF05 SRF(trigger, echo);

void setup() {
  Serial.begin(9600);
  pinMode(IR, INPUT);
  if (Serial.available() > 0)
    Serial.print("\tBluetooth Connected Seccessfully.\a");
  SRF.setCorrectionFactor(1.035);
}

void loop() {

  if (Serial.available() > 0) {
    voice = "";
    delay(2);
    voice = (Serial.readString() || Serial.read());
    delay(2);
    Serial.println(voice);
  }

  if ((voice == "turn lift") || (voice == "lift") || (voice == "go left"))
    left();

  if ((voice == "turn right") || (voice == "right") || (voice == "go right"))
    right();

  if ((voice == "forward") || (voice == "go forward"))
    forward();

  if ((voice == "dolly"))
    backward();

  if (voice == "low speed")
    Speed = 50;

  if (voice == "medium speed")
    Speed = 150;

  if (voice == "high speed")
    Speed = 255;

  if (voice == "stop")
    Stop();
}


void right() {
  digitalWrite(l_motor_in1, LOW);
  digitalWrite(l_motor_in2, HIGH);
  analogWrite(l_motor, Speed);

  digitalWrite(r_motor_in3, LOW);
  digitalWrite(r_motor_in4, HIGH);
  analogWrite(r_motor, Speed);
}

void left() {
  digitalWrite(l_motor_in1, HIGH);
  digitalWrite(l_motor_in2, LOW);
  analogWrite(l_motor, Speed);

  digitalWrite(r_motor_in3, HIGH);
  digitalWrite(r_motor_in4, LOW);
  analogWrite(r_motor, Speed);
}

void backward() {
  digitalWrite(l_motor_in1, LOW);
  digitalWrite(l_motor_in2, HIGH);
  analogWrite(l_motor, Speed);

  digitalWrite(r_motor_in3, HIGH);
  digitalWrite(r_motor_in4, LOW);
  analogWrite(r_motor, Speed);
}

void forward() {
  digitalWrite(l_motor_in1, HIGH);
  digitalWrite(l_motor_in2, LOW);
  analogWrite(l_motor, Speed);

  digitalWrite(r_motor_in3, LOW);
  digitalWrite(r_motor_in4, HIGH);
  analogWrite(r_motor, Speed);
}

void Stop() {
  digitalWrite(l_motor_in1, HIGH);
  digitalWrite(l_motor_in2, LOW);
  analogWrite(l_motor, 0);

  digitalWrite(r_motor_in3, HIGH);
  digitalWrite(r_motor_in4, LOW);
  analogWrite(r_motor, 0);
}
