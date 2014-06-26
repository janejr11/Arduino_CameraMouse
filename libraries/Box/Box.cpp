#include "Box.h"

// constructor
Box::Box(int xCentert, int yCentert, int xMaxt, int xMint, int yMaxt,int yMint){
	xCenter = xCentert;
	yCenter = yCentert;
	xMax = xMaxt;
	xMin = xMint;
	yMax = yMaxt;
	yMin = yMint;
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

void Box::calibrate(Driver dr,int targetR, int targetG, int targetB,
						  int rTolerance, int gTolerance, int bTolerance){
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
	while(i<3){
		t++;
		Serial.println("Reading: ");
		Serial.println(t);
		Serial.flush();
		dr.read();
		if (dr.isImageComplete()){
			Serial.println("Extracting image");
			Serial.flush();
			i++;
			current = dr.getFrame().locate(targetR, targetG, targetB, rTolerance, gTolerance, bTolerance);
			if (current.getX() > currentXMax)
				currentXMax = current.getX();
				
			if (current.getY() > currentYMax)
				currentYMax = current.getY();
			
			if (current.getX() < currentXMin)
				currentXMin = current.getX();
			
			if (current.getY() < currentYMin)
				currentYMin = current.getY();
		}
		
		// now we have collected the max/min values so we build the box
		int xDiff = currentXMax - currentXMin;
		int yDiff = currentYMax - currentYMin;
		// Box(int xCentert, int yCentert, int xMaxt, int xMint, int Ymaxt, yMint)
		//(int xCentert, int yCentert, int xMaxt, int xMint, int Ymaxt,int yMint);
		xCenter = currentXMin + xDiff / 2;
		yCenter = currentYMin + yDiff / 2;

		xMax = currentXMax;
		yMax = currentYMax;
		xMin = currentXMin;
		yMin = currentYMin;
	}
}
