#ifndef frameImp
#define frameImp


#include "Arduino.h"
#include "Frame.h"
#include "Line.h"
#include "Coordinates.h"
#include "Pixel.h"

Frame::Frame(int heightt, int widtht){
	Serial.println("In true Frame constructor");
	Serial.flush();
	height = heightt;
	width = widtht;
	spine = new Line[heightt];
	build = new Line[heightt];
	for (int i=0; i<heightt; i++){
		spine[i].setWidth(widtht);
	}
	lineNum = 0;
	pixNum = 0;
	byteNum = 0;
}
Frame::Frame(){
	Serial.println("In default Frame constructor");
}
Line *Frame::getSpine(){
	return spine;
}
int Frame::getHeight(){
	return height;
}
int Frame::getWidth(){
	return width;
}

Coordinates Frame::locate(int targetR, int targetG, int targetB,
						  int rTolerance, int gTolerance, int bTolerance){
  Coordinates target;
  int xSum = 0;
  int ySum = 0;
  int total = 0;
  // check each row
  for (int i = 0; i<height; i++){
    // check each pixel
    for (int j = 0; j<width; j++){
          // if the R is within the tolerated values
      if (
        spine[i].getPixelR(j) > targetR-rTolerance &&
        spine[i].getPixelR(j) < targetR+rTolerance &&
        // and the G is within the tolerated values
        spine[i].getPixelG(j) > targetG-gTolerance &&
        spine[i].getPixelG(j) < targetG+gTolerance &&
        // and the B is within the tolerated values
        spine[i].getPixelB(j) > targetB-bTolerance &&
        spine[i].getPixelB(j) < targetB+bTolerance){
        // if yes to all, update the sums. Once completed with frame analysis,
        // average the values to find the center of the target
        xSum = xSum + j;
        ySum = ySum = i;
        total++;
      }
    }
  }
  
  target.setY(ySum / total);
  target.setX(xSum / total);
  return target;
}

void Frame::readWord(unsigned int data){
	if (pixNum == width){ // if end of line
		pixNum = 0;
		lineNum++;
		// at the end of the frame, convert the YCbCr data to RGB colorspace and move 
		// the image to the spine from the build
		if (lineNum == height){ // if end of frame
			for (int i=0; i<height; i++){
				build[i].convert(); // convert every row
				// take every converted value and build the pixels of the spine
				for (int j=0; j<width; j++){
					spine[i].setPixelData(j,build[i].getPixelR(i), build[i].getPixelG(i), build[i].getPixelB(i));
				}
			}
		}
	}
	
	
	if (byteNum == 0){ // first byte of the word (Cb of pixel A&B)
		build[lineNum].setPixelCb(pixNum, data);
		build[lineNum].setPixelCb(pixNum+1, data);
		byteNum++;
	}
	
	else if (byteNum == 1){ // second byte of the word (Y of pixel A)
		build[lineNum].setPixelY(pixNum, data);
		byteNum++;
	}
	
	else if (byteNum == 2){ // third byte of the word (Cr of pixel A&B)
		build[lineNum].setPixelCr(pixNum, data);
		build[lineNum].setPixelCr(pixNum+1, data);
		byteNum++;
	}
	
	else if (byteNum == 3){ // fourth and final byte of the word (Y of pixel B)
		build[lineNum].setPixelY(pixNum+1, data);
		byteNum = 0;
		pixNum = pixNum + 2;
	}
}

#endif