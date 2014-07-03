#ifndef pixelImp
#define pixelImp

#include "Pixel.h"

// constructors
Pixel::Pixel(uint8_t yt,uint8_t cbt,uint8_t crt) : y(yt), cb(cbt), cr(crt){
}
Pixel::Pixel() : r (300){
}

// mutators
void Pixel::sety(uint8_t yt){
	y = yt;
}
void Pixel::setcb(uint8_t cbt){
	cb = cbt;
}
void Pixel::setcr(uint8_t crt){
	cr = crt;
}
void Pixel::setData(uint8_t rt, uint8_t gt, uint8_t bt){
	r = rt;
	g = gt;
	b = bt;
}

// accessors
uint8_t Pixel::getR(){
	return r;
}
uint8_t Pixel::getG(){
	return g;
}
uint8_t Pixel::getB(){
	return b;
}

// methods
void Pixel::convert(){
	r = y+1.402*(cr-128);
    g = y-0.34414*(cb-128)-0.71414*(cr-128);
    b = y+1.772*(cb-128);
}

#endif