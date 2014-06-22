#include "Arduino.h"
#include "Line.h"


Line::Line(int widtht){
	width = widtht;
	pix = new Pixel[widtht];
}
Line::Line(){
	width = 0;
}
void Line::setWidth(int widtht){
	width = widtht;
	pix = new Pixel[widtht];
}
Pixel *Line::getLine(){
	return pix;
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
void Line::setPixelData(int i, int r, int g, int b){
	pix[i].setData(r,g,b);
}
void Line::convert(){
	for (int i=0; i<width; i++){
		pix[i].convert();
	}
}