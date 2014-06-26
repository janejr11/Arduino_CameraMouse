#include "Arduino.h"
#include "Coordinates.h"

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