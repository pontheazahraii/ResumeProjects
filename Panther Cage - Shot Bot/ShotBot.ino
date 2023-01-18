
// Libraries for modules
#include <AFMotor.h> //Import library to control motor shield
#include <Servo.h>   //Import library to control the servo
#include <NewPing.h> //add Ultrasonic sensor library
//#include <IRremote.h>
#include <NECIRrcv.h>

// Define Left & Right DC Motor Pins 
#define LEFT_FORWARD 7
#define LEFT_BACKWARD 6
#define RIGHT_FORWARD 5
#define RIGHT_BACKWARDS 4
#define RIGHT_PWM 2
#define LEFT_PWM 3

#define TRIG_PIN 9 // Pin A0 on the Motor Drive Shield soldered to the ultrasonic sensor
#define ECHO_PIN 10 // Pin A1 on the Motor Drive Shield soldered to the ultrasonic sensor

#define RECV_PIN 8

#define MAX_SPEED 255

#define MAX_DISTANCE 300 // sets maximum useable sensor measuring distance to 300cm
#define COLL_DIST 30 // sets distance at which robot stops and reverses to 30cm
#define TURN_DIST COLL_DIST+20 // sets distance at which robot veers away from object
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // sets up sensor library to use the correct pins to measure distance.
Servo myservo;

int leftDistance, rightDistance; //distances on either side
int curDist = 0;
String motorSet = "";
int speedSet = 0;

int i;
int dir;

NECIRrcv IR_1(RECV_PIN);
//IRrecv irrecv(RECV_PIN);
//decode_results results;
 
void setup() 
{
  // Set pin direction
  pinMode(LEFT_BACKWARD,OUTPUT);
  pinMode(LEFT_FORWARD,OUTPUT);
  pinMode(RIGHT_BACKWARDS,OUTPUT);
  pinMode(RIGHT_FORWARD,OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);


  // Start receiver
  //irrecv.enableIRIn(); // Start the receiver
  //Serial.begin(9600);
  IR_1.begin();

  myservo.attach(11);  // attaches the servo on pin 10 (SERVO_1 on the Motor Drive Shield to the servo object 
  myservo.write(90); // tells the servo to position at 90-degrees ie. facing forward.
}

//---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
void loop() {
  /*myservo.write(90);  // move eyes forward
  delay(90);
  curDist = readPing();   // read distance
  if (curDist < COLL_DIST) {changePath();}  // if forward is blocked change direction
  MoveForward();  // move forward
  delay(500);*/

  while(IR_1.available())
  {
     // Serial.println(IR_1.read(),HEX);
      
     switch(IR_1.read())
    {
      case 0xFF16E9: // 0  

        myservo.write(90);  // move eyes forward
        delay(90);
        curDist = readPing();   // read distance
        if (curDist < COLL_DIST) {changePath();}  // if forward is blocked change direction
        MoveForward();  // move forward
        delay(500);
        break;

      case 0xFF0CF3: // 1    
        Stop();
        break;

      case 0xFF18E7: // 2
        MoveForward();
        break;

      case 0xFF5EA1: // 3
        Stop();
        break;

      case 0xFF08F7: // 4
        turnLeft();
        break;

      case 0xFF1CE3: // 5
        Stop();
        break;

      case 0xFF5AA5: // 6
        turnRight();
        break;

      case 0xFF42BD: // 7
        Stop();
        break;

      case 0xFF52AD: // 8
        MoveBackward();
        break;

      case 0xFF4AB5: // 9 
        Stop();
        break;

     }// End Case
     
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------

void changePath() {
  Stop();   // stop forward movement
  myservo.write(36);  // check distance to the right
    delay(500);
    rightDistance = readPing(); //set right distance
    delay(500);
    myservo.write(144);  // check distace to the left
    delay(700);
    leftDistance = readPing(); //set left distance
    delay(500);
    myservo.write(90); //return to center
    delay(100);
    compareDistance();
  }

  
void compareDistance()   // find the longest distance
{
  if (leftDistance>rightDistance) //if left is less obstructed 
  {
    turnLeft();
  }
  else if (rightDistance>leftDistance) //if right is less obstructed
  {
    turnRight();
  }
   else //if they are equally obstructed
  {
    turnLeft();
    delay(170);
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------

int readPing() { // read the ultrasonic sensor distance
  delay(70);   
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

//-------------------------------------------------------------------------------------------------------------------------------------
void Stop() {
  digitalWrite(RIGHT_FORWARD,LOW);
  digitalWrite(RIGHT_BACKWARDS,LOW);
  digitalWrite(LEFT_FORWARD,LOW);
  digitalWrite(LEFT_BACKWARD,LOW);
}

void Accelerate() {
  for (int i = 60; i < MAX_SPEED; i += 2) {
    analogWrite(RIGHT_PWM, i);
    analogWrite(LEFT_PWM, i);
    delay(10);
  }
}

void MoveForward() {
  dir = 1;
  digitalWrite(RIGHT_FORWARD,HIGH);
  digitalWrite(RIGHT_BACKWARDS,LOW);
  digitalWrite(LEFT_FORWARD,HIGH);
  digitalWrite(LEFT_BACKWARD,LOW);
  Accelerate();
}

void MoveBackward() {
  dir = 2;
  digitalWrite(RIGHT_BACKWARDS,HIGH);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD,HIGH);
  digitalWrite(LEFT_FORWARD,LOW);
  Accelerate();
}

void turnRight() {
  dir = 3;
  
  digitalWrite(RIGHT_BACKWARDS,HIGH);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(LEFT_BACKWARD,LOW);
  digitalWrite(LEFT_FORWARD,HIGH);
  Accelerate(); 
  delay(1500); // run motors this way for 1500        

  dir = 1;
  digitalWrite(RIGHT_BACKWARDS,LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD,LOW);
  digitalWrite(LEFT_FORWARD,HIGH);
  
}  

void turnLeft() {
  dir = 4;
  
  digitalWrite(RIGHT_BACKWARDS,LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD,HIGH);
  digitalWrite(LEFT_FORWARD,LOW);
  Accelerate(); 
  delay(1500); // run motors this way for 1500  

  dir = 1;
  digitalWrite(RIGHT_BACKWARDS,LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(LEFT_BACKWARD,LOW);
  digitalWrite(LEFT_FORWARD,HIGH);
} 
