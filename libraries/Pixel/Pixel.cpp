#ifndef pixelImp
#define pixelImp

#include "Pixel.h"


// constructors
Pixel::Pixel(byte yt,byte cbt,byte crt) : y(yt), cb(cbt), cr(crt){//, edited(true){
	//Serial.println("In pixel constructor.");
	//Serial.flush();
}

Pixel::Pixel() {// : edited(false){
	//Serial.println("In pixel default constructor.");
	//Serial.flush();
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
	y = rt;
	cb = gt;
	cr = bt;
}

// accessors
byte Pixel::getR(){
	return y;
}
byte Pixel::getG(){
	return cb;
}
byte Pixel::getB(){
	return cr;
}

// methods
void Pixel::convert(){
	byte rt = y+1.402*(cr-128);
    byte gt = y-0.34414*(cb-128)-0.71414*(cr-128);
    byte bt = y+1.772*(cb-128);
	y = rt;
	cb = gt;
	cr = bt;
}

bool Pixel::isEdited(){
	return edited;
}

#endif