#include <Servo.h> //servo library
Servo myservo; // create servo object to control servo
int Echo = A4;  
int Trig = A5; 
int ENA=5;
int ENB=11; 
int IN1=6;
int IN2=7;
int IN3=8;
int IN4=9;
int ABS = 150;
int distance = 0 ;
int angle = 135;
int angleIncrement = 50;

void setup()
{
  myservo.attach(3);
  Serial.begin(9600);
  pinMode(IN1,OUTPUT); // Left
  pinMode(IN2,OUTPUT); // Left
  pinMode(IN3,OUTPUT); // Right
  pinMode(IN4,OUTPUT); // Right
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  digitalWrite(ENA,HIGH);  
  digitalWrite(ENB,HIGH);      

}

void _forward(short duration)
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  
  delay(duration);
}

void _stop(short duration)
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  
  delay(duration);
}

void _back(short duration)
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);      
  digitalWrite(IN4,LOW);
  
  delay(duration);
}

void _right(float percentage)
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  
  delay(1000*percentage);
}

void _left(float percentage)
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
 
  delay(1000*percentage);
}

 /*Ultrasonic distance measurement Sub function*/
int Distance_test()   
{
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance/58;       
  return (int)Fdistance;
}

void setAngleIncrement()
{
  if (angleIncrement == 50 && angle > 180) {
    angleIncrement = -50;
  } else if (angleIncrement == -50 && angle < 90) {
    angleIncrement = 50;
  } else {
    angleIncrement = angleIncrement;
  }
}

void setAngle()
{
  setAngleIncrement();
  angle += angleIncrement; 
  Serial.println(angle);
}

void loop()
{
  setAngle();
  myservo.write(angle);
  delay(50);
  _forward(5);
  distance = Distance_test();
  
  if (distance <= 35) {
    _stop(500);
    _back(250);
    _right(0.125); // Turn around
  }
}

