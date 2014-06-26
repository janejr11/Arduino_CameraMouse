#include <Coordinates.h>
#include <Box.h>
#include <Pixel.h>
#include <Line.h>
#include <Frame.h>
#include <TimerOne.h>
#include <Driver.h>



// target RGB values (describing tape color)
const int targetR = 255;
const int targetG = 100;
const int targetB = 142;

// margin of error allowed in pixel color analysis (specific to each color)
const int rTolerance = 5;
const int gTolerance = 20;
const int bTolerance = 20;

// camera driver object
Driver driver(480,640);

// box for judging mouse movement
Box range;

// the current location of the tracked point
Coordinates target;


void setup(){
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Calibrating box dimensions, move the target around");
  Serial.flush();
  range.calibrate(driver, targetR, targetG, targetB, rTolerance, gTolerance, bTolerance);
						 
}

void loop(){
  
  while (!Serial.available());
  Serial.println("\nBegin? [Y/N]");
  Serial.flush();
  while(!Serial.available()) ; // busy wait for user input
  char signal = Serial.read(); // read signal from the stream
  if (signal == 'y' || signal == 'Y'){
    Serial.println("Running");
    while(1){ // active loop
    
    
    
      // body here
      
      
      
    }
  }
}


