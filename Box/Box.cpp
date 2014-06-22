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
