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
    target = locate(driver.getFrame());
    Serial.println("Target located, moving mouse");
    moveMouse(range,target);
  }
  // move the mouse according to the movement of the point within the range box
}


Coordinates locate(Frame fr){
  Coordinates target;
  int xSum = 0;
  int ySum = 0;
  int total = 0;
  // check each row
  for (int i = 0; i<fr.getHeight(); i++){
    // check each pixel
    for (int j = 0; j<fr.getWidth(); j++){
          // if the R is within the tolerated values
      if (
        fr.getSpine()[i].getPixelR(j) > targetR-rTolerance &&
        fr.getSpine()[i].getPixelR(j) < targetR+rTolerance &&
        // and the G is within the tolerated values
        fr.getSpine()[i].getPixelG(j) > targetG-gTolerance &&
        fr.getSpine()[i].getPixelG(j) < targetG+gTolerance &&
        // and the B is within the tolerated values
        fr.getSpine()[i].getPixelB(j) > targetB-bTolerance &&
        fr.getSpine()[i].getPixelB(j) < targetB+bTolerance){
        // if yes to all, update the sums. Once completed with frame analysis,
        // average the values to find the center of the target
        xSum = xSum + j;
        ySum = ySum = i;
        total++;
      }
    }
  }
  
  target.setY(ySum / total);
  target.setX(xSum / total);
  return target;
}
/*
// pass in the completed frame from the camera and return the 
// first point that falls within the accepted RGB values
Coordinates locate(Frame fr){
  Coordinates target;
  for (int i = 0; i<fr.getHeight(); i++){
    for (int j = 0; j<fr.getWidth(); j++){
          // if the R is within the tolerated values
      if (fr.getSpine()[i].getPixelR(j) > targetR-tolerance &&
          fr.getSpine()[i].getPixelR(j) < targetR+tolerance &&
          // and the G is within the tolerated values
          fr.getSpine()[i].getPixelG(j) > targetG-tolerance &&
          fr.getSpine()[i].getPixelG(j) < targetG+tolerance &&
          // and the B is within the tolerated values
          fr.getSpine()[i].getPixelB(j) > targetB-tolerance &&
          fr.getSpine()[i].getPixelB(j) < targetB+tolerance){
            // if yes to all, update the target coordinates and return
            target.setY(i);
            target.setX(j);
            return target;
          }
    }
  }
}
*/

// calibrate the center location of the point and min/max x and y values
Box calibrate(Driver dr){
  Coordinates current;
  int currentXMax = 0;
  int currentYMax = 0;
  int currentXMin = 640;
  int currentYMin = 480;
  int i = 0;
  // reads 100 frames to find the min and max y/y values for the calibrated box
  while(i<100){
    dr.read();
    if (driver.isImageComplete()){
      i++;
      current = locate(dr.getFrame());
      if (current.getX() > currentXMax)
        currentXMax = current.getX();
        
      if (current.getY() > currentYMax)
        currentYMax = current.getY();
      
      if (current.getX() < currentXMin)
        currentXMin = current.getX();
      
      if (current.getY() < currentYMin)
        currentYMin = current.getY();
    }
  }
  // now we have collected the max/min values so we build the box
  int xDiff = currentXMax - currentXMin;
  int yDiff = currentYMax - currentYMin;
  // Box(int xCentert, int yCentert, int xMaxt, int xMint, int Ymaxt, yMint)
  Box box(currentXMin + xDiff / 2, currentYMin + yDiff / 2, currentXMax, currentXMin, currentYMax, currentYMin);
  return box;
}


void moveMouse(Box box, Coordinates point){
  int sectorWidth;
  int sectorHeight;
  sectorWidth = (box.getXMax() - box.getXCenter()) / 4;
  sectorHeight = (box.getYMax() - box.getYCenter()) / 4;
  Mouse.begin();
  if (point.getX() > box.getXMax() - sectorWidth)           // fast right
    Mouse.move(3,0,0);
  else if (point.getX() < box.getXMin() + sectorWidth)      // fast left
    Mouse.move(-3,0,0);
  else if (point.getX() > box.getXMax() - 2 * sectorWidth)  // medium right
    Mouse.move(2,0,0);
  else if (point.getX() < box.getXMin() + 2 * sectorWidth)  // medium left
    Mouse.move(-2,0,0);
  else if (point.getX() > box.getXMax() - 3 * sectorWidth)  // slow right
    Mouse.move(1,0,0);
  else if (point.getX() < box.getXMin() + 3 * sectorWidth)  // slow left
    Mouse.move(-1,0,0);
  if (point.getY() > box.getYMax() - sectorHeight)          // fast right
    Mouse.move(0,3,0);
  else if (point.getY() < box.getYMin() +     sectorHeight) // fast left
    Mouse.move(0,-3,0);
  else if (point.getY() > box.getYMax() - 2 * sectorHeight) // medium right
    Mouse.move(0,2,0);
  else if (point.getY() < box.getYMin() + 2 * sectorHeight) // medium left
    Mouse.move(0,-2,0);
  else if (point.getY() > box.getYMax() - 3 * sectorHeight) // slow right
    Mouse.move(0,1,0);
  else if (point.getY() < box.getYMin() + 3 * sectorHeight) // slow left
    Mouse.move(0,-1,0);
  Mouse.end();
}
