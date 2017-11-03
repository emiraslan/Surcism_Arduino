const short M1F = 6;
const short M2F = 9;
const short M1R = 10;
const short M2R = 11;

const short leftDisplay = 2;
const short middleDisplay = 3;
const short rightDisplay = 4;

int M1E = 8; //Todo: Change this pincwith transistor
int M2E = 8; // Do it with transistors and battery! Pin voltage will be enough for operating a transistor

const short initial_delay = 10; 
const short action_delay = 3000; 
const short input_delay = 1;
const short motor_delay = 10; 

const short left = A0;
const short middle = A1;
const short right = A2;

const bool debug_mode = true;

float barrier = 558;
 
  float left_barrier = 580;
  float middle_barrier = 480;
  float right_barrier = 540;

short M1_move = 110;
short M2_move = 110;

short M1_move_s = 40;
short M2_move_s = 40;

short M1_stop = 0;
short M2_stop = 0;

const char left_dir = 'l';
const char right_dir = 'r';
const char forward_dir = 'f';
const char backward_dir = 'b';

char cur_pos = forward_dir;
char prev_pos = forward_dir;

/*
 directions:
       left = 'l'
       right = 'r'
       forward = 'f'
       background = 'b' 
*/

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

void setup() {
  Serial.begin(9600);
  
  pinMode(M1F, OUTPUT);
  pinMode(M2F, OUTPUT);
  pinMode(M1R, OUTPUT);
  pinMode(M2R, OUTPUT);
  
  pinMode(M1E, OUTPUT);
  pinMode(M2E, OUTPUT);

  pinMode(middleDisplay, OUTPUT);
  pinMode(leftDisplay, OUTPUT);
  pinMode(rightDisplay, OUTPUT);

  delay(action_delay);
  startMotors();
}

void loop() {
  calibrateWithPotentiometer();
  
  SensorData data = readData();

  bool leftIsBlack = data.isLeftBlack();
  bool middleIsBlack = data.isMiddleBlack();
  bool rightIsBlack = data.isRightBlack();
   
  if(leftIsBlack && middleIsBlack && rightIsBlack){ //XXX
    cur_pos = forward_dir;
    checkForDelay();
    goForward();
  }else if(!leftIsBlack && !middleIsBlack && !rightIsBlack){ // OOO
//    cur_pos = forward_dir;
//    checkForDelay();
//    goForward();
  }else if(!leftIsBlack && middleIsBlack && !rightIsBlack){ // OXO
    cur_pos = forward_dir;
    checkForDelay();
    goForward();
  }
  else if(leftIsBlack && !middleIsBlack && rightIsBlack){ // XOX
    cur_pos = forward_dir;
    checkForDelay();
    goForward();
  }
  else if(leftIsBlack && !middleIsBlack && !rightIsBlack){ // XOO
    cur_pos = left_dir;
    checkForDelay();
    goLeft();
  }
  else if(leftIsBlack && middleIsBlack && !rightIsBlack){ // XXO
    cur_pos = left_dir;
    checkForDelay();
    goLeft();
  }
  else if(!leftIsBlack && middleIsBlack && rightIsBlack){ // OXX
    cur_pos = right_dir;
    checkForDelay();
    goRight();
  }
  else if(!leftIsBlack && !middleIsBlack && rightIsBlack){ // OOX
    cur_pos = right_dir;
    checkForDelay();
    goRight();
  }
  else{
    cur_pos = backward_dir;
    checkForDelay();
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

  delay(input_delay);
}


//Todo: Optimize this function. Remove hard coded data.  
void calibrateWithPotentiometer(){
 
  int sensorValue = analogRead(A3);
  int sensorValue2 = analogRead(A4);
  int sensorValue3 = analogRead(A5);
  
  left_barrier = sensorValue * (1000.0 / 1023.0);
  middle_barrier = sensorValue2 * (1000.0 / 1023.0);
  right_barrier = sensorValue3 * (1000.0 / 1023.0);
}

void goForward(){
  analogWrite(M1F, M1_stop);
  analogWrite(M2F, M2_stop);
  analogWrite(M1R, M1_move);
  analogWrite(M2R, M2_move);
}

void goBackward(){
  analogWrite(M1F, M1_move);
  analogWrite(M2F, M2_move);
  analogWrite(M1R, M1_stop);
  analogWrite(M2R, M2_stop); 
}

void goRight(){
  analogWrite(M1F, M1_stop);
  analogWrite(M2F, M2_stop);
  analogWrite(M1R, M1_move_s);
  analogWrite(M2R, M2_move); 
}

void goLeft(){
  analogWrite(M1F, M1_stop);
  analogWrite(M2F, M2_stop);
  analogWrite(M1R, M1_move);
  analogWrite(M2R, M2_move_s);     
}

void stopMotors(){
  digitalWrite(M1E, LOW);
  digitalWrite(M2E, LOW);
}

void startMotors(){
  digitalWrite(M1E, HIGH);
  digitalWrite(M2E, HIGH);
}
  
SensorData readData(){
  SensorData data;
  
  data.left_data = analogRead(left);
  data.middle_data = analogRead(middle);
  data.right_data = analogRead(right);

  if(debug_mode){
    data.displayData();
  }

  return data;
}

bool checkForDelay(){
   if(prev_pos != cur_pos){
      prev_pos = cur_pos;
      makeMSCD(); // Motor State Change Delay  
      return true;
    }
    return false;
}

void makeMSCD(){
   delay(motor_delay);
}
