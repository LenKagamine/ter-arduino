//Standard PWM DC control
int E1 = 5;    //M1 Speed Control
int E2 = 6;    //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control
  
void stop(){ //Stop
  digitalWrite(E1,LOW);   
  digitalWrite(E2,LOW);      
}

void advance(int a, int b){ //Move forward
  analogWrite (E1,a);      //PWM Speed Control
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}

void back_off(int a, int b){ //Move backward
  analogWrite (E1,a);
  digitalWrite(M1,LOW);   
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}

void turn_L(int a, int b){ //Turn Left
  analogWrite (E1,a);
  digitalWrite(M1,LOW);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}

void turn_R(int a, int b){ //Turn Right
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}

void setup{
  for(int i=4;i<=7;i++) pinMode(i, OUTPUT);  
}

void loop(){
  advance(255,255);   //move forward in max speed
  delay(5000);
  back_off(255,255);   //move back in max speed
  delay(5000);
  turn_L(200,200);
  delay(1500);
  turn_R(200,200);
  delay(1500);
  stop();
  delay(3000);
}
