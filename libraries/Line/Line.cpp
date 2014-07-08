#ifndef lineImp
#define lineImp

#include "Line.h"

// constructors
Line::Line(int widtht) : width(widtht) {
	//Serial.println("In line constructor.");
	//Serial.flush();
	pix = new Pixel[widtht];
}
Line::Line(){
	//Serial.println("In line default constructor.");
	//Serial.flush();
}
// destructor
Line::~Line(){

}

// mutators
void Line::setWidth(int widtht){
	width = widtht;
	pix = new Pixel[widtht];
}
void Line::setPixelY(int i, byte y){
	pix[i].sety(y);
}
void Line::setPixelCb(int i, byte cb){
	pix[i].setcb(cb);
}
void Line::setPixelCr(int i, byte cr){
	pix[i].setcr(cr);
}
void Line::setPixelData(int i, byte r, byte g, byte b){
	pix[i].setData(r,g,b);
}

// accessors
Pixel *Line::getLine(){
	return pix;
}
byte Line::getPixelR(int i){
	return pix[i].getR();
}
byte Line::getPixelG(int i){
	return pix[i].getG();
}
byte Line::getPixelB(int i){
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

bool Line::isEdited(){
	if (pix[width].isEdited())
		return true;
	else
		return false;
}

#endif