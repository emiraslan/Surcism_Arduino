// Written and copyrighted by (Alphabetical order)
//    Amiraslan Bakhshili
//    Eltun Ibrahimov
//    Gulshan Hajibalayeva
//    Madina Shukurlu
//    Ramziyya Garazade

char cur_state = 'i';

#include "Globals.h"
#include "MotorControl.h"
#include "Infrared.h"
#include "Ultrasonic.h"

#define infrared 'i'
#define ultrasonic 'u'
#define remote_control 'r'
#define self_balance 's'
#define motor_check 'm'

void setup() {
  Serial.begin(9600);

  // Infrared Line-Follower
  pinMode(M1F, OUTPUT);
  pinMode(M2F, OUTPUT);
  pinMode(M1R, OUTPUT);
  pinMode(M2R, OUTPUT);
  
  pinMode(M1E, OUTPUT);
  pinMode(M2E, OUTPUT);

  pinMode(middleDisplay, OUTPUT);
  pinMode(leftDisplay, OUTPUT);
  pinMode(rightDisplay, OUTPUT);

  // Ultrasonic 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

  delay(action_delay);
  
  startMotors();
}

void loop() {
  switch(cur_state){
    case infrared:
      startInfraredRobot();
    break;

    case ultrasonic: 
     startUltrasonicRobot();
    break;
    
    case remote_control:
    //Todo: not implemented yet...
    break;

    case self_balance: 
    //Todo: not implemented yet...
    break;

    case motor_check: 
      goForward();
      delay(3000);
      goBackward();
      delay(3000);
      goLeft();
      delay(3000);
      goRight();
      delay(3000);
    break;

    default:
      startUltrasonicRobot();
    break;
    }
}



