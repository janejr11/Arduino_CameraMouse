#ifndef lineImp
#define lineImp

#include "Line.h"

// constructors
Line::Line(int widtht) : width(widtht) {
	// replaced in initializer list
	//width = widtht;
	pix = new Pixel[widtht];
}
Line::Line(){
}

// mutators
void Line::setWidth(int widtht){
	width = widtht;
	pix = new Pixel[widtht];
}
void Line::setPixelY(int i, uint8_t y){
	pix[i].sety(y);
}
void Line::setPixelCb(int i, uint8_t cb){
	pix[i].setcb(cb);
}
void Line::setPixelCr(int i, uint8_t cr){
	pix[i].setcr(cr);
}
void Line::setPixelData(int i, uint8_t r, uint8_t g, uint8_t b){
	pix[i].setData(r,g,b);
}

// accessors
Pixel *Line::getLine(){
	return pix;
}
uint8_t Line::getPixelR(int i){
	return pix[i].getR();
}
uint8_t Line::getPixelG(int i){
	return pix[i].getG();
}
uint8_t Line::getPixelB(int i){
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