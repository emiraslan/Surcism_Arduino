
class SensorData{
  public: 
    short left_data;
    short middle_data;
    short right_data;  

    void displayData()
    {
       Serial.print("Left: ");
       Serial.print(left_data);
       Serial.print("\tMiddle: ");
       Serial.print(middle_data);
       Serial.print("\tRight: ");
       Serial.print(right_data);
       
       Serial.print("\tLeft-bar: ");
       Serial.print(left_barrier);
       Serial.print("\tMiddle-bar: ");
       Serial.print(middle_barrier);
       Serial.print("\tRight-bar: ");
       Serial.println(right_barrier);
    }

    bool isLeftBlack(){
      if(left_data > left_barrier){
          return true;
      }
      return false;
    }

    bool isMiddleBlack(){
      if(middle_data > middle_barrier){
          return true;
      }
      return false;
    }

    bool isRightBlack(){
      if(right_data > right_barrier){
          return true;
      }
      return false;
    }
};


//Todo: Optimize this function. Remove hard coded data.  
void calibrateWithPotentiometer(){
 
  int sensorValue = analogRead(A3);
  int sensorValue2 = analogRead(A4);
  int sensorValue3 = analogRead(A5);
  
  left_barrier = sensorValue * (1000.0 / 1023.0);
  middle_barrier = sensorValue2 * (1000.0 / 1023.0);
  right_barrier = sensorValue3 * (1000.0 / 1023.0);
}

SensorData readData(){
  SensorData data;
  
  data.left_data = analogRead(left);
  data.middle_data = analogRead(middle);
  data.right_data = analogRead(right);

  if(debug_mode){
  //  data.displayData();
  }

  return data;
}


void makeMSCD(){
   delay(motor_delay);
}

bool checkForDelay(){
   if(prev_pos != cur_pos){
      prev_pos = cur_pos;
      makeMSCD(); // Motor State Change Delay  
      return true;
    }
    return false;
}


void startInfraredRobot(){
	
  calibrateWithPotentiometer();
  
  SensorData data = readData();

  bool leftIsBlack = data.isLeftBlack();
  bool middleIsBlack = data.isMiddleBlack();
  bool rightIsBlack = data.isRightBlack();
   
  if(leftIsBlack && middleIsBlack && rightIsBlack){ //XXX
    //cur_pos = right_dir;
    //checkForDelay();
    goRight();
  }else if(!leftIsBlack && !middleIsBlack && !rightIsBlack){ // OOO
//    cur_pos = forward_dir;
//    checkForDelay();
//    goForward();
  }else if(!leftIsBlack && middleIsBlack && !rightIsBlack){ // OXO
    //cur_pos = forward_dir;
    //checkForDelay();
    goForward();
  }
  else if(leftIsBlack && !middleIsBlack && rightIsBlack){ // XOX
    //cur_pos = right_dir;
    //checkForDelay();
    goRight();
  }
  else if(leftIsBlack && !middleIsBlack && !rightIsBlack){ // XOO
   // cur_pos = left_dir;
    //checkForDelay();
    goLeft();
  }
  else if(leftIsBlack && middleIsBlack && !rightIsBlack){ // XXO
    //cur_pos = left_dir;
    //checkForDelay();
    goLeft();
  }
  else if(!leftIsBlack && middleIsBlack && rightIsBlack){ // OXX
    //cur_pos = right_dir;
    //checkForDelay();
    goRight();
  }
  else if(!leftIsBlack && !middleIsBlack && rightIsBlack){ // OOX
    //cur_pos = right_dir;
    //checkForDelay();
    goRight();
  }
  else{
    //cur_pos = backward_dir;
    //checkForDelay();
    goBackward();
  }

  if(middleIsBlack){
    digitalWrite(middleDisplay, HIGH);
  }else{
    digitalWrite(middleDisplay, LOW);  
  }

  if(leftIsBlack){
    digitalWrite(leftDisplay, HIGH);
  }else{
    digitalWrite(leftDisplay, LOW);  
  }

  if(rightIsBlack){
    digitalWrite(rightDisplay, HIGH);
  }else{
    digitalWrite(rightDisplay, LOW);  
  }

  //delay(input_delay);
 }
