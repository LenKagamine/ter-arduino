// Morse Code Translator for Arduino
// TER Summative Project
int reader = A5;
int light = 3;
int motor = 11;
int reading = 0;
String msg;
String morse[] = {".-","-...","-.-.","-..", ".", "..-.", "--.", //array of morse code letters (morse[0] = A, morse[1] = B, ...)
                  "....", "..", ".---", "-.-", ".-..", "--",
                  "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                  "..-", "...-", ".--", "-..-", "-.--", "--.."};
void setup(){
  pinMode(motor, OUTPUT);
  pinMode(light, OUTPUT);
  //analogWrite(motor,100); //for analog motor movement
  Serial.begin(9600);
}

int getLight(){ //get light reading
  digitalWrite(light, HIGH); //flash light
  int bright = analogRead(reader); //get reading
  digitalWrite(light, LOW);
  delay(10);
  return bright;
}

int loopLight(int ms){ //take average of light reading over time period
  long time = millis(), bright = 0;
  int num = 0;
  while(millis()-time<ms){
    bright += getLight();
    num++;
  }
  return bright/num;
}

char translate(String str){ //convert string of morse code to english letter
  if(str=="") return ' ';
  for(int i=0;i<26;i++) if(str == morse[i]) return (char)(i+'A');
  return '_';
}

void loop(){
  digitalWrite(motor, HIGH); //move motor a bit (digital movement)
  delay(65);
  digitalWrite(motor, LOW);
  if(loopLight(500)<21){ //21 is light threshold, no dot detected
    if(reading == 1) msg += '.'; //dot length 1: dot
    else if(reading > 1) msg += '-';//dot length > 1: dash
    else Serial.print(translate(msg)); //dot length 0: space, letter is finished
    reading = 0; //reset length and message
    msg = "";
  }
  else reading++; //dot detected
  delay(250);
}
