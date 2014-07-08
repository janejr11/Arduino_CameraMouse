#ifndef coordinatesImp
#define coordinatesImp

#include "Coordinates.h"

Coordinates::Coordinates(){
	Serial.println("Coordinates constructed.");
	Serial.flush();
}

int Coordinates::getX(){
	return x;
}
int Coordinates::getY(){
	return y;
}
void Coordinates::setX(int xt){
	x = xt;
}
void Coordinates::setY(int yt){
	y = yt;
}

#endif