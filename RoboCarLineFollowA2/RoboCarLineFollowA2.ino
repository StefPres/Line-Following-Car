int BIN2 = 4;
int PWMB = 5;
int PWMA = 6;
int AIN1 = 7;
int BIN1 = 9;
int triggerPin = 12;
int echoPin = 13;
int AIN2 = 10;
float distance;
#include <Wire.h>
#define uchar unsigned char
uchar t;
//void send_data(short a1,short b1,short c1,short d1,short e1,short f1);
uchar data[16];
int thresh = 93;
int loSpeed = 0;
int medSpeed = 50;
int hiSpeed = 70;
int defSpeed = 90;
unsigned long start;
int state = 0;
int lastState = 0;

void setup() {
  // put your setup code here, to run once:


pinMode (BIN2, OUTPUT);
pinMode (PWMB, OUTPUT);
pinMode (PWMA, OUTPUT);
pinMode (AIN1, OUTPUT);
pinMode (BIN1, OUTPUT);
pinMode (AIN2, OUTPUT);
pinMode(echoPin, INPUT); //remember: the Echo pin is the microphone pin
pinMode(triggerPin, OUTPUT); //remember: the Trig pin is the speaker pin

digitalWrite (BIN2,LOW);
digitalWrite (PWMB,LOW);
digitalWrite (PWMA,LOW);
digitalWrite (AIN1,LOW);
digitalWrite (BIN1,LOW);
digitalWrite (AIN2,LOW);

delay(200);
digitalWrite(AIN1, HIGH);
digitalWrite(BIN1, HIGH);

Serial.begin(9600);
Wire.begin();
 t = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
getLine();
if (data[6]<thresh||data[8]<thresh){
  driveForward();
  state = 1;
}
else if (data[4]<thresh){
  driveLeft();
  state = 1;
}
else if (data[10]<thresh){
  driveRight();
  state = 1;
}
else if (data[2]<thresh){
  driveLeftMed();
  state = 1;
}
else if (data[12]<thresh){
  driveRightMed();
  state = 1;
}
else if (data[0]<thresh){
  driveLeftHi();
  state = 1;
}
else if (data[14]<thresh){
  driveRightHi();
  state = 1;
}
else{
  state = 0;
  if (state != (lastState)){
    start = millis();
  }
  if (millis() - start >= 500){
    stahp();
  }
}
lastState = state;
}

void goForward(int duration){
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  delay(duration);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  //delay(duration);
}
void goBackwards(int duration){
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, HIGH);
  delay(duration);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, LOW);
  //delay(duration);
}
void goRight(int duration){
  digitalWrite(BIN1, HIGH);
  delay(duration);
  digitalWrite(BIN1, LOW);
  //delay(duration);
}
void goLeft(int duration){
  digitalWrite(AIN1, HIGH);
  delay(duration);
  digitalWrite(AIN1, LOW);
  //delay(duration);
}
void driveForward(){
analogWrite (PWMB, defSpeed);
analogWrite (PWMA, defSpeed);
}
void stahp(){
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}
void driveRight(){
analogWrite (PWMB, defSpeed);
analogWrite (PWMA, hiSpeed);
}
void driveLeft(){
analogWrite (PWMB, hiSpeed);
analogWrite (PWMA, defSpeed);
}
void driveRightMed(){
analogWrite (PWMB, defSpeed);
analogWrite (PWMA, medSpeed);
}
void driveLeftMed(){
analogWrite (PWMB, medSpeed);
analogWrite (PWMA, defSpeed);
}
void driveRightHi(){
analogWrite (PWMB, defSpeed);
analogWrite (PWMA, loSpeed);
}
void driveLeftHi(){
analogWrite (PWMB, loSpeed);
analogWrite (PWMA, defSpeed);
}
void getLine(){
Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9
  while (Wire.available())   // slave may send less than requested
  {
    data[t] = Wire.read(); // receive a byte as character
    if (t < 15)
      t++;
    else
      t = 0;  
  }
  Serial.print("data[0]:");
  Serial.println(data[0]);
  Serial.print("data[2]:");
  Serial.println(data[2]);
  Serial.print("data[4]:");
  Serial.println(data[4]);
  Serial.print("data[6]:");
  Serial.println(data[6]);
  Serial.print("data[8]:");
  Serial.println(data[8]);
  Serial.print("data[10]:");
  Serial.println(data[10]);
  Serial.print("data[12]:");
  Serial.println(data[12]);
  Serial.print("data[14]:");
  Serial.println(data[14]);
}
float getDistance(){
long duration;
float cm;
float inches;
digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  /* The echo pin is used to read the signal from the PING))): a HIGH
  pulse whose duration is the time (in microseconds) from the sending
  of the ping to the reception of its echo off of an object.*/
  
  duration = pulseIn(echoPin, HIGH);
  
  // convert the time into a distance
  cm = float(duration) /29.0 /2.0;
  inches = cm /2.54;
  
  Serial.print(inches);
  Serial.println(" inches");
  

  return inches;
}
int getColor(){



  
}

