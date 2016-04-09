int button[4] = {}; //button[] are the input buttons (all set to 0)
int level = 1; //current level
int* notes = new int[level]; //the notes of the level
boolean win = true; //if the player pressed the correct button

int out[4] = {9,10,11,12}; //the 4 output pins
int note[4] = {261,329,392,523}; //the 4 notes used
int sfx = 13; //sound pin

void setup() {
  randomSeed(analogRead(0)); //randomize random()
  pinMode(2, INPUT); //set pins to input and output
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop(){
  for(int i=0;i<level;i++){ //create the notes for the level, and output it
    notes[i] = random(0,4); //create note
    tone(sfx,note[notes[i]],400/level+100); //output sound of note
    digitalWrite(out[notes[i]],HIGH); //turn on led
    delay(400/level+100);
    digitalWrite(out[notes[i]],LOW); //turn off led
    delay(400/level+100);
  }
  for(int i=0;i<level&&win;i++){ //loop for all notes and player hasn't lost yet
    do{ //wait for input
      for(int j=0;j<4;j++){ //go through all the input pins
        button[j] = digitalRead(j+2); //check for input
        if(button[j] == HIGH) tone(sfx,note[j],250); //if there is an input, play the sound
      }
    } while(button[0] != HIGH && button[1] != HIGH && button[2] != HIGH && button[3] != HIGH); //keep on looping until a button is pressed

    win = (button[notes[i]] == HIGH); //if the required button is pressed, game continues
    
    do{
      for(int j=0;j<4;j++) button[j] = digitalRead(j+2); //check for input
    } while(button[0] == HIGH || button[1] == HIGH || button[2] == HIGH || button[3] == HIGH); //keep on looping until all buttons are released
    delay(10);
  }
  delay(500);
  if(win){ //level won
    level++; //increase level
    digitalWrite(9,HIGH); //play win theme and leds
    tone(sfx,note[0],150);
    delay(50);
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    delay(50);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
    tone(sfx,note[1],150);
    delay(50);
    digitalWrite(11,LOW);
    digitalWrite(12,HIGH);
    delay(50);
    tone(sfx,note[2],150);
    digitalWrite(12,LOW);
    digitalWrite(11,HIGH);
    delay(50);
    digitalWrite(11,LOW);
    digitalWrite(10,HIGH);
    delay(50);
    tone(sfx,note[3],450);
    digitalWrite(10,LOW);
    digitalWrite(9,HIGH);
    delay(50);
    digitalWrite(9,LOW);
    delay(1350);
  }
  else{ //level lost
    level = 1; //reset level to 1
    tone(sfx,392,250); //play lost theme and leds
    digitalWrite(12,HIGH);
    delay(250);
    digitalWrite(12,LOW);
    digitalWrite(10,HIGH);
    tone(sfx,370,250);
    delay(250);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
    tone(sfx,349,250);
    delay(250);
    digitalWrite(11,LOW);
    digitalWrite(9,HIGH);
    tone(sfx,329,1000);
    delay(1000);  
    digitalWrite(9,LOW);
    delay(1000);
  }
  
  notes = new int[level]; //resize array of notes
  win = true; //reset win
}
