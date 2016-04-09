//note values
#define g1 48
#define g1s 51
#define a1 55
#define a1s 58
#define b1 61
#define c2 65
#define c2s 69
#define d2 73
#define d2s 77
#define e2 82
#define f2 87
#define f2s 92
#define g2 97
#define g2s 103
#define a2 110
#define a2s 116
#define b2 123
#define c3 130
#define c3s 138
#define d3 146
#define d3s 155
#define e3 164
#define f3 174
#define f3s 184
#define g3 195
#define g3s 207
#define a3 220
#define a3s 233
#define b3 246
#define c4 261
#define c4s 277
#define d4 293
#define d4s 311
#define e4 329
#define f4 349
#define f4s 369
#define g4 391
#define g4s 415
#define a4 440
#define a4s 466
#define b4 493
#define c5 523
#define c5s 554
#define d5 587
#define d5s 622
#define e5 659
#define f5 698
#define f5s 739
#define g5 783
#define g5s 830
#define a5 880
#define a5s 932
#define b5 989
#define c6 1046
#define c6s 1108
#define d6 1174
#define d6s 1244
#define e6 1318
#define f6 1396
#define f6s 1479
#define g6 1567
#define g6s 1661
#define a6 1760
#define a6s 1864
#define b6 1975
#define c7 2093
#define d7 2349
#define e7 2637

int music = 13; //music pin
int state = 1; //state: # song

int btn1 = 2; //button input pins
int btn2 = 3;
int btn3 = 4;

int redpin = 6; //led output pins
int greenpin = 9;
int bluepin = 10;

float whole; //note lengths
float half;
float quarter;
float eighth;
float triplet;
float sixteenth;
float sixtriplet;
float thirtysecond;
float grace;

void setup(){
  pinMode(btn1, INPUT); //set button pins to input
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(music, OUTPUT); //set button pin to output
}

void loop(){
  if(state == 1) titanic(); //chooses song based on state
  else if(state == 2) megaman();
  else if(state == 3) champions();
}

void setBPM(float bpm){ //sets the note lenghts given the bpm
  whole = (60/bpm)*4000;
  half = whole/2;
  quarter = whole/4;
  eighth = whole/8;
  triplet = whole/12;
  sixteenth = whole/16;
  sixtriplet = whole/24;
  thirtysecond = whole/32;
  grace = whole/32;
}

void light(int r,int g,int b){ //outputs rgb code to led light
  analogWrite(redpin,255-r/1.5);
  analogWrite(greenpin,255-g);
  analogWrite(bluepin,255-b);
}

void titanic(){ //1st song: my heart will go on
  setBPM(99); //set bpm to 99
  //the notes
  int titanicNote[] = { e4,e4,e4,e4, //verse
                        d4s,e4,e4,
                        d4s,e4,f4s,
                        g4s,f4s,
                        e4,e4,e4,e4,
                        d4s,e4,e4,
                        b3,
                        a3,b3,c4s,e4,a4,b4,c5s,d5s,
                        e4,e4,e4,e4, //verse loop
                        d4s,e4,e4,
                        d4s,e4,f4s,
                        g4s,f4s,
                        e4,e4,e4,e4,
                        d4s,e4,e4,
                        b3,
                        -1,c4s,d4s,
                        e4, //chorus
                        f4s,b3,
                        b4,a4,g4s,
                        f4s,g4s,a4,
                        g4s,f4s,e4,
                        d4s,e4,d4s,
                        c4s,
                        b3,a3,
                        e4, //chorus loop
                        f4s,b3,
                        b4,a4,g4s,
                        f4s,g4s,a4,
                        g4s,f4s,e4,
                        d4s,e4,d4s,
                        d4s,e4,f4s,
                        g4s,f4s
  };
  //the length of the notes
  float titanicTime[] = {quarter+eighth,eighth,quarter,quarter,
                        quarter,half,quarter,
                        quarter,half,quarter,
                        half,half,
                        quarter+eighth,eighth,quarter,quarter,
                        quarter,half,quarter,
                        whole,
                        eighth,eighth,eighth,eighth,eighth,eighth,eighth,eighth,
                        quarter+eighth,eighth,quarter,quarter,
                        quarter,half,quarter,
                        quarter,half,quarter,
                        half,half,
                        quarter+eighth,eighth,quarter,quarter,
                        quarter,half,quarter,
                        whole,
                        half,quarter,quarter,
                        whole,
                        half+quarter,quarter,
                        half,quarter,quarter,
                        half,quarter,quarter,
                        half,quarter,quarter,
                        quarter,half,quarter,
                        whole,
                        half,half,
                        whole,
                        half+quarter,quarter,
                        half,quarter,quarter,
                        half,quarter,quarter,
                        half,quarter,quarter,
                        quarter,half,quarter,
                        quarter,half,quarter,
                        half,half
  };
  for(int i=0;i<sizeof(titanicNote)/sizeof(int);i++){ //loops though all the notes
    if(titanicNote[i] != -1) tone(music,titanicNote[i],titanicTime[i]-10); //note of -1 means rest
    //lights: colors set to a theme
    if (i < 28) light(random(0,50),random(0,50),random(50,256));// blue range
    else if (i >= 29 && i < 50) light(random(100,256),random(0,25),random(0,200)); // pink range
    else if (i >= 50 && i < 68) light(random(50,255),random(100,255),random(50,255)); // green range
    else light(random(0,255),random(0,255),random(0,255)); // any color   
    
    unsigned long start = millis(); //special delay: goes through while loop until note is over
    while(millis()-start<titanicTime[i]){ //while note is still playing
      if(digitalRead(btn1)){ //check for buttons
        noTone(music); //replay song
        delay(500);
        return;
      }
      else if(digitalRead(btn2)){
        state = 2; //if button input, change song
        noTone(music);
        delay(500);
        return;
      }
      else if(digitalRead(btn3)){
        state = 3;
        noTone(music);
        delay(500);
        return;
      }
    }
  }
}

void megaman(){ //2nd song: megaman 2, dr. wily theme song
  setBPM(170); //same code, just different notes
  int megamanNote[] = {-1,e4,e4,e4,e4,e4,e4,c4s,-1,c4s,c4s,//verse
                      e4,e4,e4,e4,c4s,-1,g4s,f4s,g4s,
                      -1,e4,e4,e4,e4,e4,e4,c4s,-1,g4s,
                      -1,f4s,-1,e4,-1,f4s,-1,
                      -1,f4s,f4s,f4s,f4s,f4s,f4s,d4s,-1,g4s,
                      -1,f4s,-1,e4,-1,d4s,-1,c4s,
                      -1,c4s,g4s,b4,a4s,c4s,
                      -1,c4s,g4s,b4,a4s,b4,c5s,
                      b4,e5, //middle part
                      c5s,b4,c5s,
                      b4,b4,c5s,
                      g4s,a4,g4s,e4,-1,e4,g4s,b4,
                      c5s,b4,e5,
                      c5s,b4,c5s,b4,
                      b4,g4s,b4,c5,
                      -1,c5,c5,d5s,g5s,e4,
                      -1,e4,e4,d4s,e4,c5s,b4, //chorus
                      a4,g4s,f4s,f4s,
                      -1,g4s,g4s,g4s,-1,f4s,
                      -1,g4s,g4s,g4s,f4s,e4,
                      -1,e4,e4,d4s,e4,c5s,b4,
                      a4,g4s,f4s,
                      d4s,e4,d4s,c4s
  };
  float megamanTime[] = {eighth,sixteenth,sixteenth,eighth,sixteenth,sixteenth,eighth,eighth,eighth,sixteenth,sixteenth,
                        eighth,sixteenth,sixteenth,eighth,eighth,eighth,eighth,eighth,eighth,
                        eighth,sixteenth,sixteenth,eighth,sixteenth,sixteenth,eighth,eighth,eighth,eighth,
                        eighth,eighth,eighth,eighth,eighth,eighth,quarter,
                        eighth,sixteenth,sixteenth,eighth,sixteenth,sixteenth,eighth,eighth,eighth,eighth,
                        eighth,eighth,eighth,eighth,eighth,eighth,eighth,eighth,
                        eighth,eighth,eighth,eighth,quarter+eighth,eighth,
                        eighth,eighth,eighth,eighth,quarter,eighth,half+quarter+eighth,
                        eighth,quarter,
                        quarter,quarter,quarter+eighth,
                        half,eighth,quarter+eighth,
                        eighth,eighth,eighth,eighth,eighth,eighth,eighth,eighth,
                        half+quarter,eighth,quarter,
                        quarter,quarter,quarter,half+eighth,
                        eighth,eighth,eighth,eighth,
                        eighth,eighth,eighth,eighth,quarter+eighth,eighth,
                        eighth,eighth,eighth,eighth,quarter,eighth,quarter,
                        quarter,quarter,quarter,eighth,
                        eighth,eighth,quarter,quarter,eighth,eighth,
                        eighth,eighth,quarter,quarter,eighth,eighth,
                        eighth,eighth,eighth,eighth,quarter,eighth,quarter,
                        quarter,quarter,quarter+eighth,
                        eighth,eighth,eighth,eighth+half+whole
  };
  for(int i=0;i<sizeof(megamanNote)/sizeof(int);i++){
    if(megamanNote[i] != -1) tone(music,megamanNote[i],megamanTime[i]-10);
    
    light(random(0,255),random(0,255),random(0,255));
    
    unsigned long start = millis();
    while(millis()-start<megamanTime[i]){
      if(digitalRead(btn1)){
        state = 1;
        noTone(music);
        delay(500);
        return;
      }
      else if(digitalRead(btn2)){
        noTone(music);
        delay(500);
        return;
      }
      else if(digitalRead(btn3)){
        state = 3;
        noTone(music);
        delay(500);
        return;
      }
    }
  }
}

void champions(){ //3rd song: chorus of we are the champions
  setBPM(124);
  int championsNote[] = {f5,e5,f5,//we are da
                         e5,c5,a4, //champ ions ma
                         d5,a4, //fri-end
                         a4s,c5,c5, //- - and
                         f5,g5,a5, //well keep on
                         c6,a5,d5,e5, //fight-ing till da
                         d5, //enddddddddddddd
                         d5,c5,d5, //we are da
                         c5,a4s, //champ-ions
                         a5s,a5,a5s, //we are da
                         a5,g5, //champ-ions
                         a5,f5,a5s, //no time for
                         a5,f5,a5s, //los-ers cuz
                         g5s,f5,a5s, //we are da
                         g5s,f5, //champ-ions
                         -1,e5,c5 //- of the (world)
  };
  float championsTime[] = {half,eighth,eighth,
                           quarter,eighth+quarter,eighth,
                           quarter,half,
                           quarter+eighth,quarter,eighth,
                           half,eighth,eighth,
                           quarter,quarter,eighth,eighth,
                           half+quarter+half+quarter,
                           quarter+eighth,quarter,eighth,
                           quarter+eighth,quarter+eighth,
                           quarter+eighth,quarter,eighth,
                           quarter+eighth,quarter+eighth,
                           quarter+eighth,quarter,eighth,
                           quarter+eighth,quarter,eighth,
                           quarter+eighth,quarter,eighth,
                           quarter+eighth,quarter+eighth,
                           half,eighth,eighth
  };
  for(int i=0;i<sizeof(championsNote)/sizeof(int);i++){
    if(championsNote[i] != -1) tone(music,championsNote[i],championsTime[i]-10);
    
    if (i < 18) light(random(150,255),random(150,200),random(0,150)); // yellow range
    else if (i >=19 && i < 23) light(random(180,225),random(0,25),random(0,200)); //red range
    else if (i >=24 && i < 28) light(random(0,50),random(0,50),random(50,256));  // blue range
    else if (i >=29 && i < 34) light(random(50,255),random(100,255),random(50,255)); // green range
    else light(random(0,256), random (0,256), random(0,256));
  
    unsigned long start = millis();
    while(millis()-start<championsTime[i]){
      if(digitalRead(btn1)){
        state = 1;
        noTone(music);
        delay(500);
        return;
      }
      else if(digitalRead(btn2)){
        state = 2;
        noTone(music);
        delay(500);
        return;
      }
      else if(digitalRead(btn3)){
        noTone(music);
        delay(500);
        return;
      }
    }
  }
}
