//Standard PWM DC control
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control
int ultra = 11; //ultrasonic sensor pin

void move(int a,int b){
  if(b<0) b = map(b,0,255,0,249);
  digitalWrite(M1, b<0);
  digitalWrite(M2, a>0);
  analogWrite(E1, abs(b));
  analogWrite(E2, abs(a));
}

float distance(int pin){
  unsigned long time;
  unsigned long sizeofpulse;
  float range;

  pinMode(pin, OUTPUT); //return digital pin to OUTPUT mode after reading
  digitalWrite(pin, LOW);
  delayMicroseconds(25);
  digitalWrite(pin, HIGH); //Trig pin pulsed LOW for 25usec
  time = micros(); //record timer
  pinMode(pin, INPUT); //change pin to INPUT to read the echo pulse 
  sizeofpulse = pulseIn(pin, LOW, 18000); //should be approx 150usec, timeout at 18msec
  time = micros() - time - sizeofpulse; // amount of time elapsed since we sent the trigger pulse and detect the echo pulse, then subtract the size of the echo pulse
  range = (time*340.29/2/10000)-3; // convert to distance in centimeters
  return range;
}

void setup(){
  for(int i=4;i<=7;i++) pinMode(i, OUTPUT);
  pinMode(ultra, OUTPUT);
  digitalWrite(ultra, HIGH);
  Serial.begin(9600);
}

void loop(){
  move(255,255);
  Serial.println(distance(ultra));
  if(distance(ultra)<=20){
    move(255,-255);
    Serial.println("l");
  }
    delay(335);
//  delay(100);
  //Serial.println(distance(ultra)<=10);
  //delay(2000);
  //move(255,-255);
  //delay(335);
  
  
  /*forwards(255);
  delay(3000);
  backwards(255);
  delay(3000);
  left();
  delay(1500);
  right();
  delay(1500);*/
  /*
  Left motor:
    forwards: 0-249
    backwards: 0-255
  Right motor:
    forwards: 0-255
    backwards: 0-255
  */
}

void setSpeed(int a,int b){
  analogWrite(E1, a);
  analogWrite(E2, b);
}
void direction(boolean a, boolean b){
  digitalWrite(M1, !a);
  digitalWrite(M2, b);
}
void forwards(int speed){
  setSpeed(map(speed,0,255,0,249),speed);
  direction(1,1);
}
void backwards(int speed){
  setSpeed(speed,speed);
  direction(0,0);
}
void left(){
  direction(1,0);
}
void right(){
  direction(0,1);
}
