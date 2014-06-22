#include <Pixel.h>
#include <Line.h>
#include <Frame.h>
#include <TimerOne.h>


// pin descriptions
// DIGITAL
// 0 - d0
// 1 - d1
// 2 - d2
// 3 - d3
// 4 - d4
// 5 - d5
// 6 - d6
// 7 - d7
// 8 - sccbData
// 9 - verticalSync
// 10 - systemClock
// 11 - sccbClock
// 12 - horizontalSync
// 13 - pixelClock

// ANALOG
// 0 - powerDown // active high
// 1 - reset // active low

// pin decl/inst
const int d0 = 0;
const int d1 = 1;
const int d2 = 2;
const int d3 = 3;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
const int sccbD = 8;
const int vSync = 9;
const int sysClk = 10;
const int sccbClk = 11;
const int hSync = 12;
const int pClk = 13;

// image dimensions
const int width = 640;
const int height = 480;

// image
Frame image(height,width);

// Clock Pulse (TimerOne) Global necessities
const char SET_PERIOD_HEADER      = 'p';
const char SET_FREQUENCY_HEADER   = 'f';
const char SET_PULSE_WIDTH_HEADER = 'w';
const char SET_DUTY_CYCLE_HEADER  = 'c';

#define pwmRegister OCR1A    // the logical pin, can be set to OCR1B
const int   outPin1 =  sysClk;     // the physical pin
const int   outPin2 =  sccbClk;     // the physical pin

long period = 1;     // the period in microseconds
int duty = 512;         // duty as a range from 0 to 1024, 512 is 50% duty cycle

int prescale[] = {0,1,8,64,256,1024}; // the range of prescale values
// end Clock section

// function definitions
int readPins(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7);


void setup() {
  // setup BAUD rate
  Serial.begin(9600);
  // digital pinModes
  pinMode(d0,INPUT);
  pinMode(d1,INPUT);
  pinMode(d2,INPUT);
  pinMode(d3,INPUT);
  pinMode(d4,INPUT);
  pinMode(d5,INPUT);
  pinMode(d6,INPUT);
  pinMode(d7,INPUT);
  pinMode(vSync,INPUT);
  pinMode(hSync,INPUT);
  pinMode(pClk,INPUT);
  pinMode(sccbClk,OUTPUT);
  pinMode(sccbD,OUTPUT);
  pinMode(sysClk,OUTPUT);
  
  // supply clock pulse to camera: SCCB and Sys
  Timer1.initialize(period);
  Timer1.pwm(sccbClk,duty);
  Timer1.pwm(sysClk,duty);
  
}

// If you instantiate these incorrectly the program might begin collecting data in the middle of a frame
int pasth = HIGH; // to test whether you have reached the falling/rising edge
int pastv = LOW;  // to test whether you have reached the falling/rising edge
int pastp = LOW;  // to test whether you have reached the falling/rising edge

void loop() {
  // variable declarations
  int h; //Horizontal Sync (one HIGH state signifies each line)
  int v; //Vertical Sync (one LOW state signifies each frame)
  int p; //

  
  v = digitalRead(vSync);
  if (v == LOW && pastv == HIGH){ // beginning of a new frame (falling edge of vertical sync)
    while (v==LOW){ // continue reading lines until the frame is fully constructed
      h = digitalRead(hSync);
      if (h == HIGH && pasth == LOW){ // beginning of a new row
        while( h== HIGH ){ // continue reading every pixel until you have constructed the full row
          p = digitalRead(pClk);
          if (p == HIGH && pastp == LOW){ // read a byte of data and add it to the row
            
            
            // read in the data from the pins using binary math
            unsigned int data = 0;
            if (digitalRead(d0) == HIGH)
              data = data + 1;
            if (digitalRead(d1) == HIGH)
              data = data + 2;
            if (digitalRead(d2) == HIGH)
              data = data + 4;
            if (digitalRead(d3) == HIGH)
              data = data + 8;
            if (digitalRead(d4) == HIGH)
              data = data + 16;
            if (digitalRead(d5) == HIGH)
              data = data + 32;
            if (digitalRead(d6) == HIGH)
              data = data + 64;
            if (digitalRead(d7) == HIGH)
              data = data + 128;
            image.readWord(data);
              
          }
          pastp = p;
        }
      }
      pasth = h;
    }
  }
  pastv = v;
} // end of loop

int readPins(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7){
  unsigned int data = 0;
  if (digitalRead(d0) == HIGH)
    data = data + 1;
  if (digitalRead(d1) == HIGH)
    data = data + 2;
  if (digitalRead(d2) == HIGH)
    data = data + 4;
  if (digitalRead(d3) == HIGH)
    data = data + 8;
  if (digitalRead(d4) == HIGH)
    data = data + 16;
  if (digitalRead(d5) == HIGH)
    data = data + 32;
  if (digitalRead(d6) == HIGH)
    data = data + 64;
  if (digitalRead(d7) == HIGH)
    data = data + 128;
  return data;
}
