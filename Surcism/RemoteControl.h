void startRemoteControl() { 
  switch(command)
  {
    case 'f':
     goForward();
    break;
    
    case 'b':
     goBackward();
    break;
    
    case 'l':
    // It is reverse comparing to Ultrasonic
     goRight();
    break;
    
    case 'r':
    // It is reverse comparing to Ultrasonic
     goLeft();
    break;
    
    case 's':
    if(motorIsEnabled)
      stopMotors();
    else
      startMotors();
    break;
  }
}


