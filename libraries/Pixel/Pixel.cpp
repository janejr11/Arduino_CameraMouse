#ifndef pixelImp
#define pixelImp

#include "Arduino.h"
#include "Pixel.h"

// constructors
Pixel::Pixel(int yt,int cbt,int crt){
	y = yt;
	cb = cbt;
	cr = crt;
}
Pixel::Pixel(){
}

// mutators
void Pixel::sety(int yt){
	y = yt;
}
void Pixel::setcb(int cbt){
	cb = cbt;
}
void Pixel::setcr(int crt){
	cr = crt;
}
void Pixel::setData(int rt, int gt, int bt){
	r = rt;
	g = gt;
	b = bt;
}

// accessors
int Pixel::getR(){
	return r;
}
int Pixel::getG(){
	return g;
}
int Pixel::getB(){
	return b;
}

// methods
void Pixel::convert(){
	r = y+1.402*(cr-128);
    g = y-0.34414*(cb-128)-0.71414*(cr-128);
    b = y+1.772*(cb-128);
}

#endif