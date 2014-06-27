/*
Things to check for errors
-Conversion of YCbCr to RGB

*/

#include <TimerOne.h>
#include <Pixel.h>
#include <Line.h>
#include <Frame.h>
#include <Driver.h>
#include <Coordinates.h>
#include <Box.h>

// target RGB values (describing tape point)
const int targetR = 255;
const int targetG = 100;
const int targetB = 142;

// margin of error allowed in pixel color analysis (specific to each color
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
  Serial.println("Calibrating box dimensions, move the target around");
  // calibrate function that builds a box to judge the movement of the tracked point
  range = calibrate(driver);
  Serial.println("Box calibrated, collecting images");
}

void loop(){
  Serial.println("Reading data");
  // read in data from the camera
  driver.read();
  // if you have completed a frame,
  if (driver.isImageComplete()){
    Serial.println("Frame complete, locating target");
    // if yes, locate the target point
    target = driver.getframe().locate();
    Serial.println("Target located, moving mouse");
    range.moveMouse(target);
  }
}




