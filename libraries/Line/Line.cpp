#ifndef lineImp
#define lineImp

#include "Arduino.h"
#include "Line.h"

// constructors
Line::Line(int widtht){
	width = widtht;
	pix = new Pixel[widtht];
}
Line::Line(){
}

// mutators
void Line::setWidth(int widtht){
	width = widtht;
	pix = new Pixel[widtht];
}
void Line::setPixelY(int i, int y){
	pix[i].sety(y);
}
void Line::setPixelCb(int i, int cb){
	pix[i].setcb(cb);
}
void Line::setPixelCr(int i, int cr){
	pix[i].setcr(cr);
}
void Line::setPixelData(int i, int r, int g, int b){
	pix[i].setData(r,g,b);
}

// accessors
Pixel *Line::getLine(){
	return pix;
}
int Line::getPixelR(int i){
	return pix[i].getR();
}
int Line::getPixelG(int i){
	return pix[i].getG();
}
int Line::getPixelB(int i){
	return pix[i].getB();
}
int Line::getWidth(){
	return width;
}

// methods
void Line::convert(){
	for (int i=0; i<width; i++){
		pix[i].convert();
	}
}

#endif