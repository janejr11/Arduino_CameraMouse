#ifndef boxImp
#define boxImp

#include "Box.h"

// constructors
Box::Box(int xCentert, int yCentert, int xMaxt, int xMint, int yMaxt,int yMint) : xCenter(xCentert), yCenter(yCentert), xMax(xMaxt), xMin(xMint), yMax(yMaxt), yMin(yMint) {
	// all replaced by initializer list
	/*xCenter = xCentert;
	yCenter = yCentert;
	xMax = xMaxt;
	xMin = xMint;
	yMax = yMaxt;
	yMin = yMint;*/
}
Box::Box(){
}

// mutators
void Box::setXCenter(int xCentert){
	xCenter = xCentert;
}
void Box::setYCenter(int yCentert){
	yCenter = yCentert;
}
void Box::setXMax (int xMaxt){
	xMax = xMaxt;
}
void Box::setYMax (int yMaxt){
	yMax = yMaxt;
}
void Box::setXMin (int xMint){
	xMin = xMint;
}
void Box::setYMin (int yMint){
	yMin = yMint;
}

//accessors
int Box::getXCenter(){
	return xCenter;
}
int Box::getYCenter(){
	return yCenter;
}
int Box::getXMax(){
	return xMax;
}
int Box::getXMin(){
	return xMin;
}
int Box::getYMax(){
	return yMax;
}
int Box::getYMin(){
	return yMin;
}

void Box::calibrate(Driver dr,uint8_t targetR, uint8_t targetG, uint8_t targetB,
					uint8_t rTolerance, uint8_t gTolerance, uint8_t bTolerance){
	Serial.println("In calibrate");
	Serial.flush();
	int currentXMax = 0;
	int currentYMax = 0;
	int currentXMin = 10000;
	int currentYMin = 10000;
	Coordinates current;
	int i = 0;
	int t = 0; // debugging
	// reads 100 frames to find the min and max y/y values for the calibrated box
	while(i<20){
		/*t++;
		if (t%100 == 0){
			Serial.print("Reading: ");
			Serial.println(t);
			Serial.flush();
		}*/
		//dr.read();
		if (dr.isImageComplete()){
			Serial.println("Frame complete. Extracting image.");
			Serial.flush();
			i++;
			
			/*bool frameTest = dr.getFrame().testFrame();
			if (frameTest)
				Serial.println("Frame successfully constructed");
			else
				Serial.println("Frame incomplete");
			*/
			current = dr.getFrame().locate(targetR, targetG, targetB, rTolerance, gTolerance, bTolerance);
			Serial.print("X: ");
			Serial.print(current.getX());
			Serial.print("   ");
			Serial.print("Y: ");
			Serial.println(current.getY());
			Serial.flush();
			if (current.getX() > currentXMax)
				currentXMax = current.getX();
				
			if (current.getY() > currentYMax)
				currentYMax = current.getY();
			
			if (current.getX() < currentXMin)
				currentXMin = current.getX();
			
			if (current.getY() < currentYMin)
				currentYMin = current.getY();
		}
		// now we have collected the max/min values so we build this box
		int xDiff = currentXMax - currentXMin;
		int yDiff = currentYMax - currentYMin;
		
		xCenter = currentXMin + xDiff / 2;
		yCenter = currentYMin + yDiff / 2;

		xMax = currentXMax;
		yMax = currentYMax;
		xMin = currentXMin;
		yMin = currentYMin;
		
	}
	Serial.println("Calibration complete, ready to activate mouse.");
	Serial.flush();
}

// move the mouse according to the movement of the point within the box
void Box::moveMouse(Coordinates point){
	float sectorWidth;
	float sectorHeight;
	
	sectorWidth  = (float)(xMax - xCenter) / 4.0;
	sectorHeight = (float)(yMax - yCenter) / 4.0;
	
	Mouse.begin();
	  // X motion
	if (point.getX() > (float)xMax - sectorWidth)             // fast right
		Mouse.move(3,0,0);
	else if (point.getX() < (float)xMin + sectorWidth)        // fast left
		Mouse.move(-3,0,0);
	else if (point.getX() > (float)xMax - 2.0 * sectorWidth)  // medium right
		Mouse.move(2,0,0);
	else if (point.getX() < (float)xMin + 2.0 * sectorWidth)  // medium left
		Mouse.move(-2,0,0);
	else if (point.getX() > (float)xMax - 3.0 * sectorWidth)  // slow right
		Mouse.move(1,0,0);
	else if (point.getX() < (float)xMin + 3.0 * sectorWidth)  // slow left
		Mouse.move(-1,0,0);
    
	// Y motion
	if (point.getY() > (float)yMax - sectorHeight)            // fast right
		Mouse.move(0,3,0);
	else if (point.getY() < (float)yMin +       sectorHeight) // fast left
		Mouse.move(0,-3,0);
	else if (point.getY() > (float)yMax - 2.0 * sectorHeight) // medium right
		Mouse.move(0,2,0);
	else if (point.getY() < (float)yMin + 2.0 * sectorHeight) // medium left
		Mouse.move(0,-2,0);
	else if (point.getY() > (float)yMax - 3.0 * sectorHeight) // slow right
		Mouse.move(0,1,0);
	else if (point.getY() < (float)yMin + 3.0 * sectorHeight) // slow left
		Mouse.move(0,-1,0);
	Mouse.end();
}

#endif