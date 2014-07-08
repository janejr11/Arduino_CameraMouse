#include <Coordinates.h>
#include <Box.h>
#include <Pixel.h>
#include <Line.h>
#include <Frame.h>
#include <TimerOne.h>
#include <Driver.h>


// target RGB values (describing tape color)
uint8_t targetR = 255;
uint8_t targetG = 100;
uint8_t targetB = 142;

// margin of error allowed in pixel color analysis (specific to each color)
uint8_t rTolerance = 5;
uint8_t gTolerance = 20;
uint8_t bTolerance = 20;

// camera driver object
//Driver driver(480,640);

// box for judging mouse movement
Box range;

// the current location of the tracked point
Coordinates target;

// timer object to supply clock pulse to camera
//TimerOne Timer1;

void setup(){
  Serial.begin(9600);
  while(!Serial);
  

  Driver debug(480,640);
  
  
  Serial.println("Calibrating systems, move the target around.");
  Serial.flush();
  //range.calibrate(driver, targetR, targetG, targetB, rTolerance, gTolerance, bTolerance);

}

void loop(){
  Serial.println("\nBegin? [Y/N]");
  Serial.flush();
  while(!Serial.available()) ; // busy wait for user input
  char signal = Serial.read(); // read signal from the stream
  if (signal == 'y' || signal == 'Y'){
    Serial.println("Running.");
    while(1){ // active loop
    
    
    
      // body here
      
      
      
    }
  }
}


