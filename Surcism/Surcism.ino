// Written and copyrighted by (Alphabetical order)
//    Amiraslan Bakhshili
//    Eltun Ibrahimov
//    Gulshan Hajibalayeva
//    Madina Shukurlu
//    Ramziyya Garazade

char cur_state = '3';

#include "Globals.h"
#include "MotorControl.h"
#include "Infrared.h"
#include "Ultrasonic.h"
#include "RemoteControl.h"


#define min_state '0'
#define infrared '1'
#define ultrasonic '2'
#define remote_control '3'
#define self_balance '4'
#define motor_check '5'
#define max_state '6'

void setup() {
  //if(debug_mode)
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
  
  stopMotors();
  
}

void loop() {
   char temp = getBlueData();
   
   if(min_state < temp && max_state > temp)
   {
    // Serial.print(temp);
    // Serial.println("\tDone");
     cur_state = temp;
   }else{
      command = temp;
    }

   //  Serial.print(temp);
   //  Serial.println("\tNormally");

  switch(cur_state){
    case infrared:
      startInfraredRobot();
    break;

    case ultrasonic: 
     startUltrasonicRobot();
    break;
    
    case remote_control:
      startRemoteControl();
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




