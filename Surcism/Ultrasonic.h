void startUltrasonicRobot() {
  goBackward();
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

if(distance <= avioding_dist){
	goForward();
	delay(back_delay);
	goLeft();
	delay(turn_delay);
	goBackward();
}

// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.print(distance);
//Serial.println(" cm");
}
