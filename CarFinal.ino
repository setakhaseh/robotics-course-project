#include <Servo.h>


// SRF04-ALL
#define EchoPinR 41 //Yellow
#define TriggerPinR 40 //Green
#define EchoPinL 49 //Yellow
#define TriggerPinL 48 //Green
#define EchoPinF 53 //Yellow 
#define TriggerPinF 52 //Green 
#define EchoPinB 35 //Yellow
#define TriggerPinB 34 //Green
// Servo Motor
#define Servopin 8
// Motor B connections
#define enB 9
#define in3 7
#define in4 6


int MotorSpeed = 45 ;
long durationR;
float distanceR;
long durationL;
float distanceL;
long durationF;
float distanceF;
long durationB;
float distanceB;
float distance_R ,distance_F , distance_B ,distance_L ;
int FreeSpaceFlagR = 0;
int FreeSpaceFlagL = 0;

int ChnageDirFlagR = 0;
int ChnageDirFlagL = 0;

int ServoLocation = 0 , ServoZ = 70;
int ServoOffSet = 35;
int nochange = 0;
Servo myservo;  // create servo object to control a servo


void GoForward(int MotorSpeed) {
  analogWrite(enB, MotorSpeed);
  // Turn on motor A & B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void GoBackward(int MotorSpeed) {
  analogWrite(enB, MotorSpeed);
  // Turn on motor A & B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void StopMotor(){
    digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void setup() {
  Serial.begin(115200);
  // Set all the motor control pins to outputs
  pinMode(enB, OUTPUT);
  //pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //pinMode(in3, OUTPUT);
  //pinMode(in4, OUTPUT);
  myservo.attach(Servopin, 600, 2300);
  // Turn off motors - Initial state
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  //digitalWrite(in3, LOW);
  //digitalWrite(in4, LOW);
  pinMode(TriggerPinR, OUTPUT); // Sets the TriggerPin as an Output
  pinMode(EchoPinR, INPUT); // Sets the EchoPin as an Input
  pinMode(TriggerPinL, OUTPUT); // Sets the TriggerPin as an Output
  pinMode(EchoPinL, INPUT); // Sets the EchoPin as an Input
  pinMode(TriggerPinF, OUTPUT); // Sets the TriggerPin as an Output
  pinMode(EchoPinF, INPUT); // Sets the EchoPin as an Input
  pinMode(TriggerPinB, OUTPUT); // Sets the TriggerPin as an Output
  pinMode(EchoPinB, INPUT); // Sets the EchoPin as an Input
  ServoLocation = 76;
  delay(1000);
}
float SRF04_R()
{
  digitalWrite(TriggerPinR, LOW);
  delayMicroseconds(2);
  //Set the TriggerPin on HIGH state for 10 microseconds
  digitalWrite(TriggerPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPinR, LOW);
  //Read the EchoPin, returning the sound wave travel time in microseconds
  durationR = pulseIn(EchoPinR, HIGH);
  //Calculate the distance
  distanceR = durationR * 0.034 / 2;
  Serial.print("r:");
  Serial.println(distanceR);
  delay(100);

  return distanceR ;
}
float SRF04_L()
{
  digitalWrite(TriggerPinL, LOW);
  delayMicroseconds(2);
  //Set the TriggerPin on HIGH state for 10 microseconds
  digitalWrite(TriggerPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPinL, LOW);
  //Read the EchoPin, returning the sound wave travel time in microseconds
  durationL = pulseIn(EchoPinL, HIGH);
  //Calculate the distance
  distanceL = durationL * 0.034 / 2;
  Serial.print("l:");
  Serial.println(distanceL);
  delay(100);

  return distanceL ;
}
float SRF04_F()
{
  digitalWrite(TriggerPinF, LOW);
  delayMicroseconds(2);
  //Set the TriggerPin on HIGH state for 10 microseconds
  digitalWrite(TriggerPinF, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPinF, LOW);
  //Read the EchoPin, returning the sound wave travel time in microseconds
  durationF = pulseIn(EchoPinF, HIGH);
  //Calculate the distance
  distanceF = durationF * 0.034 / 2;
  Serial.print("f:");
  Serial.println(distanceF);
  delay(100);

  return distanceF ;
}
float SRF04_B()
{
  digitalWrite(TriggerPinB, LOW);
  delayMicroseconds(2);
  //Set the TriggerPin on HIGH state for 10 microseconds
  digitalWrite(TriggerPinB, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPinB, LOW);
  //Read the EchoPin, returning the sound wave travel time in microseconds
  durationB = pulseIn(EchoPinB, HIGH);
  //Calculate the distance
  distanceB = durationB * 0.034 / 2;
  Serial.print("b:");
  Serial.println(distanceB);
  delay(100);

  return distanceB ;
}
void loop() {

  myservo.write(ServoLocation);


  if (nochange == 0)
  {
     distance_R = SRF04_R();
    GoForward(70);
  }


  if (distance_R < 15 && nochange == 0)
  {
    GoForward(70);

  } else if (distance_R > 20 && nochange == 0)
  {
    FreeSpaceFlagR = 1;
    GoForward(70);
  }
  if (FreeSpaceFlagR == 1 && distance_R < 15 && nochange == 0)
  {
    ChnageDirFlagR = 1;

    ServoLocation = ServoZ + ServoOffSet;
    myservo.write(ServoLocation);
    GoBackward(70);
    nochange = 1;

  }

  if (nochange == 1)
  {
    GoBackward(70);
    delay(4000);
    ServoLocation = ServoZ - ( ServoOffSet);
      myservo.write(ServoLocation);
      delay(2000);
    ServoLocation = ServoZ +ServoOffSet ;
      myservo.write(ServoLocation);
    GoForward(70);
    for(int i =0 ; i < 15 ; i++){
      if(SRF04_F() < 7){
        StopMotor();
      }
    }
      
    StopMotor();
    delay(1000);

     distance_B = SRF04_B();
    nochange = 3;
  }

  if (nochange == 2)
  {
    GoForward(70);
     distance_F = SRF04_F();
    if (distance_F < 6)
    {
      ServoLocation = ServoZ  + ServoOffSet;
    nochange = 3;
    }
    
  }

  if (nochange == 3)
  {
   StopMotor();

    
  }


}



