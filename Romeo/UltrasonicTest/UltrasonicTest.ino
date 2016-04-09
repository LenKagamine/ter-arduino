int pin = 11; // connected to the Trig on the module, this serves as both Trigger and Echo

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
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH); // Trig pin is normally HIGH
}

void loop(){
  float range = distance(pin);
  Serial.print(" Distance: ");
  Serial.print(range);
  Serial.println(" cm");
  delay(1000);
}
