#ifndef driverImp
#define driverImp

#include "Driver.h"


Driver::Driver(int heightt, int widtht): height (heightt), width (widtht), imageComplete (false), pasth (1), pastv (0), pastp(1) {

	image = new Frame(heightt,widtht);
	
    int prescale[] = {0,1,8,64,256,1024}; // the range of prescale values
    
    // If you instantiate these incorrectly the program might begin collecting data in the middle of a frame
    //pasth = HIGH; // to test whether you have reached the falling/rising edge
    //pastv = LOW;  // to test whether you have reached the falling/rising edge
    //pastp = LOW;  // to test whether you have reached the falling/rising edge
	
	// digital pinModes
    pinMode(d0,INPUT);
    pinMode(d1,INPUT);
    pinMode(d2,INPUT);
    pinMode(d3,INPUT);
    pinMode(d4,INPUT);
    pinMode(d5,INPUT);
    pinMode(d6,INPUT);
    pinMode(d7,INPUT);
    pinMode(vSync,INPUT);
    pinMode(hSync,INPUT);
    pinMode(pClk,INPUT);
    pinMode(sccbClk,OUTPUT);
    pinMode(sccbD,OUTPUT);
    pinMode(sysClk,OUTPUT);
    

	// supply clock pulse to camera: SCCB and Sys
    Timer1.initialize(period);
	
    //Timer1.pwm(sccbClk,duty);
    Timer1.pwm(sysClk,duty,1);
	Timer1.start();
	
}

Frame Driver::getFrame(){
	return *image;
}

void Driver::read(){
	uint8_t data; // used to hold data from pins
	imageComplete = 0; // if end of the frame, this will be updated before function return
	v = digitalRead(vSync);
	if (v == LOW && pastv == HIGH){ // beginning of a new frame (falling edge of vertical sync)
		Serial.println("In new frame");
		while (v==LOW){ // continue reading lines until the frame is fully constructed
			h = digitalRead(hSync);
			if (h == HIGH && pasth == LOW){ // beginning of a new row
				while( h== HIGH ){ // continue reading every pixel until you have constructed the full row
					p = digitalRead(pClk);
					if (p == HIGH && pastp == LOW){ // read a byte of data and add it to the row
						
						// read in the data from the pins using binary math
						data = readPins(d0,d1,d2,d3,d4,d5,d6,d7);
						(*image).readWord(data);
						
					}
				pastp = p;
				h = digitalRead(hSync);
				}
			}
			pasth = h;
			v = digitalRead(vSync);
		}
		imageComplete = 1;
		getFrame().convert();
	}
	pastv = v;
} // end of read

bool Driver::isImageComplete(){
	if (imageComplete == true)
		return true;
	else
		return false;
}

uint8_t Driver::readPins(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7){
    uint8_t data = 0;
    if (digitalRead(d0) == HIGH)
        bitWrite(data,0,1);
    if (digitalRead(d1) == HIGH)
		bitWrite(data,1,1);
    if (digitalRead(d2) == HIGH)
		bitWrite(data,2,1);
    if (digitalRead(d3) == HIGH)
		bitWrite(data,3,1);
    if (digitalRead(d4) == HIGH)
		bitWrite(data,4,1);
    if (digitalRead(d5) == HIGH)
		bitWrite(data,5,1);
    if (digitalRead(d6) == HIGH)
		bitWrite(data,6,1);
    if (digitalRead(d7) == HIGH)
		bitWrite(data,7,1);
    return data;
}

#endif