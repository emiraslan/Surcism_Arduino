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
    goLeft();
    break;
    
    case 'r':
    goRight();
    break;
    
    case 's':
    stopMotors();
    break;
  }
}

