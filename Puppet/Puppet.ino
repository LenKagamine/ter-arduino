//Servo Puppet
#include <Servo.h>
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

Servo s1,s2,s3; //servos
int btn1=11,btn2=10,btn3=9,music=12; //pins for button and music
int s1pin=6,s2pin=5,s3pin=4; //servo pins
void setup(){
  pinMode(btn1,INPUT); //set pins and servos
  pinMode(btn2,INPUT);
  pinMode(btn3,INPUT);
  s1.attach(s1pin);
  s2.attach(s2pin);
  s3.attach(s3pin);
}
float whole = 3333.33; //tempo for music
float half = whole/2;
float quarter = whole/4;
float eighth = whole/8;

float note[] = {a2,c3s,a3,b3,c4s,b3,a3,e3, //music notes
                d3,f3s,c4s,e4,c4s,a3,
                a2,c3s,a3,b3,c4s,b3,a3,e3,
                d3,f3s,c4s,e4,c4s,a3,
                g4s,a4,
                f4s,e4,f4s,
                g4s,b4,c5s,
                -1,f4s,c5s,e5,
                g5,f5s,d5,a4,b4,
                g5,f5s,d5,a4,b4,
                a4,
                e4,a3,
                a2,c3s,e3,b3,c4s,e4,a4,c5s,
                d5,c5s,a4,e5,f5s,
                -1,d5,b4,c5s,
                d5,c5s,d5s,f5s,
                c5s,b3,a3,
                e2,g2s,b2,e3,g3s,e3,b2,g2s,
                e2,g2s,b2,e3,g3s,e3,a3,
                g5,f5s,e5,d5,e5,d5,e5,f5s,
                -1,e5,a5,
                g5s,e5,b4,g4s,e4,
                b4,g5s,e4,b3,g3s,
                e3,g3s,b3,e4,b3,g3s,
                e3,g3s,b3,e4,b3,g3s
};
float time[] = {eighth,eighth,eighth,eighth,eighth,eighth,eighth,eighth, //music note lengths
                eighth,eighth,eighth,eighth,eighth,eighth+quarter,
                eighth,eighth,eighth,eighth,eighth,eighth,eighth,eighth,
                eighth,eighth,eighth,eighth,eighth,eighth+quarter,
                half+quarter,quarter,
                half+quarter,eighth,eighth,
                half+quarter,eighth,eighth,
                eighth,eighth+half,eighth,eighth,
                quarter+eighth,eighth,quarter,eighth,eighth+whole,
                quarter,quarter,quarter,eighth,eighth+half+quarter,
                quarter,
                quarter,quarter,half,
                eighth,eighth,eighth,eighth,eighth,eighth,eighth,eighth,
                quarter+eighth,eighth,quarter,eighth,eighth,
                eighth,eighth+half,eighth,eighth,
                quarter,eighth,quarter,quarter+eighth,
                half+quarter,eighth,eighth,
                eighth,eighth,eighth,eighth,eighth,eighth,eighth,eighth,
                eighth,eighth,eighth,eighth,eighth,eighth,quarter,
                eighth,eighth,eighth,eighth,eighth,eighth,eighth,eighth,
                eighth,quarter+eighth,half,
                eighth,eighth,eighth,eighth,half,
                eighth,eighth,eighth,eighth,half,
                eighth,eighth,eighth,eighth,eighth,eighth+quarter,
                eighth,eighth,eighth,eighth,eighth,eighth+quarter
};

void loop(){
  for(int i=0;i<sizeof(note)/sizeof(float);i++){ //loop for music
    if(note[i] != -1) tone(music,note[i],time[i]); 
    unsigned long start = millis();
    while(millis()-start<time[i]){
      if(digitalRead(btn1) == HIGH){ //pickaxe
        pickaxe();
      }
      else if(digitalRead(btn2) == HIGH){ //running
        run();
      }
      else if(digitalRead(btn3) == HIGH){ //creeper jumping
        s3.write(0);
      }
      else{ //automatic
        for(int i=0;i<7;i++){
          pickaxe();
        }
        s3.write(0);
        delay(1000);
        for(int i=0;i<5;i++){
          run();
        }
        s3.write(95);
      }
    }
  }
}

void pickaxe(){
  s1.write(173);
  delay(400);
  s1.write(5);
  delay(400);
}
void run(){
  s2.write(180);
  delay(380);
  s2.write(0);
  delay(380);
}
