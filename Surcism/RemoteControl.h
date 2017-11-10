void startRemoteControl() {

  command = com;
  
  switch(command)
  {
    case 'f':
    goForward();
    break;
    case 'b':
    goBackward();
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

