char command;
String string;
boolean ledon = false;
#define led 5
short analogValue = 128;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0)
  {
    string = "";
    command = ((byte)Serial.read());
    string += command;
    Serial.print("Here: ");
    Serial.println(string);
    delay(1);
  }

  if(string == "O" && !ledon ){
    ledOn();
    ledon = true;
    Serial.println("ledon");
  }
  else if(string =="F" && ledon){
    ledOff();
    ledon = false;
    Serial.println("ledoff");
  }else if(string =="b" && ledon){
    string = "";
     while (Serial.available() > 0){
       command = ((byte)Serial.read());
       if(command == "e"){ break;}
       else{
        string += command;
        delay(1);
       }
     }
     if (ledon){
      analogValue = map(string.toInt(), 0, 100, 0, 255);
      analogWrite(led, analogValue);
      Serial.print("Seeker bar: ");
      Serial.print(string.toInt());
      Serial.print("\t");
      Serial.print(analogValue);
      Serial.print("\t");
      Serial.println(string);
    }
  }
}

void ledOn(){
  analogWrite(led, analogValue);
  delay(1);
}

void ledOff(){
  analogWrite(led, 0);
  delay(1);
}
