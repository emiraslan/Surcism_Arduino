
void goForward(){
  analogWrite(M1R, M1_stop);
  analogWrite(M2R, M2_stop);
  analogWrite(M1F, M1_move);
  analogWrite(M2F, M2_move);
}

void goBackward(){
  analogWrite(M1R, M1_move);
  analogWrite(M2R, M2_move);
  analogWrite(M1F, M1_stop);
  analogWrite(M2F, M2_stop); 
}

void goRight(){
  analogWrite(M1R, M1_move_s);
  analogWrite(M2R, M2_stop);
  analogWrite(M1F, M1_stop);
  analogWrite(M2F, M1_move_s); 
}

void goLeft(){
  analogWrite(M1R, M1_stop);
  analogWrite(M2R, M2_move_s);
  analogWrite(M1F, M1_move_s);
  analogWrite(M2F, M2_stop);     
}

void stopMotors(){
  motorIsEnabled = false;
  digitalWrite(M1E, LOW);
  digitalWrite(M2E, LOW);
}

void startMotors(){
  motorIsEnabled = true;
  digitalWrite(M1E, HIGH);
  digitalWrite(M2E, HIGH);
}
  

