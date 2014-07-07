#ifndef pixelImp
#define pixelImp

#include "Pixel.h"


// constructors
Pixel::Pixel(byte yt,byte cbt,byte crt) : y(yt), cb(cbt), cr(crt), edited(true){
}

Pixel::Pixel() : edited (false){
}

// mutators
void Pixel::sety(byte yt){
	y = yt;
}
void Pixel::setcb(byte cbt){
	cb = cbt;
}
void Pixel::setcr(byte crt){
	cr = crt;
}
void Pixel::setData(byte rt, byte gt, byte bt){
	r = rt;
	g = gt;
	b = bt;
}

// accessors
byte Pixel::getR(){
	return r;
}
byte Pixel::getG(){
	return g;
}
byte Pixel::getB(){
	return b;
}

// methods
void Pixel::convert(){
	r = y+1.402*(cr-128);
    g = y-0.34414*(cb-128)-0.71414*(cr-128);
    b = y+1.772*(cb-128);
}

bool Pixel::isEdited(){
	return edited;
}
#endif